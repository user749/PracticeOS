#ifndef IO_H
#define IO_H

//input a byte and a word
unsigned char insb(unsigned short port);
unsigned short insw(unsigned short port);

//output a byte and a word
void outb(unsigned short port, unsigned char val);
void outw(unsigned short port, unsigned short val);


#endif