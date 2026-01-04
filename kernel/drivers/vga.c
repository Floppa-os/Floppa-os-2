#include "include/drivers.h"

void vga_write(const char *str, uint8_t color) {
    volatile uint16_t *vga = (uint16_t *)0xB8000;
    static int offset = 0;

    for (int i = 0; str[i]; i++) {
        vga[offset++] = (color << 8) | str[i];
    }
}
