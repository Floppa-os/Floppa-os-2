char keyboard_to_ascii(uint8_t scancode) {
    static const char ascii_map[128] = {
        [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', /* ... */
        [0x1C] = '\n',  // Enter
        [0x0E] = '\b',  // Backspace
        /* ... заполнить для нужных клавиш ... */
    };
    return (scancode < 128) ? ascii_map[scancode] : 0;
}
