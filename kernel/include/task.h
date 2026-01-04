#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 32
#define STACK_SIZE 4096

typedef struct {
    uint32_t* stack_ptr;      // Указатель на вершину стека
    uint32_t  state;          // Состояние (RUNNING, WAITING, etc.)
    int       pid;            // Идентификатор задачи
    void (*entry_point)();   // Точка входа задачи
} task_t;

extern task_t tasks[MAX_TASKS];
extern int current_task;

void task_init();
int task_create(void (*func)());
void task_yield();
void schedule();

#endif
