#!/bin/bash
mkdir build

nasm bootloader.asm -f bin -o build/bootloader.bin && echo bootloader.asm complete

nasm extendedMemory.asm -f elf64 -o build/extendedMemory.o && echo extendedMemory.asm complete
nasm Binaries.asm -f elf64 -o build/Binaries.o && echo Binaries.asm complete

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "kernel.cpp" -o "build/Kernel.o" && echo gcc complete

x86_64-elf-ld -T"link.ld" && echo link complete

cat build/bootloader.bin build/kernel.bin > build/bootloader.flp && echo flp complete
