[BITS 32]

section .asm

global _start

_start:

_loop:
    call getkey
    push eax
    mov eax, 3 ; Command putchar 
    int 0x80
    add esp, 4
    jmp _loop

getkey:
    mov eax, 2 ;command getkey
    int 0x80
    cmp eax, 0x00 ; if eax is 0, no key in the buffer, interrupt again and check
    je getkey
    ret

section .data
message db 'I can talk with the kernel', 0
