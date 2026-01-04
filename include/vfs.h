#ifndef VFS_H
#define VFS_H

#include <stddef.h>
#include <stdint.h>

int vfs_open(const char *path, int flags);
ssize_t vfs_read(int fd, void *buf, size_t count);

#endif
