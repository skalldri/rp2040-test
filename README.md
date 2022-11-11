# rp2040-test
A repo used for testing / developing SMP support for the RP2040

# DEV LOG

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