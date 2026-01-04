#include "include/fs.h"

int sys_open(const char *path, int flags) {
    return vfs_open(path, flags);
}

ssize_t sys_read(int fd, void *buf, size_t count) {
    return vfs_read(fd, buf, count);
}
