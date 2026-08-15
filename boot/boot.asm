[org 0x7C00]
[bits 16]

start:
    cli

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov [boot_drive], dl

    ; Print loading message
    mov si, message
    call print

    ; Load kernel from sector 2
    mov ah, 0x02
    mov al, 10
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [boot_drive]

    mov bx, 0x1000
    int 0x13

    jc disk_error

    ; Load GDT
    lgdt [gdt_descriptor]

    ; Enable Protected Mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Far jump into 32-bit mode
    jmp 0x08:protected_mode


disk_error:
    mov si, error_message
    call print

hang:
    cli
    hlt
    jmp hang


print:
.next:
    lodsb
    cmp al, 0
    je .done

    mov ah, 0x0E
    int 0x10

    jmp .next

.done:
    ret


; ==========================================
; Global Descriptor Table
; ==========================================

gdt_start:

gdt_null:
    dq 0

gdt_code:
    dw 0xFFFF
    dw 0
    db 0
    db 10011010b
    db 11001111b
    db 0

gdt_data:
    dw 0xFFFF
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start


; ==========================================
; 32-bit Protected Mode
; ==========================================

[bits 32]

protected_mode:

    mov ax, 0x10

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x9000

    ; Jump to C kernel
    call 0x1000

    cli

kernel_hang:
    hlt
    jmp kernel_hang


[bits 16]

boot_drive db 0

message db "GlassOS v0.3 - Loading kernel...", 13, 10, 0

error_message db "ERROR: Kernel could not be loaded!", 13, 10, 0


times 510-($-$$) db 0
dw 0xAA55