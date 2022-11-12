ORG 0
BITS 16

_start:
    jmp short start
    nop

times 33 db 0 ; creating 33 extra bytes because BIOS parameter block sometimes overwrites this

start:
    jmp 0x7c0:step2  ; changing our code segment to desired address

step2:
    cli ; clear Interrupts flag (disable), when clearing the segments we don't want to trigger an interrupt
    mov ax, 0x7c0 ; we can not move directly values to ds and es
    mov ds, ax
    mov es, ax ; init the extra segment 
    mov ax, 0x00 ; set all the segments  ds,es,ss and stack pointer
    mov ss, ax
    mov sp, 0x7c00
    sti ; Enables Interrupts again, all segments set

    mov ah, 2 ; READ SECTOR COMMAND
    mov al, 1 ; ONE SECTOR TO READ
    mov ch, 0 ; Cylinder low eight bits
    mov cl, 2 ; Read sector two
    mov dh, 0 ; Head Number
    mov bx, buffer
    int 0x13

    jc error; if the carry flag set jump to the error
    mov si, buffer
    call print

    jmp $ ;infinite loop to display char by char , 1.h 2. e 3.l 4.l 5.o ...

error:
    mov si, error_message
    call print
    jmp $

print:
    mov bx, 0 ; color 

.loop: 
    lodsb ;load chars from our address
    cmp al,0 ; null terminator
    je .done
    call print_char ; output char to the screen
    jmp .loop  ;display all the charachters

.done:    
    ret

print_char:
    mov ah, 0eh ;comamnd for writing in teletype mode
    int 0x10 ;interrupt code - check interrupt jump table
    ret

error_message: db 'Failed to load sector', 0

times 510- ($ - $$) db 0 ; fill 510 bytes of data with 0, pad the rest with zeros
dw 0xAA55 ;execute our signature, remember little endianess 55AA, dw - double word

buffer: ; we reference this only by label, because the bios has loaded only 1 sector