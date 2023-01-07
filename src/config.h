#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10


#define PRACTICEOS_TOTAL_INTERRUPTS 512

// 100 mb heap size
#define PRACTICEOS_HEAP_SIZE_BYTES 104857600
#define PRACTICEOS_HEAP_BLOCK_SIZE 4096
#define PRACTICEOS_HEAP_ADDRESS 0x01000000
#define PRACTICEOS_HEAP_TABLE_ADDRESS 0x00007E00

#define PRACTICEOS_SECTOR_SIZE 512

#define PRACTICEOS_MAX_FILESYSTEMS 12
#define PRACTICEOS_MAX_FILE_DESCRIPTORS 512

#define PRACTICEOS_MAX_PATH 108
#define PRACTICEOS_TOTAL_GDT_SEGMENTS 6

#define PRACTICEOS_PROGRAM_VIRTUAL_ADDRESS 0x400000
#define PRACTICEOS_USER_PROGRAM_STACK_SIZE 1024 * 16
#define PRACTICEOS_PROGRAM_VIRTUAL_STACK_ADDRESS_START 0x3FF000
#define PRACTICEOS_PROGRAM_VIRTUAL_STACK_ADDRESS_END PRACTICEOS_PROGRAM_VIRTUAL_STACK_ADDRESS_START - PRACTICEOS_USER_PROGRAM_STACK_SIZE

#define PRACTICEOS_MAX_PROGRAM_ALLOCATIONS 1024
#define PRACTICEOS_MAX_PROCESESS 12

#define USER_DATA_SEGMENT 0x23
#define USER_CODE_SEGMENT 0x1b

#endif