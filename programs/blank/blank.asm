[BITS 32]

section .asm

global _start

_start:
    call getkey
    push message
    mov eax, 1
    int 0x80
    add esp, 4
    jmp $

getkey:
    mov eax, 2 ;command getkey
    int 0x80
    cmp eax, 0x00 ; if eax is 0, no key in the buffer, interrupt again and check
    je getkey
    ret

section .data
message db 'I can talk with the kernel', 0
