#include "include/fs.h"
#include "drivers.h"

typedef struct {
    uint8_t  jump[3];
    uint8_t  oem[8];
    uint16_t sector_size;
    uint8_t  sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t  fat_count;
    uint16_t root_entries;
    uint16_t total_sectors;
    uint8_t  media;
    uint16_t sectors_per_fat;
    // ... другие поля BPB
} __attribute__((packed)) fat12_bpb;

fat12_bpb fat_info;

int fat12_init() {
    uint8_t boot_sector[512];
    if (disk_read(0, boot_sector, 1) != 0)
        return -1;

    // Копируем BPB
    memcpy(&fat_infos, boot_sector, sizeof(fat12_bpb));

    // Проверяем сигнатуру
    if (boot_sector[510] != 0x55 || boot_sector[511] != 0xAA)
        return -1;

    return 0;
}

// Поиск файла в корневом каталоге
int fat12_find_file(const char *name, uint32_t *cluster) {
    // Реализация: сканирование корневого каталога (32-байтовые записи)
    // ...
    return 0;
}
