#include <zephyr/zephyr.h>

void second_thread_entry(void* a, void* b, void* c);

K_THREAD_DEFINE(
    second_thread, 
    1024,
    second_thread_entry,
    NULL,
    NULL, 
    NULL,
    6,
    0,
    0
);

int main() {

    while(true) {
        printk("Hello world from main thread, CPU %d\n", arch_proc_id());
        k_msleep(2000);
    }

    return 0;
}

void second_thread_entry(void* a, void* b, void* c) {
    while(true) {
        printk("Hello world from thread 2, CPU %d!\n", arch_proc_id());
        k_msleep(3000);
    }
}