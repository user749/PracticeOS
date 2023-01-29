#ifndef PRACTICEOS_H
#define PRACTICEOS_H

#include <stddef.h>

void print(const char* message);

int getkey();

void* practiceos_malloc(size_t size);
void practiceos_free(void* ptr);
void practiceos_putchar(char c);

#endif