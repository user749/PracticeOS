#include "stdlib.h"
#include "practiceos.h"

void* malloc(size_t size)
{
    return practiceos_malloc(size);

}

void free(void* ptr)
{
    practiceos_free(ptr);

}