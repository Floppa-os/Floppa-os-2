# Floppa-os
floppa-os/
├── boot/
│   ├── bootloader.asm      # Загрузчик (x86-64)
│   └── multiboot.h         # Макросы для совместимости с GRUB
├── kernel/
│   ├── main.c             # Точка входа ядра
│   ├── memory/
│   │   ├── paging.c       # Управление страничной памятью
│   │   └── heap.c         # Куча (malloc/free)
│   ├── drivers/
│   │   ├── vga.c          # Вывод на экран (VGA)
│   │   └── keyboard.c       # Обработка ввода с клавиатуры
│   ├── sys/
│   │   ├── syscall.c      # Системные вызовы
│   │   └── process.c      # Управление процессами
│   └── include/
│       ├── kernel.h       # Глобальные определения
│       ├── memory.h       # Прототипы для memory/
│       └── drivers.h        # Прототипы для drivers/
├── lib/
│   ├── string.c           # strlen, strcpy и т.п.
│   └── stdio.c            # printf-подобные функции
├── Makefile               # Сборка проекта
└── README.md              # Описание проекта
