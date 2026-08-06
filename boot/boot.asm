; ==========================================
; GlassOS Bootloader v0.2
; ==========================================

[org 0x7C00]
[bits 16]

start:

    mov ax, 0x0003
    int 0x10

    mov si, title
    call print

    mov si, line
    call print

    mov si, msg1
    call print

    mov si, msg2
    call print

    mov si, msg3
    call print

hang:
    cli
    hlt
    jmp hang

print:
.next:
    lodsb
    cmp al,0
    je .done

    mov ah,0x0E
    int 0x10
    jmp .next

.done:
    ret

title db 13,10
      db "========================================",13,10
      db "          GlassOS v0.2",13,10
      db "========================================",13,10,13,10,0

line db "Booting GlassOS...",13,10,0

msg1 db "[ OK ] BIOS Loaded",13,10,0
msg2 db "[ OK ] Bootloader Started",13,10,0
msg3 db "[ OK ] Kernel Loading...",13,10,13,10,0

times 510-($-$$) db 0
dw 0xAA55