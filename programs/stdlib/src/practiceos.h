#ifndef PRACTICEOS_H
#define PRACTICEOS_H

#include <stddef.h>
#include <stdbool.h>

void print(const char* message);

int practiceos_getkey();

void* practiceos_malloc(size_t size);
void practiceos_free(void* ptr);
void practiceos_putchar(char c);
int practiceos_getkeyblock();
void practiceos_terminal_readline(char* out, int max, bool output_while_typing);


#endif