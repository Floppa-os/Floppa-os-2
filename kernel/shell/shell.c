#include "include/shell.h"
#include "include/drivers.h"
#include "include/fs.h"
#include "commands.h"

static char input_buffer[256];
static int input_pos = 0;

void shell_init() {
    shell_puts("Floppa OS Console v0.1\n");
    shell_puts("Type 'help' for commands.\n");
    shell_puts("floppa-os $ ");
}

void shell_putchar(char c) {
    vga_write(&c, 0x07);
}

void shell_puts(const char *str) {
    while (*str) vga_write(str++, 0x07);
}

void shell_clear() {
    // Заполняем экран пробелами с атрибутом 0x07
    volatile uint16_t *vga = (uint16_t *)0xB8000;
    for (int i = 0; i < 2000; i++) vga[i] = 0x0720;
}

// Обработчик ввода с клавиатуры
void shell_on_key(uint8_t scancode, char ascii) {
    if (ascii == '\b') {  // Backspace
        if (input_pos > 0) {
            input_pos--;
            shell_putchar('\b');
            shell_putchar(' ');
            shell_putchar('\b');
        }
    }
    else if (ascii == '\n' || ascii == '\r') {  // Enter
        shell_putchar('\n');
        if (input_pos > 0) {
            input_buffer[input_pos] = '\0';
            execute_command(input_buffer);
            input_pos = 0;
        }
        shell_puts("floppa-os $ ");
    }
    else if (input_pos < 255 && ascii >= ' ') {  // Обычный символ
        input_buffer[input_pos++] = ascii;
        shell_putchar(ascii);
    }
}

// Задача консоли (работает в отдельном потоке)
void shell_task() {
    shell_init();
    while (1) {
        // Ждём ввода (в реальном ядре — через прерывания)
        // Здесь упрощённо: опрашиваем клавиатуру
        uint8_t scancode = keyboard_read_scancode();
        char ascii = keyboard_to_ascii(scancode);
        if (ascii) shell_on_key(scancode, ascii);
        sys_task_yield();
    }
}
