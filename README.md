# Floppa-os
floppa-os/
├── boot/
│   ├── bootloader.asm
│   └── multiboot.h
├── kernel/
│   ├── main.c
│   ├── memory/
│   │   ├── paging.c
│   │   └── heap.c
│   ├── drivers/
│   │   ├── vga.c
│   │   ├── keyboard.c
│   │   └── disk.c          # Новый: работа с диском
│   ├── fs/                # Новый каталог: файловая система
│   │   ├── fat12.c       # Реализация FAT12
│   │   ├── vfs.c         # Виртуальная ФС (VFS)
│   │   └── file.c        # Операции с файлами
│   ├── sys/
│   │   ├── syscall.c
│   │   └── process.c
│   └── include/
│       ├── kernel.h
│       ├── memory.h
│       ├── drivers.h
│       ├── fs.h          # Новый: заголовки ФС
│       └── vfs.h         # Новый: заголовки VFS
├── lib/
│   ├── string.c
│   └── stdio.c
├── tools/                 # Новый: утилиты для создания образа ФС
│   └── mkfat12.py
├── Makefile
└── README.md
