Исходный код `kernel/drivers/keyboard.c` для **Floppa OS 2** с поддержкой:
- чтения скан‑кодов из порта `0x60`;
- преобразования скан‑кодов в ASCII (базовая латинская раскладка + служебные клавиши);
- буферизации ввода для консоли.

---

### `kernel/drivers/keyboard.c`

```c
#include "include/drivers.h"
#include <stdint.h>
#include <string.h>

// Таблица преобразования скан‑кодов → ASCII (упрощённая)
static const char ascii_map[128] = {
    [0x01] = 0x1B,    // Esc
    [0x02] = '1',     // 1
    [0x03] = '2',     // 2
    [0x04] = '3',     // 3
    [0x05] = '4',     // 4
    [0x06] = '5',     // 5
    [0x07] = '6',     // 6
    [0x08] = '7',     // 7
    [0x09] = '8',     // 8
    [0x0A] = '9',     // 9
    [0x0B] = '0',     // 0
    [0x0C] = '-',     // -
    [0x0D] = '=',     // =
    [0x0E] = '\b',  // Backspace
    [0x0F] = '\t',  // Tab
    [0x10] = 'q',    // q
    [0x11] = 'w',    // w
    [0x12] = 'e',    // e
    [0x13] = 'r',    // r
    [0x14] = 't',    // t
    [0x15] = 'y',    // y
    [0x16] = 'u',    // u
    [0x17] = 'i',    // i
    [0x18] = 'o',    // o
    [0x19] = 'p',    // p
    [0x1A] = '[',    // [
    [0x1B] = ']',    // ]
    [0x1C] = '\n',  // Enter
    [0x1D] = 0,     // Ctrl (не символьная клавиша)
    [0x1E] = 'a',    // a
    [0x1F] = 's',    // s
    [0x20] = 'd',    // d
    [0x21] = 'f',    // f
    [0x22] = 'g',    // g
    [0x23] = 'h',    // h
    [0x24] = 'j',    // j
    [0x25] = 'k',    // k
    [0x26] = 'l',    // l
    [0x27] = ';',    // ;
    [0x28] = '\'',   // '
    [0x29] = '`',    // `
    [0x2A] = 0,     // LShift
    [0x2B] = '\\',   // \
    [0x2C] = 'z',    // z
    [0x2D] = 'x',    // x
    [0x2E] = 'c',    // c
    [0x2F] = 'v',    // v
    [0x30] = 'b',    // b
    [0x31] = 'n',    // n
    [0x32] = 'm',    // m
    [0x33] = ',',    // ,
    [0x34] = '.',    // .
    [0x35] = '/',    // /
    [0x36] = 0,     // RShift
    [0x37] = '*',    // * (numpad)
    [0x38] = 0,     // Alt
    [0x39] = ' ',    // Space
    [0x3A] = 0,     // CapsLock
    // ... можно дополнить по необходимости
};

// Состояние модификаторов
static uint8_t shift_pressed = 0;
static uint8_t caps_lock = 0;

// Буфер для необработанных скан‑кодов
#define KEYBUF_SIZE 32
static uint8_t keybuf[KEYBUF_SIZE];
static int keybuf_head = 0;
static int keybuf_tail = 0;

// Чтение байта из порта клавиатуры (0x60)
static inline uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile("inb %1, %0" : "=a"(data) : "dN"(port));
    return data;
}

// Добавление скан‑кода в буфер
static void keybuf_put(uint8_t scancode) {
    if ((keybuf_head + 1) % KEYBUF_SIZE != keybuf_tail) {
        keybuf[keybuf_head] = scancode;
        keybuf_head = (keybuf_head + 1) % KEYBUF_SIZE;
    }
}

// Получение скан‑кода из буфера (если есть)
uint8_t keyboard_read_scancode() {
    if (keybuf_tail != keybuf_head) {
        uint8_t scancode = keybuf[keybuf_tail];
        keybuf_tail = (keybuf_tail + 1) % KEYBUF_SIZE;
        return scancode;
    }
    return 0;
}

// Преобразование скан‑кода в ASCII с учётом модификаторов
char keyboard_to_ascii(uint8_t scancode) {
    // Проверяем, что скан‑код в допустимом диапазоне
    if (scancode >= 128) return 0;

    char c = ascii_map[scancode];

    // Обрабатываем модификаторы для букв
    if (c >= 'a' && c <= 'z') {
        if (shift_pressed || caps_lock) {
            c = c - 'a' + 'A';
        }
    }

    return c;
}

// Обработчик прерывания клавиатуры (вызывается из ISR)
void keyboard_handler() {
    uint8_t scancode = inb(0x60);  // Читаем скан‑код из порта 0x60

    // Определяем, нажата или отпущена клавиша (бит 7)
    uint8_t is_break = scancode & 0x80;
    uint8_t keycode = scancode & 0x7F;

    // Обновляем состояние модификаторов
    if (keycode == 0x2A || keycode == 0x36) {  // LShift или RShift
        shift_pressed = !is_break;
    }
    else if (keycode == 0x3A) {  // CapsLock
        if (!is_break) {
            caps_lock = !caps_lock;
        }
    }

    // Если клавиша нажата (не break-код), добавляем в буфер
    if (!is_break) {
        keybuf_put(keycode);
    }
}

// Инициализация драйвера клавиатуры
void keyboard_init() {
    // Здесь должна быть настройка PIC и вектора прерываний
    // (в учебной ОС часто пропускается; предполагается, что прерывания уже работают)
    memset(keybuf, 0, KEYBUF_SIZE);
    keybuf_head = keybuf_tail = 0;
    shift_pressed = 0;
    caps_lock = 0;
}
```

---

### Как это работает

1. **`keyboard_handler()`**  
   - Вызывается при прерывании от клавиатуры (IRQ1).
   - Читает скан‑код из порта `0x60`.
   - Определяет, нажата (`!is_break`) или отпущена (`is_break`) клавиша.
   - Обновляет флаги `shift_pressed` и `caps_lock`.
   - Помещает **нажатый** скан‑код в кольцевой буфер `keybuf`.


2. **`keyboard_read_scancode()`**  
   - Возвращает следующий скан‑код из буфера (FIFO).
   - Используется консо
