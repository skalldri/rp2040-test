#include <zephyr/zephyr.h>
#include <zephyr/drivers/hwinfo.h>

void primary_thread_entry(void* a, void* b, void* c);
void second_thread_entry(void* a, void* b, void* c);
void tertiary_thread_entry(void* a, void* b, void* c);

K_THREAD_DEFINE(
    primary_thread, 
    4096,
    primary_thread_entry,
    NULL,
    NULL, 
    NULL,
    6,
    0,
    0
);

K_THREAD_DEFINE(
    second_thread, 
    4096,
    second_thread_entry,
    NULL,
    NULL, 
    NULL,
    6,
    0,
    0
);

K_THREAD_DEFINE(
    tertiary_thread, 
    4096,
    tertiary_thread_entry,
    NULL,
    NULL, 
    NULL,
    6,
    0,
    0
);

int main() {
    printk("MAIN THREAD RUN, CPU %d\n", arch_proc_id());
    return 0;
}

static inline void printf_hex(uint8_t* buff, size_t len) {
    static const size_t per_line = 10;
    for (size_t i = 0; i < len; i++) {
        printk("%x ", buff[i]);

        // Last char for this line
        if (i !=0 && i % per_line == 0) {
            printk("\n");
        }
    }

    // Extra newline at the end
    printk("\n");
}

void primary_thread_entry(void* a, void* b, void* c) {
    static uint8_t id[256];
    while(true) {
        k_msleep(15000);
        size_t len = hwinfo_get_device_id(id, 256);
        printk("Device Serial Number: ");
        printf_hex(id, len);
    }
}

void second_thread_entry(void* a, void* b, void* c) {
    while(true) {
        printk("Hello world from secondary thread, CPU %d!\n", arch_proc_id());
        k_msleep(300);
    }
}

void tertiary_thread_entry(void* a, void* b, void* c) {
    while(true) {
        printk("Hello world from tertiary thread, CPU %d\n", arch_proc_id());
        k_msleep(200);
    }
}

