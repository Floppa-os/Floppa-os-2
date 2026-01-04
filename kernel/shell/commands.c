#include "include/shell.h"
#include "include/fs.h"

// Список команд
static struct {
    const char *name;
    void (*func)(int argc, char **argv);
} commands[] = {
    {"help", cmd_help},
    {"reboot", cmd_reboot},
    {"ls", cmd_ls},
    {NULL, NULL}  // Конец списка
};

// Разбиваем строку на аргументы
static int parse_args(char *cmd, char **argv) {
    int argc = 0;
    char *p = cmd;
    while (*p) {
        if (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\r') {
            argv[argc++] = p;
            while (*p && *p != ' ' && *p != '\t' && 
                   *p != '\n' && *p != '\r') p++;
            *p = '\0';  // Завершаем строку
        }
        p++;
    }
    return argc;
}

void execute_command(char *cmd) {
    char *argv[10];
    int argc = parse_args(cmd, argv);

    for (int i = 0; commands[i].name; i++) {
        if (strcmp(argv[0], commands[i].name) == 0) {
            commands[i].func(argc, argv);
            return;
        }
    }
    shell_puts("Unknown command: ");
    shell_puts(argv[0]);
    shell_puts("\n");
}

// Реализация команд
void cmd_help(int argc, char **argv) {
    shell_puts("Available commands:\n");
    for (int i = 0; commands[i].name; i++) {
        shell_puts("  ");
        shell_puts(commands[i].name);
        shell_puts("\n");
    }
}

void cmd_reboot(int argc, char **argv) {
    shell_puts("Rebooting...\n");
    asm volatile("mov $0xFE, %%ah\n"
                 "int $0x19"
                 : : : "ah");
}

void cmd_ls(int argc, char **argv) {
    // Пример: выводим файлы из корневого каталога FAT12
    // (реальная реализация требует обхода FAT)
    shell_puts("file1.txt\n");
    shell_puts("kernel.bin\n");
}
#include "include/shell.h"
#include "include/fs.h"

// ... (предыдущие команды: help, reboot, ls)


// Новые команды
void cmd_clear(int argc, char **argv);
void cmd_echo(int argc, char **argv);
void cmd_cat(int argc, char **argv);
void cmd_pwd(int argc, char **argv);
void cmd_date(int argc, char **argv);


static struct {
    const char *name;
    void (*func)(int argc, char **argv);
} commands[] = {
    {"help",     cmd_help},
    {"reboot",   cmd_reboot},
    {"ls",       cmd_ls},
    {"clear",    cmd_clear},
    {"echo",     cmd_echo},
    {"cat",      cmd_cat},
    {"pwd",      cmd_pwd},
    {"date",     cmd_date},
    {NULL,       NULL}
};
