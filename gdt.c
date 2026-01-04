#include "gdt.h"

// Простая таблица GDT
static struct gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned short limit_high_point;
    unsigned char base_high;
} __attribute__((packed));

static struct gdt_desc {
    unsigned short size;
    unsigned int base;
} __attribute__((packed));

static struct gdt_entry gdt_entries[3];
static struct gdt_desc gdt_descriptor;

void gdt_install() {
    // Заполнение таблицы GDT
    // NULL descriptor
    gdt_entries[0] = (struct gdt_entry){0,0,0,0,0,0};
    // Кодовая
    gdt_entries[1] = (struct gdt_entry){0xFFFF, 0, 0x9A, 0, 0xFFFF, 0};
    // Данными
    gdt_entries[2] = (struct gdt_entry){0xFFFF, 0, 0x92, 0, 0xFFFF, 0};

    gdt_descriptor.size = sizeof(gdt_entries) - 1;
    gdt_descriptor.base = (unsigned int)&gdt_entries;

    // Загрузка таблицы GDT
    asm volatile ("lgdt [%0]" : : "r" (&gdt_descriptor));
}
