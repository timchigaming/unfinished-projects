# ПЕРЕМЕННЫЕ
ASM = nasm
CC = i686-elf-g++
LD = i686-elf-ld
OC = i686-elf-objcopy

CFLAGS = -c -O0 -ffreestanding -Wall -Wextra -m16 
LDFLAGS = -T tools\BareMetal.ld -m elf_i386 -nostdlib -g

# МЕТКА НА ЦЕЛИ БЕЗ ВЫХОДНЫХ ФАЙЛОВ
.PHONY: all clean run move

# ЦЕЛИ
default: clean all run

bootloader.bin: boot.asm
	$(ASM) -f bin boot.asm -o .\out\bootloader.bin

kernel_entry.elf: kernel_entry.asm
	$(ASM) -f elf -Wall kernel_entry.asm -o .\out\kernel_entry.elf

start.obj: start.cpp
	$(CC) $(CFLAGS) start.cpp -o .\out\$@
start.bin: start.obj kernel_entry.elf
	$(LD) $(LDFLAGS) -o .\out\start.elf .\out\kernel_entry.elf .\out\start.obj
	$(OC) -O binary .\out\start.elf .\out\$@

boot.bin: bootloader.bin start.bin
	copy /b .\out\bootloader.bin+.\out\start.bin boot.bin

clean:
	del /Q *.bin *.o *.elf out\*

run: boot.bin
	qemu-system-i386 -drive format=raw,file=$< -m 64

debug:
	$(ASM) -f bin 		   boot.asm 											   -o .\out\bootloader.bin
	$(ASM) -f elf -g -Wall kernel_entry.asm 									   -o .\out\kernel_entry.elf
	$(CC) $(CFLAGS) -g 	   start.cpp 											   -o .\out\start.obj
	$(LD) $(LDFLAGS) -o .\out\start.elf .\out\kernel_entry.elf .\out\start.obj 
	$(OC) -O binary .\out\start.elf .\out\start.bin

	copy /b .\out\bootloader.bin+.\out\start.bin boot.bin

all: boot.bin