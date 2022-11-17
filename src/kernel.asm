[BITS 32]

global _start

extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp
    
    ;Enabling the A20 line
    in al, 0x92
    or al,2
    out 0x92, al
    
    call kernel_main
    
    jmp $


times 512- ($ - $$) db 0 ; used for alignment purposes caused by kernel.asm, so we don't end up in another section while in C, 512%16=0
   ; our assembly shares the same sections as our object file from compiler, we cannot change alignment of our C-compiler,
   ; so we must ensure that our assembly is aligned to 16 bytes because that is what C-compiler is using hence the above statement
   ; also we have to add assembly section in the ldr file, we always add it on the bottom
   ; apart from that, we have to make sure that our kernel object file is firstly linked in the MakeFile
   ; because it could happen that a C-object file runs before our kernel
