#ifndef FS_H
#define FS_H

#include <stdint.h>

int fat12_init();
int fat12_find_file(const char *name, uint32_t *cluster);

#endif
