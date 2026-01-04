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
