#!/bin/bash
mkdir build

nasm src/bootloader.asm -f bin -o build/bootloader.bin && echo bootloader.asm complete

nasm src/extendedMemory.asm -f elf64 -o build/extendedMemory.o && echo extendedMemory.asm complete
nasm src/Binaries.asm -f elf64 -o build/Binaries.o && echo Binaries.asm complete

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/kernel/kernel.cpp" -o "build/Kernel.o" && echo gcc complete

x86_64-elf-ld -T"src/link.ld" && echo link complete

cat build/bootloader.bin build/kernel.bin > build/bootloader.flp && echo flp complete
