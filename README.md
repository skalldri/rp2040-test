# rp2040-test
A repo used for testing / developing SMP support for the RP2040

# DEV LOG

## 12/4/22
- So lets start building something real with SMP! 
- Lets build a simple USB device
- First problem: hwid
  - On RP2040, the hwid driver reads the flash memory serial number to use as the serial number. Sure....
  - To read this value, we have to take the flash out of XIP mode
  - The functions to do this are RAMFUNCs to ensure that when the flash leaves XIP mode, we can keep executing our code
  - Problem: the other core doesn't know we're about to mess with flash memory, so it will continue executing. It will hit a hard-fault when it tries to load invalid flash memory
  - Solution: lockout the other core using the FIFO. Send a special message to the other core's FIFO ISR, which causes it to busy-wait in the ISR to get unlocked. Ensure the ISR and all dependent functions are RAMFUNCs as well.
  - Great! It works!
- New problem: threads are waking up _way_ too often.
  - Likely cause: the SysTick timers are not consistent between the two cores
  - Need to examine the cortex_m_systick code very carefully to see how to solve this...

## 12/3/22
- Lets try to solve the deadlock issue, and hopefully solve the problem of threads clearly not running at-rate
- Hrm. Just saying "never re-queue threads" is obviously too simplistic.
- Potentially the idle loop busy-waiting is causing us problems...
- YOLO! Lets implement IPI!
- Well that seems to have solved it! Very easy!


## 11/28/22
- Solve one bug, find another
- Eventually deadlocks
- Scheduler on one core is picking a thread which is running on the other core
- Deadlock!
- Code comments suggest this happens if a thread gets put back in the runq while not inside the scheduler spinlock...
- A problem for another day

## 11/28/22
- Solved!
- Looks like bugs in Zephyr
- The idle thread should _never_ be placed in the runq
- Not enough checks to prevent that from happening
- Add more checks to guarantee that it never happens and problem solved!

## 11/27/22 - Second Bug
- The next bug: incorrect idle thread re-queueing on secondary core
- Getting an assert caused by the idle thread getting passed into the re-queuing function
- Happens via k_yield
  - k_yield() -> queue_thread(_current)
  - k_yield() -> z_swap() -> do_swap() -> z_requeue_current() -> ASSERT()
  - Maybe a bug in `should_queue_thread()`? Comments suggest that it should be `return !IS_ENABLED(CONFIG_SMP) && th != _current;`, instead of `return !IS_ENABLED(CONFIG_SMP) || th != _current;`
- Why does k_yield do these silly things? It `dequeue_thread()` then `queue_thread()` the same thread? Maybe this is how yield is implemented, with the intention that it puts the current thread on the back of the runq, so it gets round-robinn'ed

- DO NOT ALLOW J-LINK TO USE "FLASH BREAKPOINTS"
  - RP2040's bootloader will detect invalid CRCs and fail to boot
  - No way to turn it off until the license expires after a day! :(

- Cortex-Debug has bugs that delete all the watchpoints from J-Link unless a breakpoint (any breakpoint) is also enabled in the code. FML.

## 11/27/22
- With the primary core crash out of the way, lets get back to SMP
- Secondary core crashing during initialization
- Problem turns out to be related to stack management
  - ARM cores boot using the machine-mode stack pointer (MSP)
  - Zephyr uses the PSP for all user-mode / thread activity, and the MSP for all ISR work (including some syscalls)
  - Zephyr gets messed up if we don't use the PSP for thread activity
  - When ARM32 takes an interrupt, it remembers which stack was in use before the interrupt occurred (PSP, MSP) and stores a different value in the LR for returning from the ISR. If it was MSP, it stores 0xFFFFFFF9. If it was PSP, it stores 0xFFFFFFFD. When we return from an ISR, this value determines which SP gets used in the code coming back out of the ISR. We need this to be the PSP.
  - The context switching code for ARM32 doesn't do anything special: it assumes that whatever mode we enter the ISR from, we want to return to (unless we enable EXEC_RETURN capture)
  - In the ARM32 startup code for a single core, we set the PSP == the initial value of the MSP, then it switches the processor to using PSP for all startup code. During the initial context switch, we enter the ISR from PSP mode, so we get placed back into PSP mode after the initial context switch. This is how the initial context switch enters the correct stack mode.
  - This also allows us to use the MSP stack for all our boot code / logic, and then reclaim and re-use that stack later for all ISRs. Because MSP is still at it's original power-on value, the first interrupt we take will erase the boot code's stack.
- Secondary core wasn't using PSP before calling the first context switch, which leads to big corruption.
- Secondary core is also using dummy_thread based initialization, which doesn't work with ARM32 yet.
  - Writing non-dummy_thread based startup code for SMP is a lot of work. Easier to make ARM32 support dummy_thread
  - Turns out to not be too hard: just add a special case in the context switching code for "switched_from" == NULL. Then when we detect that we're switching from the dummy_thread to a real thread during startup, set switched_from == NULL.
- Initially tried to get the dummy_thread to initialize correctly, and actually perform a one-time context switch into the dummy thread. This is fools errand though, because the dummy_thread is allocated on the MSP / ISR stack. We trash this stack during the initial context switch, so the dummy_thread cannot be trusted. It's better to set "switched_from" to be NULL in a known-safe thread.
- Was able to get a thread to run on the secondary core! But now we're crashing again.

## 11/26/22
- Finally solved it!
- The problem was that the scheduler was "changing its mind" about what thread it wanted to run next in the ISR handler
- The problem would happen something like this:
  - Setup: we have 3 threads. A, B, C. A is `_current`, and is running.
  - An interrupt happens and interrupts the running A thread. A's CPU registers are preserved by the ISR, and it's stack pointer is stored in PSP while the ISR uses MSP.
  - Scheduler runs at the end of an ISR and selects thread A and B should swap. Code sets up A and B to swap using arch.swap_to and arch.swapped_from. `_current` now points to thread B, because of how Zephyr's context switching code runs
  - Before PendSV has a chance to run, another ISR arrives. Due to tail-chaining, the ISR runs immediately, before PendSV has a chance to run. At this point, thread A's context is still stored on the CPU, but `_current` points at thread B.
  - At the end of the ISR, the scheduler decides that it should swap B and C (because B == `_current`)
  - The scheduler code we wrote would now setup a context switch between B and C using the arch.swapped_from and arch.swap_to variables.
  - PendSV now runs and stores the current CPU context into B. However, the context on the CPU was actually thread A's context!! B's thread context now contains data from thread A.
  - Thread C gets swapped in as normal.
- This repeats until the system crashes, with threads round-robinning through the various available thread context slots
- The fix was to detect this condition in the ISR scheduler. If the thread we are swapping has its swapped_from value set, that means we didn't get a pass through the scheduler yet. We are in a situation where the scheduler asked us to perform swap(A, B) -> swap(B, C) without a PendSV in the middle. We detect this, and collapse it down to swap(A, C)
- Since this can only occur with tail-chained interrupts, and each time we detect it we fix it, this can repeat itself. Say the scheduler changes its mind multiple times. swap(A, B) -> swap(B, C) -> swap (C, A). We execute this as:
  - swap(A, B)
  - swap(B, C) -> Detect missing PendSV, actually record swap(A, C)
  - swap (C, A) -> Detect missing PendSV, actually record swap(A, A)
- Swapping A with A is undesirable / inefficient, but not a huge problem

## 11/25/22
- Picking back up the `k_msleep()` crash. Need to deep-dive the context switch code to see why we might come back from context switch with the wrong stack
- Idle thread is coming back from context switch with the context of "second_thread_entry"
- Added additional logging to thread switching. Seeing some really strange behavior. Maybe _current isn't being updated correctly?
  - See thread switching like this:
  ```
  SWITCH: old (0x20000908) -> new (0x200009e0)
  SWITCH: old (0x200007c0) -> new (0x200009e0)
  ```

  How is this possible? This is happening inside `arch_switch()`, so we _must_ be switching to the idle thread (0x9e0). How can we then be switching immediately from 0x7c0 -> 0x9e0? We are doing:
  ```
  0x908 -> 0x9e0
  0x7c0 -> 0x9e0
  ```

  But we should be doing:
  ```
  0x908 -> 0x9e0
  0x9e0 -> 0x7c0
  0x7c0 -> 0x9e0
  ```

  Seems possible that thread switching is fundamentally broken somehow.

- Seems specific to the idle thread? Other thread switches seem to work OK...
- `_current_cpu->current` is just spontaneously changing into a different thread without going through a context switch
  - This eventually causes a crash, obviously...
  - Need data watchpoint to identify the cause I think
  - Found it!!! `z_get_next_switch_handle()` can/will change the value of `_current_cpu->current` without going through the full `do_swap()` kernel routine.
  - This function gets called in `z_arm_exc_exit`
  - On exit from certain interrupts (ex: timer interrupts) we can perform a context switch
  - Might not be taking the PendSV interrupt on exit from `z_arm_exc_exit`? Potential red-herring due to debug wierdness
  - Added asserts to catch this based on PSP value in callee-saved.
    - Observing this happen with a pair of unrelated threads. Suggests this is round-robinning its way through the threads until it makes its way to one that causes a crash
  - Use watchpoint to catch the first instruction instance where we assign the wrong stack pointer to a thread callee saved instance?
    - This works, and it's a bit nasty. But if we hardware watchpoint every single thread's callee_saved.psp member, we should be able to catch the first instance where the wrong thread gets saved into the wrong stack, and from there track down what causes it
    - Worked to find the first instance of a bad logging_thread PSP store, but it came from the main_thread. Stack pointers are _definitely_ getting round-robin'd through the system

## 11/7/22
- Debugging the crash on the main core:
  ```
  ASSERTION FAIL [!z_is_thread_state_set(z_current_get(), ((1UL << (4))))] @ WEST_TOPDIR/zephyr/kernel/sched.c:1442
  ```
  Turns out that this is a wierd race condition of some kind. One of the threads calling `k_msleep()` gets swapped out in the middle of calling `k_msleep()`, and the `idle` thread gets swapped in. Several questions:
    - The scheduler is getting run while calling `k_msleep()` and the idle thread gets swapped in. Why? Idle thread should be extremely low priority and should never get swapped in for a running thread...
    - Some digging, we're using CONFIG_SCHED_DUMB which looks like a round-robin scheduler. I _guess_ it could pick the idle thread?
    - Investigate _why_ idle is getting swapped in later. Bigger problem is that the thread stack pointer
    is getting messed up somehow. That's how the idle thread ends up in the `k_msleep()` function: when we return from the PendSV ISR, we've still got the stack from the original thread, which is in the middle of `k_msleep()`. This causes the idle thread to get suspended, which isn't allowed.
- Easy-ish to repro. But hard to catch under the debugger to see what's going on. Maybe dump some state to the console to help debug after each context switch?

## 11/5/22
- Spent the day digging into ways to disable CONFIG_ARCH_HAS_CUSTOM_SWAP_TO_MAIN.
  This define is making SMP... difficult, because it bypasses the normal startup procedure for Zephyr. SMP
  startup works better if we follow default Zephyr codepaths.
- Was observing corruption of the new "switch_to" arch member for Aarch32. Finally determined the root cause.
  Recall: ARM has two stacks: MSP and PSP. MSP == Machine Stack Pointer, PSP == Process Stack Pointer.
  During startup in [reset.S](..\zephyrproject\zephyr\arch\arm\core\aarch32\cortex_m\reset.S), line 142, we set the PSP to the same value as the initial stack pointer, then switch to using PSP for our initialization code. We allocate the `dummy_thread` on the stack (see [init.c](..\zephyrproject\zephyr\kernel\init.c), line ~430), and then this dummy_thread pointer gets passed into `arch_swap()` as the `old` thread. `arch_swap()` dutifully fills in the `swap_to` and `swap_from` members of the new `arch` field that I've created. However, remmeber that `dummy_thread` is allocated on the PSP stack. `arch_swap()` causes a context switch into
  the `PendSV` interrupt. As part of swapping into the interrupt context, the processor automatically performs a few operations:
  - It changes the stack pointer from the PSP to the MSP (recall that the MSP is still poining to the initial stack address)
  - It automatically stacks `r0`-`r3` as well as the `lr`
  
  Automatically stacking these variables during the ISR swapover causes the processor to start overwriting the contents of the PSP stack. The PSP was correctly tracking the new location of the top of the stack, including the space needed for `dummy_thread`. MSP was not tracking the contents of the stack, and just starts
  overwriting stuff from the bottom. Since the `arch` members are close to the end of the struct, they get overwritten first by the ISR transition.

- Solutions? Not great ones. 
  - We don't want to make `dummy_thread` static, since that wastes global memory space
  - Trying to avoid special-casing the startup sequence, since that's just what we do already
  - Cortex-R gets around this by having many more stacks, so that they don't pollute each other

- Approach this from the other direction? Modify the SMP startup code to make use of `arch_switch_to_main_thread()`?
- Turning off the custom arch gets us farther...
- We end up in a deadlock:
  - CPU 1 decides that it wants switch to the `z_main_thread`, which is currently running on CPU 0 << -- This is a big problem
  - CPU 1 takes the global scheduler spinlock and waits for `z_main_thread` to get swapped out
  - This is never going to happen! CPU 0 cannot enter the scheduler because CPU 1 is holding the global spinlock
  - `z_main_thread` tries to call `k_msleep()` which gets stuck trying to acquire the global scheduler spinlock

- Why did CPU 1 try to take `z_main_thread` when `secondary_thread` or `idle_thread` were perfectly good candidates?
- Because `z_main_thread` is still in the `runq`. ARM32's custom `arch_switch_to_main_thread()` isn't removing `z_main_thread` from the `runq`
- Removing `z_main_thread` from the `runq` gets things somewhat more unblocked
- CPU 1 is crashing, getting stuck in 0xFFFFFFFE. Looks like a return from an ISR, so probably something is busted about swapping out of the dummy thread