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
    // **********************************Изображение запуска экрана**************************************
void draw_boot_screen(const char* bootscreen.bmp) {
    int fd = sys_open(bootscreen.bmp, 0);
    if (fd < 0) {
        vga_write("Error loading bootscreen!\n", 0x0C); // Красный текст
        return;
    }

    // Размер экрана 320x200 = 64000 байт (каждый пиксель — 1 байт = индекс палитры)
    char screen_buffer[64000];
    ssize_t bytes_read = sys_read(fd, screen_buffer, 64000);
    sys_close(fd);

    if (bytes_read != 64000) {
        vga_write("Bootscreen size mismatch!\n", 0x0C);
        return;
    }

    // Копируем буфер в VGA-память (A0000 — начало видеопамяти для 320x200)
    volatile uint8_t* vga_mem = (uint8_t*)0xA0000;
    memcpy(vga_mem, screen_buffer, 64000);

    // Устанавливаем VGA-режим 0x13 (320x200, 256 цветов)
    asm volatile("mov ah, 0x00; mov al, 0x13; int 0x10");
}

    // Запускаем консоль в отдельной задаче
    task_create(shell_task);

    enable_interrupts();

    while (1) {
        schedule();
    }
}
void kernel_main() {
    vga_write("Floppa OS booting...\n", 0x07);
    init_paging();
    init_heap();

    // Отображаем загрузочный экран
    draw_boot_screen("/bootscreen.raw"); // или .bmp, если поддерживается

    task_init();
    task_create(shell_task);
    enable_interrupts();
    while (1) {
        schedule();
    }
}
