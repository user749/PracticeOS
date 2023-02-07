#ifndef PRACTICEOS_H
#define PRACTICEOS_H

#include <stddef.h>
#include <stdbool.h>

struct command_argument 
{
    char argument[512];
    struct command_argument* next;

};

struct process_arguments
{
    int argc;
    char** argv;
};

void print(const char* message);
int practiceos_getkey();

void*   practiceos_malloc(size_t size);
void    practiceos_free(void* ptr);
void    practiceos_putchar(char c);
int     practiceos_getkeyblock();
void    practiceos_terminal_readline(char* out, int max, bool output_while_typing);
void    practiceos_process_load_start(const char* filename);
struct command_argument* practiceos_parse_command(const char* command, int max);
void practiceos_process_get_arguments(struct process_arguments* arguments);


#endif