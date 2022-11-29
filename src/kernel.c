#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "string/string.h"
#include "disk/streamer.h"

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
void kernel_main()
{
    // init the terminal
    terminal_initialize(); 
    print("Hello world\n Hello");
    
    //initialize heap
    kheap_init(); 

    //Search and init the disks
    disk_search_and_init();    

    // init the global descriptor table    
    idt_init(); 

    //setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    //Switch to kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    //enable paging
    enable_paging();

    //enable the system interrupts
    enable_interrupts(); 

    struct disk_stream* stream = diskstreamer_new(0);
    diskstreamer_seek(stream, 0x201);
    unsigned char c = 0;
     diskstreamer_read(stream, &c, 1);

    while (1)
    {
        /* code */
    }
}