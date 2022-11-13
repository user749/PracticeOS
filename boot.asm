ORG 0x7c00
BITS 16

;below will caluclate us offset of that segments
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_start:
    jmp short start
    nop

times 33 db 0 ; creating 33 extra bytes because BIOS parameter block sometimes overwrites this

start:
    jmp 0:step2  ; changing our code segment to desired address

step2:
    cli ; clear Interrupts flag (disable), when clearing the segments we don't want to trigger an interrupt
    mov ax, 0 ; we can not move directly values to ds and es
    mov ds, ax
    mov es, ax ; init the extra segment 
    mov ss, ax
    mov sp, 0x7c00
    sti ; Enables Interrupts again, all segments set

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:load32 ;switches to code seg and jumps to load32

; GDT general descriptor table
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code: ;CS should point to this
    dw 0xffff   ; Segment limit first 0-15 bits
    dw 0        ; Base first 0-15 bits
    db 0        ; Base 16-23 bits
    db 0x9a     ; Acess bytes
    db 11001111b; High 4 bit flags and the low 4 bit flags
    db 0        ; Base 24-31 bits

; offset 0x10
gdt_data: ; DS, SS, ES, FS, GS
    dw 0xffff   ; Segment limit first 0-15 bits
    dw 0        ; Base first 0-15 bits
    db 0        ; Base 16-23 bits
    db 0x92     ; Acess bytes
    db 11001111b; High 4 bit flags and the low 4 bit flags
    db 0        ; Base 24-31 bits

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[BITS 32]
load32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp
    jmp $

times 510- ($ - $$) db 0 ; fill 510 bytes of data with 0, pad the rest with zeros
dw 0xAA55 ;execute our signature, remember little endianess 55AA, dw - double word
