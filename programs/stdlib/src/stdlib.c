#include "stdlib.h"
#include "practiceos.h"

char* itoa(int i)
{
    static char text[12];
    int loc = 11; 
    text[11] = 0; //append zero terminator
    char neg = 1; // considered signed by default
    
    //if int i is positive or 0
    if (i >= 0)
    {
        neg = 0; // set neg to null
        i = -i; // set i to -i -> 250 to -250
    }
    
    while (i)
    {
        text[--loc] = '0' - (i % 10); // text[10] = 0 - 250%10 -> text[10] = 0 - 0 
        i /= 10;  // i=25
    }

    if (loc == 11)
        text[--loc] = '0'; //

    if (neg)
    {
        text[--loc] = '-';
    }

    return &text[loc];         
}

void* malloc(size_t size)
{
    return practiceos_malloc(size);

}

void free(void* ptr)
{
    practiceos_free(ptr);
}