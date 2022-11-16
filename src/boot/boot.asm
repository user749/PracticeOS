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
    mov eax, 1 ;starting sector to load from , 0 -boot sector, 1-kernel...
    mov ecx, 100 ; total number of sectors to load
    mov edi, 0x0100000 ; address to load them into  
    call ata_lba_read 
    jmp CODE_SEG:0x0100000
                                                   

ata_lba_read:
    mov ebx, eax ; backup the LBA
    ;Send the highest 8 bits of the lba to hard disk controller
    shr eax, 24
    or eax, 0xE0 ; Select the master drive  
    mov dx, 0x1F6 ;port
    out dx, al
    ; Finished sending the highest 8 bits of the LBA

    ; Send the total sectors to read
    mov eax, ecx
    mov dx, 0x1F2
    out dx, al
    ; Finished sending the total sectors to read

    ; Send more bits of the LBA
    mov eax, ebx; Restore the backup LBA
    mov dx, 0x1F3
    out dx, al
    ; Finished sending more bits of the LBA

    ; Sending more bits of the LBA
    mov dx, 0x1F4
    mov eax, ebx ; Restore the backup LBA
    shr eax, 8
    out dx, al
    ; Finished sending more bits of the LBA

    ; Send upper 16 bits of the LBA
    mov dx, 0x1F5
    mov eax, ebx; restore the backup LBA
    shr eax, 16
    out dx, al
    ; Finished sending upper 16 bits of the LBA

    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

; Read all sectors into memory
.next_sector:
    push ecx

; Checking if we need to read
.try_again:
    mov dx, 0x1f7
    in al, dx
    test al, 8
    jz .try_again

; We need to read 256 words at a time
    mov ecx, 256
    mov dx, 0x1F0
    rep insw
    pop ecx
    loop .next_sector
    ; End of reading sectory into memory
    ret
    

times 510- ($ - $$) db 0 ; fill 510 bytes of data with 0, pad the rest with zeros
dw 0xAA55 ;execute our signature, remember little endianess 55AA, dw - double word












