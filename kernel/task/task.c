#include "include/task.h"
#include "include/kernel.h"

task_t tasks[MAX_TASKS];
int current_task = -1;

void task_init() {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].state = 0;  // 0 = не используется
        tasks[i].pid = i;
    }
}

int task_create(void (*func)()) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].state == 0) {
            // Выделяем стек
            uint32_t* stack = (uint32_t*)kmalloc(STACK_SIZE);
            if (!stack) return -1;

            // Инициализируем стек (обратный порядок для x86)
            stack += STACK_SIZE / 4 - 1;  // Вершина стека
            stack[0] = (uint32_t)func;     // Адрес возврата
            stack[-1] = 0xDEADBEEF;      // Метка для отладки

            tasks[i].stack_ptr = stack;
            tasks[i].entry_point = func;
            tasks[i].state = 1;  // RUNNING

            return i;
        }
    }
    return -1;  // Нет свободных слотов
}
