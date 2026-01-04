# Минимальный Makefile для сборки OS

CROSS_COMPILE ?= i686-elf-
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy

CFLAGS := -nostdlib -ffreestanding -fno-builtin -m16 -std=gnu99

BINARY := floppaos.bin
SRC := kernel/main.c kernel/syscall.c kernel/gdt.c
ASM := boot/boot.asm

# Создаём объектные файлы из asm
ASM_OBJ := boot/boot.o

# Объектные файлы из C
OBJ := $(SRC:.c=.o)

all: $(BINARY)

$(BINARY): $(ASM_OBJ) $(OBJ)
	# Линковка
	ld -o temp.elf -T linker.ld $(ASM_OBJ) $(OBJ) --oformat binary
	$(OBJCOPY) -O binary temp.elf $@

$(ASM_OBJ): boot/boot.o

boot/boot.o:
	nasm -f elf32 boot/boot.asm -o $@

clean:
	rm -f $(BINARY) temp.elf $(OBJ) $(ASM_OBJ)
