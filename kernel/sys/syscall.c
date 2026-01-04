#include "include/task.h"

int sys_task_create(void (*func)()) {
    return task_create(func);
}

void sys_task_yield() {
    task_yield();
}

// Таблица системных вызовов (дополняем)
void* syscall_table[] = {
    [SYS_WRITE]  = sys_write,
    [SYS_OPEN]   = sys_open,
    [SYS_READ]   = sys_read,
    [SYS_TASK_CREATE] = sys_task_create,
    [SYS_TASK_YIELD]  = sys_task_yield,
};
