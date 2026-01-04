CC = gcc
AS = nasm
CFLAGS = -m32 -fno-pie -nostdlib -nostartfiles -nodefaultlibs -Wall -Werror
ASFLAGS = -f elf32

OBJ = boot/bootloader.o kernel/main.o kernel/memory/paging.o \
      kernel/drivers/vga.o kernel/sys/syscall.o lib/string.o

all: floppa.bin

boot/bootloader.o: boot/bootloader.asm
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

floppa.bin: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -T link.ld -o $@

clean:
	rm -f $(OBJ) floppa.bin

OBJ = boot/bootloader.o kernel/main.o kernel/memory/paging.o \
      kernel/drivers/vga.o kernel/fs/fat12.o kernel/fs/vfs.o \
      kernel/task/scheduler.o kernel/task/context.o \
      lib/string.o lib/stdio.o

kernel/task/context.o: kernel/task/context.s
	$(AS) $(ASFLAGS) $< -o $@
OBJ = boot/bootloader.o kernel/main.o \
      kernel/memory/paging.o \
      kernel/drivers/vga.o kernel/drivers/keyboard.o \
      kernel/fs/fat12.o kernel/fs/vfs.o \
      kernel/task/scheduler.o kernel/task/context.o \
      kernel
