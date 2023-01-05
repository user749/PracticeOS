section .asm

global tss_load

; loads the task switch segment
tss_load:
    push ebp
    mov ebp, esp
    mov ax, [ebp+8] ; TSS segment
    ltr ax
    pop ebp
    ret
