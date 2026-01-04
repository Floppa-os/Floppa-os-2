#include "include/task.h"

void schedule() {
    int next = (current_task + 1) % MAX_TASKS;
    while (tasks[next].state != 1) {  // Ищем RUNNING задачу
        next = (next + 1) % MAX_TASKS;
        if (next == current_task) return;  // Нет других задач
    }

    int prev = current_task;
    current_task = next;

    // Переключаем контекст (ассемблерная функция)
    context_switch(prev, next);
}

void task_yield() {
    schedule();
}
