#include "../include/boot.h"
#include "gdt.h"

// Основная точка входа ядра
void kernel_main() {
    // Инициализация GDT
    gdt_install();

    // Выводим сообщение (для отладки)
    const char *msg = "Hello, Floppa OS!\n";
    // Для простоты не реализуем вывод, предполагаем,
    // что есть какая-то функция для вывода.
}
