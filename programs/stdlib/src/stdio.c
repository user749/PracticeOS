#include "stdio.h"
#include "practiceos.h"

int putchar(int c)
{   
    practiceos_putchar((char)c);
    return 0;
}