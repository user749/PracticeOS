section .asm

global idt_load ; to export the symbol
idt_load:
    push ebp
    mov ebp, esp
    mov ebx, [ebp + 8];
    lidt[ebx]    
    pop ebp
    ret