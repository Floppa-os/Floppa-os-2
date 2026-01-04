char* itoa(int val, char* buf, int base) {
    // Упрощённая реализация
    if (val == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }

    int i = 0;
    while (val > 0) {
        buf[i++] = '0' + (val % base);
        val /= base;
    }
    buf[i] = '\0';

    // Разворачиваем строку
    for (int j = 0; j < i / 2; j++) {
        char t = buf[j];
        buf[j] = buf[i - j - 1];
        buf[i - j - 1] = t;
    }
    return buf;
}
