#include "practiceos.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv)
{
    printf("My age is %i\n", 44);
    print("hello how are you!\n");

    print(itoa(2332));

    putchar('z');

    void* ptr = malloc(512);
    free(ptr);
    if (ptr)
    {
        
    }
                                            

    while (1)
    {
        if (getkey() != 0)
        {
            print("key was pressed\n");
        }
    }
    
    return 0;
}
