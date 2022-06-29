
[org 0x7c00]

mov [BOOT_DISK], dl

mov bp, 0x7c00
mov sp, bp

call ReadDisk

jmp PROGRAM_SPACE

%include "src/print.asm"
%include "src/diskRead.asm"

times 510-($-$$) db 0
dw 0xaa55 ;magic number