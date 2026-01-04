; Простой загрузчик для GRUB (Multiboot)
.section .text
.global start
start:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    ; Переходим к C-коду ядра
    call kernel_main
    hlt
