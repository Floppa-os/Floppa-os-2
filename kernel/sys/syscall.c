#include "include/kernel.h"

int sys_write(int fd, const void *buf, size_t count) {
    if (fd == 1) { // stdout
        vga_write((const char *)buf, 0x07);
        return count;
    }
    return -1;
}

// Таблица системных вызовов
void *syscall_table[] = {
    [SYS_WRITE] = sys_write,
    // ... другие вызовы
};
