#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "practiceos.h"

int main(int argc, char** argv)
{
    print("PracticeOS V1.0.0\n");

    while (1)
    {
        print("> ");
        char buf[1024];
        practiceos_terminal_readline(buf, sizeof(buf), true);
        print("\n");
        practiceos_system_run(buf);
        
        print("\n");    
    }
    return 0;
}