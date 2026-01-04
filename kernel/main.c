#include "include/kernel.h"

void kernel_main() {
    vga_write("Floppa OS booting...\n", 0x07);
    init_paging();
    init_heap();
    enable_interrupts();

    while (1) {
        // Основной цикл ядра
    }
}
