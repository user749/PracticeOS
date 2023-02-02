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

    char buf[1024];
    practiceos_terminal_readline(buf, sizeof(buf), true);

    print(buf);


    while (1)
    {
        
    }
    
    return 0;
}
