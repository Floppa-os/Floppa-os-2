#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

void shell_init();
void shell_task();        // Задача-оболочка, работает в фоне
void shell_putchar(char c); // Вывод символа в консоль
void shell_puts(const char *str); // Вывод строки
void shell_clear();        // Очистка экрана

#endif
