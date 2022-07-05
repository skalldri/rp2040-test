#define CONFIG_LV_Z_POINTER_KSCAN_DEV_NAME "KSCAN"
#define CONFIG_BOARD "qemu_cortex_m3"
#define CONFIG_SOC "ti_lm3s6965"
#define CONFIG_NUM_IRQS 43
#define CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC 12000000
#define CONFIG_FLASH_SIZE 256
#define CONFIG_FLASH_BASE_ADDRESS 0x0
#define CONFIG_HEAP_MEM_POOL_SIZE 0
#define CONFIG_ROM_START_OFFSET 0x0
#define CONFIG_CORTEX_M_SYSTICK 1
#define CONFIG_SYS_CLOCK_TICKS_PER_SEC 100
#define CONFIG_SERIAL_INIT_PRIORITY 55
#define CONFIG_TEST_EXTRA_STACK_SIZE 0
#define CONFIG_SERIAL 1
#define CONFIG_MP_NUM_CPUS 1
#define CONFIG_UART_STELLARIS_PORT_0 1
#define CONFIG_UART_STELLARIS_PORT_1 1
#define CONFIG_UART_STELLARIS_PORT_2 1
#define CONFIG_ZEPHYR_CANOPENNODE_MODULE 1
#define CONFIG_ZEPHYR_CHRE_MODULE 1
#define CONFIG_ZEPHYR_HAL_GIGADEVICE_MODULE 1
#define CONFIG_ZEPHYR_HAL_INFINEON_MODULE 1
#define CONFIG_ZEPHYR_HAL_NORDIC_MODULE 1
#define CONFIG_ZEPHYR_HAL_NXP_MODULE 1
#define CONFIG_ZEPHYR_HAL_RPI_PICO_MODULE 1
#define CONFIG_ZEPHYR_LIBLC3CODEC_MODULE 1
#define CONFIG_ZEPHYR_LITTLEFS_MODULE 1
#define CONFIG_ZEPHYR_LORAMAC_NODE_MODULE 1
#define CONFIG_LV_Z_POINTER_KSCAN_MSGQ_COUNT 10
#define CONFIG_ZEPHYR_LVGL_MODULE 1
#define CONFIG_ZEPHYR_LZ4_MODULE 1
#define CONFIG_ZEPHYR_MBEDTLS_MODULE 1
#define CONFIG_ZEPHYR_NANOPB_MODULE 1
#define CONFIG_DEBUG 1
#define CONFIG_ZEPHYR_SOF_MODULE 1
#define CONFIG_ZEPHYR_TFLITE_MICRO_MODULE 1
#define CONFIG_ZEPHYR_TRACERECORDER_MODULE 1
#define CONFIG_ZEPHYR_TRUSTED_FIRMWARE_M_MODULE 1
#define CONFIG_ZEPHYR_ZCBOR_MODULE 1
#define CONFIG_ZEPHYR_ZSCILIB_MODULE 1
#define CONFIG_HAS_CMSIS_CORE 1
#define CONFIG_HAS_CMSIS_CORE_M 1
#define CONFIG_BOARD_REVISION "$BOARD_REVISION"
#define CONFIG_QEMU_TARGET 1
#define CONFIG_BOARD_QEMU_CORTEX_M3 1
#define CONFIG_QEMU_ICOUNT 1
#define CONFIG_QEMU_ICOUNT_SHIFT 6
#define CONFIG_SOC_TI_LM3S6965 1
#define CONFIG_SOC_TI_LM3S6965_QEMU 1
#define CONFIG_SOC_LOG_LEVEL_INF 1
#define CONFIG_SOC_LOG_LEVEL 3
#define CONFIG_ARCH "arm"
#define CONFIG_CPU_CORTEX 1
#define CONFIG_CPU_CORTEX_M 1
#define CONFIG_ISA_THUMB2 1
#define CONFIG_ASSEMBLER_ISA_THUMB2 1
#define CONFIG_COMPILER_ISA_THUMB2 1
#define CONFIG_STACK_ALIGN_DOUBLE_WORD 1
#define CONFIG_FAULT_DUMP 2
#define CONFIG_FP16 1
#define CONFIG_FP16_IEEE 1
#define CONFIG_CPU_CORTEX_M3 1
#define CONFIG_CPU_CORTEX_M_HAS_SYSTICK 1
#define CONFIG_CPU_CORTEX_M_HAS_DWT 1
#define CONFIG_CPU_CORTEX_M_HAS_BASEPRI 1
#define CONFIG_CPU_CORTEX_M_HAS_VTOR 1
#define CONFIG_CPU_CORTEX_M_HAS_PROGRAMMABLE_FAULT_PRIOS 1
#define CONFIG_ARMV7_M_ARMV8_M_MAINLINE 1
#define CONFIG_GEN_ISR_TABLES 1
#define CONFIG_NULL_POINTER_EXCEPTION_DETECTION_NONE 1
#define CONFIG_GEN_IRQ_VECTOR_TABLE 1
#define CONFIG_ARM 1
#define CONFIG_ARCH_IS_SET 1
#define CONFIG_ARCH_LOG_LEVEL_INF 1
#define CONFIG_ARCH_LOG_LEVEL 3
#define CONFIG_MPU_LOG_LEVEL_INF 1
#define CONFIG_MPU_LOG_LEVEL 3
#define CONFIG_SRAM_SIZE 64
#define CONFIG_SRAM_BASE_ADDRESS 0x20000000
#define CONFIG_GEN_PRIV_STACKS 1
#define CONFIG_GEN_SW_ISR_TABLE 1
#define CONFIG_ARCH_SW_ISR_TABLE_ALIGN 0
#define CONFIG_GEN_IRQ_START_VECTOR 0
#define CONFIG_ARCH_HAS_SINGLE_THREAD_SUPPORT 1
#define CONFIG_ARCH_HAS_TIMING_FUNCTIONS 1
#define CONFIG_ARCH_HAS_RAMFUNC_SUPPORT 1
#define CONFIG_ARCH_HAS_NESTED_EXCEPTION_DETECTION 1
#define CONFIG_ARCH_SUPPORTS_COREDUMP 1
#define CONFIG_ARCH_SUPPORTS_ARCH_HW_INIT 1
#define CONFIG_ARCH_HAS_EXTRA_EXCEPTION_INFO 1
#define CONFIG_ARCH_HAS_THREAD_LOCAL_STORAGE 1
#define CONFIG_ARCH_HAS_THREAD_ABORT 1
#define CONFIG_DCACHE 1
#define CONFIG_TOOLCHAIN_HAS_BUILTIN_FFS 1
#define CONFIG_KERNEL_LOG_LEVEL_INF 1
#define CONFIG_KERNEL_LOG_LEVEL 3
#define CONFIG_MULTITHREADING 1
#define CONFIG_NUM_COOP_PRIORITIES 16
#define CONFIG_NUM_PREEMPT_PRIORITIES 15
#define CONFIG_MAIN_THREAD_PRIORITY 0
#define CONFIG_COOP_ENABLED 1
#define CONFIG_PREEMPT_ENABLED 1
#define CONFIG_PRIORITY_CEILING -127
#define CONFIG_NUM_METAIRQ_PRIORITIES 0
#define CONFIG_MAIN_STACK_SIZE 1024
#define CONFIG_IDLE_STACK_SIZE 256
#define CONFIG_ISR_STACK_SIZE 2048
#define CONFIG_ERRNO 1
#define CONFIG_SCHED_MULTIQ 1
#define CONFIG_WAITQ_DUMB 1
#define CONFIG_BOOT_BANNER 1
#define CONFIG_BOOT_DELAY 0
#define CONFIG_SYSTEM_WORKQUEUE_STACK_SIZE 1024
#define CONFIG_SYSTEM_WORKQUEUE_PRIORITY -1
#define CONFIG_ATOMIC_OPERATIONS_BUILTIN 1
#define CONFIG_TIMESLICING 1
#define CONFIG_TIMESLICE_SIZE 0
#define CONFIG_TIMESLICE_PRIORITY 0
#define CONFIG_NUM_MBOX_ASYNC_MSGS 10
#define CONFIG_KERNEL_MEM_POOL 1
#define CONFIG_ARCH_HAS_CUSTOM_SWAP_TO_MAIN 1
#define CONFIG_SWAP_NONATOMIC 1
#define CONFIG_SYS_CLOCK_EXISTS 1
#define CONFIG_TIMEOUT_64BIT 1
#define CONFIG_SYS_CLOCK_MAX_TIMEOUT_DAYS 365
#define CONFIG_XIP 1
#define CONFIG_KERNEL_INIT_PRIORITY_OBJECTS 30
#define CONFIG_KERNEL_INIT_PRIORITY_DEFAULT 40
#define CONFIG_KERNEL_INIT_PRIORITY_DEVICE 50
#define CONFIG_APPLICATION_INIT_PRIORITY 90
#define CONFIG_USE_SWITCH 1
#define CONFIG_USE_SWITCH_SUPPORTED 1
#define CONFIG_TICKLESS_KERNEL 1
#define CONFIG_TOOLCHAIN_SUPPORTS_THREAD_LOCAL_STORAGE 1
#define CONFIG_HAS_DTS 1
#define CONFIG_CONSOLE 1
#define CONFIG_CONSOLE_INPUT_MAX_LINE_LEN 128
#define CONFIG_CONSOLE_HAS_DRIVER 1
#define CONFIG_CONSOLE_INIT_PRIORITY 60
#define CONFIG_UART_CONSOLE 1
#define CONFIG_UART_CONSOLE_LOG_LEVEL_INF 1
#define CONFIG_UART_CONSOLE_LOG_LEVEL 3
#define CONFIG_SERIAL_HAS_DRIVER 1
#define CONFIG_SERIAL_SUPPORT_INTERRUPT 1
#define CONFIG_UART_LOG_LEVEL_INF 1
#define CONFIG_UART_LOG_LEVEL 3
#define CONFIG_UART_USE_RUNTIME_CONFIGURE 1
#define CONFIG_UART_STELLARIS 1
#define CONFIG_INTC_INIT_PRIORITY 40
#define CONFIG_INTC_LOG_LEVEL_INF 1
#define CONFIG_INTC_LOG_LEVEL 3
#define CONFIG_SYSTEM_CLOCK_INIT_PRIORITY 0
#define CONFIG_TICKLESS_CAPABLE 1
#define CONFIG_SYSTEM_TIMER_HAS_DISABLE_SUPPORT 1
#define CONFIG_CORTEX_M_SYSTICK_INSTALL_ISR 1
#define CONFIG_RISCV_MACHINE_TIMER_SYSTEM_CLOCK_DIVIDER 0
#define CONFIG_RISCV_MACHINE_TIMER_MIN_DELAY 100
#define CONFIG_GROVE_LCD_RGB_LOG_LEVEL_INF 1
#define CONFIG_GROVE_LCD_RGB_LOG_LEVEL 3
#define CONFIG_USBC_LOG_LEVEL_INF 1
#define CONFIG_USBC_LOG_LEVEL 3
#define CONFIG_SUPPORT_MINIMAL_LIBC 1
#define CONFIG_MINIMAL_LIBC 1
#define CONFIG_HAS_NEWLIB_LIBC_NANO 1
#define CONFIG_MINIMAL_LIBC_NON_REENTRANT_FUNCTIONS 1
#define CONFIG_MINIMAL_LIBC_MALLOC 1
#define CONFIG_MINIMAL_LIBC_MALLOC_ARENA_SIZE 0
#define CONFIG_MINIMAL_LIBC_CALLOC 1
#define CONFIG_MINIMAL_LIBC_REALLOCARRAY 1
#define CONFIG_MINIMAL_LIBC_TIME 1
#define CONFIG_STDOUT_CONSOLE 1
#define CONFIG_NEED_LIBC_MEM_PARTITION 1
#define CONFIG_MPSC_PBUF 1
#define CONFIG_CBPRINTF_COMPLETE 1
#define CONFIG_CBPRINTF_FULL_INTEGRAL 1
#define CONFIG_CBPRINTF_N_SPECIFIER 1
#define CONFIG_SYS_HEAP_ALLOC_LOOPS 3
#define CONFIG_SYS_HEAP_SMALL_ONLY 1
#define CONFIG_POSIX_MAX_FDS 4
#define CONFIG_MAX_TIMER_COUNT 5
#define CONFIG_CPLUSPLUS 1
#define CONFIG_STD_CPP11 1
#define CONFIG_CPP_STATIC_INIT_GNU 1
#define CONFIG_PRINTK 1
#define CONFIG_EARLY_CONSOLE 1
#define CONFIG_ASSERT_VERBOSE 1
#define CONFIG_LOG 1
#define CONFIG_LOG_MODE_DEFERRED 1
#define CONFIG_LOG2 1
#define CONFIG_LOG2_DEFERRED 1
#define CONFIG_LOG_DEFAULT_LEVEL 3
#define CONFIG_LOG_OVERRIDE_LEVEL 0
#define CONFIG_LOG_MAX_LEVEL 4
#define CONFIG_LOG_MODE_OVERFLOW 1
#define CONFIG_LOG_PROCESS_TRIGGER_THRESHOLD 10
#define CONFIG_LOG_PROCESS_THREAD 1
#define CONFIG_LOG_PROCESS_THREAD_STARTUP_DELAY_MS 0
#define CONFIG_LOG_PROCESS_THREAD_SLEEP_MS 1000
#define CONFIG_LOG_PROCESS_THREAD_STACK_SIZE 4096
#define CONFIG_LOG_BUFFER_SIZE 1024
#define CONFIG_LOG_TRACE_SHORT_TIMESTAMP 1
#define CONFIG_LOG_FUNC_NAME_PREFIX_DBG 1
#define CONFIG_LOG_BACKEND_SHOW_COLOR 1
#define CONFIG_LOG_TAG_MAX_LEN 0
#define CONFIG_LOG_BACKEND_FORMAT_TIMESTAMP 1
#define CONFIG_LOG_BACKEND_UART 1
#define CONFIG_LOG_BACKEND_UART_BUFFER_SIZE 1
#define CONFIG_LOG_BACKEND_UART_OUTPUT_TEXT 1
#define CONFIG_LOG_BACKEND_UART_OUTPUT_DEFAULT 0
#define CONFIG_LOG_DOMAIN_ID 0
#define CONFIG_LOG2_USE_VLA 1
#define CONFIG_LOG2_ALWAYS_RUNTIME 1
#define CONFIG_TEST_LOGGING_FLUSH_AFTER_TEST 1
#define CONFIG_TOOLCHAIN_ZEPHYR_0_14 1
#define CONFIG_LINKER_ORPHAN_SECTION_WARN 1
#define CONFIG_HAS_FLASH_LOAD_OFFSET 1
#define CONFIG_FLASH_LOAD_OFFSET 0x0
#define CONFIG_FLASH_LOAD_SIZE 0x0
#define CONFIG_LD_LINKER_SCRIPT_SUPPORTED 1
#define CONFIG_LD_LINKER_TEMPLATE 1
#define CONFIG_KERNEL_ENTRY "__start"
#define CONFIG_LINKER_SORT_BY_ALIGNMENT 1
#define CONFIG_SRAM_OFFSET 0x0
#define CONFIG_LINKER_GENERIC_SECTIONS_PRESENT_AT_BOOT 1
#define CONFIG_NO_OPTIMIZATIONS 1
#define CONFIG_COMPILER_COLOR_DIAGNOSTICS 1
#define CONFIG_COMPILER_OPT ""
#define CONFIG_RUNTIME_ERROR_CHECKS 1
#define CONFIG_KERNEL_BIN_NAME "zephyr"
#define CONFIG_OUTPUT_STAT 1
#define CONFIG_OUTPUT_DISASSEMBLY 1
#define CONFIG_OUTPUT_PRINT_MEMORY_USAGE 1
#define CONFIG_COMPAT_INCLUDES 1
#define CONFIG_LEGACY_INCLUDE_PATH 1