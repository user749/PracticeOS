[BITS 32]

section .asm

global paging_load_directory
global enable_paging

;load the paging directory with new empty chunks
paging_load_directory:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    mov cr3, eax
    pop ebp
    ret

;enable paging in the system
enable_paging:
    push ebp
    mov ebp, esp
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    pop ebp
    ret