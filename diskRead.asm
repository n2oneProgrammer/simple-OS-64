PROGRAM_SPACE equ 0x8000

ReadDisk:
    mov ah, 0x02
    mov bx, PROGRAM_SPACE
    mov al, 32
    mov dl, [BOOT_DISK]
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13
    jc DiskReadFailed
    ret

BOOT_DISK:
    db 0

DISK_READ_ERROR_STR:
    db 'Disk read failed', 0

DiskReadFailed:
    mov bx, DISK_READ_ERROR_STR
    call PrintString
    hlt