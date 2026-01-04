#include "include/vfs.h"

struct vfs_node {
    char name[12];
    uint32_t size;
    uint32_t start_cluster;
    int flags; // READ_ONLY, DIRECTORY и т.п.
};

// Таблица открытых файлов
static struct vfs_node open_files[32];

int vfs_open(const char *path, int flags) {
    uint32_t cluster;
    if (fat12_find_file(path, &cluster) != 0)
        return -1;

    // Находим свободный слот
    for (int i = 0; i < 32; i++) {
        if (open_files[i].flags == 0) {
            strcpy(open_files[i].name, path);
            open_files[i].start_cluster = cluster;
            open_files[i].flags = flags;
            return i; // Возвращаем дескриптор
        }
    }
    return -1;
}

ssize_t vfs_read(int fd, void *buf, size_t count) {
    if (fd < 0 || fd >= 32 || open_files[fd].flags == 0)
        return -1;

    // Чтение данных через FAT12 (упрощённо)
    // ...
    return count;
}
