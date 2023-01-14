#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "memory/memory.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "string/string.h"
#include "disk/streamer.h"
#include "fs/file.h"
#include "gdt/gdt.h"
#include "isr80h/isr80h.h"
#include "task/tss.h"
#include "config.h"
#include "task/task.h"
#include "task/process.h"
#include "status.h"
#include "keyboard/keyboard.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char color)
{
    return (color << 8) | c; //shift it by 8 bits and OR with char to get 2 byte combination of ASCII char and color
}


//put chars in the terminal, it doesn't keep track of column and rows
void terminal_putchar(int x, int y, char c, char color)
{
    video_mem[( y * VGA_WIDTH ) + x] = terminal_make_char(c, color);  
}

// write chars in the terminal in an organized fashion (keeps track of column and rows)
void terminal_writechar(char c, char color)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return; 
    }
    
    terminal_putchar(terminal_col, terminal_row, c, color);
    terminal_col += 1; //each time we call this function the column is incremented by one 'H-0 e-1 l-2 l-3 o-4" 
    
    //insures that we are not out of bounds, if we are - go to the next row.
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }    
}

/* This function initializes the terminal by setting the video_mem variable and clearing all chars written by bios. */
void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000); // you write ASII chars into memory starting at address 0xB8000 for colorued displays
    terminal_row = 0;
    terminal_col = 0;    
    for (int y = 0; y < VGA_HEIGTH; y++) //in the bounds of the display heigth
    {
        for (int x = 0; x < VGA_WIDTH; x++) //in the bounds of the display width
        {
            terminal_putchar(x, y, ' ', 0); //clear the array-screen by iterating the ASCII video mem array zeroing it 
        }
        
    }    
}


//print multiple chars
void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }    
}

static struct paging_4gb_chunk* kernel_chunk = 0;

void panic(const char* msg)
{
    print(msg);
    while (1) { }
}
void kernel_page()
{
    kernel_registers();
    paging_switch(kernel_chunk);
}

struct tss tss;
struct gdt gdt_real[PRACTICEOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[PRACTICEOS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00,       .type = 0x00},              // NULL segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},              //Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},              // Kernel data segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},              // User Code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},              // User data segment
    {.base = (uint32_t)&tss, .limit = sizeof(tss), .type = 0xE9}    // TSS segment
};

void kernel_main()
{
    // init the terminal
    terminal_initialize(); 
    
    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, PRACTICEOS_TOTAL_GDT_SEGMENTS);

    //Load the GDT
    gdt_load(gdt_real, sizeof(gdt_real));
    
    //initialize heap
    kheap_init(); 

    //init the filesystems
    fs_init();

    //Search and init the disks
    disk_search_and_init();    

    // init the global descriptor table    
    idt_init(); 

    // Setup the TSS
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000; //kernel stack
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // Load the TSS
    tss_load(0x28);

    //setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    //Switch to kernel paging chunk
    paging_switch(kernel_chunk);

    //enable paging
    enable_paging();

    //register commands
    isr80h_register_commands();

    // init all the system keyboards
    keyboard_init();

    struct process* process = 0;
    int res = process_load("0:/blank.bin", &process);
    if (res != PRACTICEOS_ALL_OK)
    {
        panic("Failed to load blank bin\n");
    }
    
    task_run_first_ever_task();

    while (1) {/* code */}  
}