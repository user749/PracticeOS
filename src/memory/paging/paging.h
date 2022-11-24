#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

//flags
#define PAGING_CACHE_DISABLED  0b00010000
#define PAGING_WRITE_THROUGH   0b00001000
#define PAGING_ACCESS_FROM_ALL 0b00000100
#define PAGING_IS_WRITEABLE    0b00000010
#define PAGING_IS_PRESENT      0b00000001

//defining total table entries and page size
#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024
#define PAGING_PAGE_SIZE 4096

//struct holding 4gb of paging chunks
struct paging_4gb_chunk
{
    uint32_t* directory_entry;
};

// initialize new 4gb of empty paging chunks
struct paging_4gb_chunk* paging_new_4gb(uint8_t flags);
//load the empty paging chunks in a new directory  
void paging_switch(uint32_t* directory);
//function to enable paging
void enable_paging();

//get the table directory 
uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk);

int paging_set(uint32_t* directory, void* virt, uint32_t val);
bool paging_is_aligned(void* addr);


#endif