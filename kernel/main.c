#include "include/kernel.h"
#include "include/task.h"

void kernel_main() {
    vga_write("Floppa OS booting...\n", 0x07);
    init_paging();
    init_heap();
    task_init();  // Инициализируем подсистему задач

    // Создаём первую задачу
    task_create(task_example);

    enable_interrupts();

    while (1) {
        schedule();  // Основной цикл планировщика
    }
}

// Пример задачи
void task_example() {
    int counter = 0;
    while (1) {
        vga_write("Task: ", 0x07);
        vga_write(itoa(counter++), 0x07);
        vga_write("\n", 0x07);
        sys_task_yield();  // Добровольно отдаём управление
    }
}

#include "include/kernel.h"
#include "include/task.h"
#include "include/shell.h"

void kernel_main() {
    vga_write("Floppa OS booting...\n", 0x07);
    init_paging();
    init_heap();
    task_init();

    // Запускаем консоль в отдельной задаче
    task_create(shell_task);

    enable_interrupts();

    while (1) {
        schedule();
    }
}
