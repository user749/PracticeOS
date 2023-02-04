#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "practiceos.h"

int main(int argc, char** argv)
{
    print("PracticeOS V1.0.0\n");

    while (1)
    {
        printf("> ");
        char buf[1024];
        practiceos_terminal_readline(buf, sizeof(buf), true);
        practiceos_process_load_start(buf);    
        print("\n");    
    }
    return 0;
}