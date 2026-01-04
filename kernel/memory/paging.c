#include "include/memory.h"

void init_paging() {
    // Инициализация таблиц страниц (упрощённо)
    uint32_t *page_dir = (uint32_t *)0x1000;
    for (int i = 0; i < 1024; i++) {
        page_dir[i] = (i << 12) | 0x03; // Присутствие + разрешение записи
    }
    // Загрузка CR3 и включение Paging
    asm volatile("mov %0, %%cr3" : : "r"(page_dir));
    asm volatile("mov %cr0, %eax");
    asm volatile("or $0x80000000, %eax");
    asm volatile("mov %eax, %cr0");
}
