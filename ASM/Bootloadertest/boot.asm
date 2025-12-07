[bits 16]
[org 0x7C00]

_start:
    mov bp, 0x7C00
    mov sp, bp

    mov ah, 0x02
    mov al, 2     ; сколько читать секторов(по 512 байт)
    mov ch, 0     ; цилиндр 0
    mov cl, 2     ; сектор 2
    mov dh, 0     ; головка 0
    mov dl, 0x80  ; первый диск
    mov bx, 0x8000
    int 0x13
    jc disk_error ; если CF=1 (ошибка)

    jmp 0x00:0x8000

disk_error:
;   fill red
    mov ax, 0xB800
    mov es, ax

    mov ah, 0
    mov al, 01000000b ;red

    mov cx, 80*50
    mov di, 0
    
    rep stosb

    jmp $

times 510-($-$$) db 0
dw 0xAA55          ; Сигнатура загрузчика