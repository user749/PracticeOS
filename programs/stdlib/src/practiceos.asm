[BITS 32]

global print:function
global getkey:function
global practiceos_malloc:function

; void print(const char* message)
print:
    push ebp
    mov ebp, esp
    push dword[ebp+8]
    mov eax, 1 ; Command print
    int 0x80
    add esp, 4

    pop ebp
    ret


; int getkey()
getkey:
    push ebp
    mov ebp, esp
    mov eax, 2 ; command getkey
    int 0x80
    pop ebp
    ret


;void* practice_malloc(size_t size)
practiceos_malloc:
    push ebp
    mov ebp, esp
    mov eax, 4; command malloc allocates memory for the process
    push dword[ebp+8] ; first argument pass-variable size
    int 0x80
    add esp, 4
    pop ebp
    ret