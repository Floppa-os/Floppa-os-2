size_t strlen(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *d = dest;
    const uint8_t *s = src;
    for (size_t i = 0; i < n; i++) d[i] = s[i];
    return dest;
}
