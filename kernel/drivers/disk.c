#include "include/drivers.h"

// Чтение сектора с диска (упрощённо, через INT 13h)
int disk_read(uint32_t sector, void *buffer, uint32_t count) {
    asm volatile(
        "mov $0x02, %%ah\n"          // Функция: чтение секторов
        "mov %%cx, %%al\n"           // Количество секторов
        "mov %0, %%bx\n"             // Буфер
        "mov %1, %%cx\n"             // Сектор (биты 0–5 — номер сектора, 6–7 — цилиндр)
        "mov $0x00, %%dh\n"         // Головка 0
        "mov $0x00, %%dl\n"         // Диск 0 (флоппи)
        "int $0x13\n"
        : 
        : "r"(buffer), "r"(sector)
        : "%ax", "%bx", "%cx", "%dx", "memory"
    );
    return 0; // В реальности проверять CF и AH
}
