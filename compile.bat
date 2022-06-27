#!/bin/bash
nasm bootloader.asm -f bin -o bootloader.bin && echo bootloader.asm complete

nasm extendedMemory.asm -f elf64 -o extendedMemory.o && echo extendedMemory.asm complete
nasm Binaries.asm -f elf64 -o Binaries.o && echo Binaries.asm complete

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "kernel.cpp" -o "Kernel.o" && echo gcc complete

x86_64-elf-ld -T"link.ld" && echo link complete

cat bootloader.bin kernel.bin > bootloader.flp && echo flp complete
