#include <zephyr/zephyr.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main);

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
        LOG_INF("Hello world!");
        k_msleep(10000);
    }

    return 0;
}

void second_thread_entry(void* a, void* b, void* c) {
    while(true) {
        LOG_INF("Hello world from thread 2!");
        k_msleep(10000);
    }
}