[BITS 32]

section .asm

global print:function
global practiceos_getkey:function
global practiceos_malloc:function
global practiceos_free:function
global practiceos_putchar:function
global practiceos_process_load_start:function
global practiceos_process_get_arguments:function
global practiceos_system:function

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


; int practiceos_getkey()
practiceos_getkey:
    push ebp
    mov ebp, esp
    mov eax, 2 ; command getkey
    int 0x80
    pop ebp
    ret

; void practiceos_putchar(char c)
practiceos_putchar:
    push ebp
    mov ebp, esp
    mov eax, 3 ; command put char
    push dword[ebp + 8] ; our c variable 
    int 0x80
    add esp, 4
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

; void practiceos_free(void* ptr)
practiceos_free:
    push ebp
    mov ebp, esp
    mov eax, 5 ; Command 5 free - free the allocated memory for this process
    push dword[ebp+8]  ; variable ptr     pop ebp
    int 0x80
    add esp, 4
    pop ebp
    ret

; void practiceos_process_load_start(const char* filename)
practiceos_process_load_start:
    push ebp
    mov ebp, esp
    mov eax, 6 ; cmnd 6 process load start - start a process
    push dword[ebp + 8] ; filename
    int 0x80
    add esp, 4
    pop ebp
    ret

;void practiceos_system(struct command_argument* arguments)
practiceos_system:
    push ebp
    mov ebp, esp
    mov eax, 7 ; Command 7 process_system (runs a system command based on the arguments)
    push dword[ebp + 8] ; Variable "arguments"
    int 0x80
    add esp, 4
    pop ebp
    ret

; void practiceos_process_get_arguments(struct process_arguments* arguments)
practiceos_process_get_arguments:
    push ebp
    mov ebp, esp
    mov eax, 8 ; command 8
    push dword[ebp+8] ; variable arguments
    int 0x80
    add esp, 4
    pop ebp
    ret