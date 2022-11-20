#include "kheap.h"
#include "heap.h"
#include "config.h"
#include "kernel.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;


void kheap_init()
{
    int total_table_entries = PRACTICEOS_HEAP_SIZE_BYTES / PRACTICEOS_HEAP_BLOCK_SIZE;
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)(PRACTICEOS_HEAP_TABLE_ADDRESS);
    kernel_heap_table.total = total_table_entries;

    void* end = (void*)(PRACTICEOS_HEAP_ADDRESS + PRACTICEOS_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void*)(PRACTICEOS_HEAP_ADDRESS), end, &kernel_heap_table);
    if (res < 0)
    {
        print("Failed to crate heap\n");
    }  

}

void* kmalloc(size_t size)
{
    return heap_malloc(&kernel_heap, size); 
}

void kfree(void *ptr)
{
    heap_free(&kernel_heap, ptr);
}