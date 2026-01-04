[BITS 16]
[ORG 0x7C00]

start:
    cli
    cld

    ; Переход в protected mode
    call setup_protected_mode

    ; Передача управления ядру
    mov ax, 0x0000
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Загрузка ядра
    extern kernel_main
    call kernel_main

hang:
    jmp hang

setup_protected_mode:
    ; Настройка GDT и включение protected mode (часть пропущена для упрощения)
    ret
times 510 - ($ - $$) db 0
dw 0xAA55
