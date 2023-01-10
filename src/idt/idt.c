#include "idt.h"
#include "config.h"
#include "kernel.h"
#include "memory/memory.h"
#include "io/io.h"

struct idt_desc idt_descriptors[PRACTICEOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc* ptr);
extern void int21h();
extern void no_interrupt();

void int21h_handler()
{
    print("Keyboard pressed\n");
}

void no_interrupt_handler()
{
    outb(0x20, 0x20);
}

void idt_zero()
{
    print("Divide by zero error\n");
}

//setting the idt structure
void idt_set(int interrupt_na, void* address)
{
    struct idt_desc* desc = &idt_descriptors[interrupt_na];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xEE; //the reason it is not 0E is because we need to take into account other field bits dpl...
    desc->offset_2 = (uint32_t) address >> 16;
}

//initializing the idt
void idt_init()
{
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base = (uint32_t) idt_descriptors;

    for(int i = 0; i < PRACTICEOS_TOTAL_INTERRUPTS; i++)
    {
        idt_set(i, no_interrupt);
    }

    //setting the zero interrupt
    idt_set(0, idt_zero);

    //setting the first interrupt
    idt_set(0x21, int21h);

    // load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}

void isr80h_handle_command(int command, struct interrupt_frame* frame)
{
    

}

void* isr80h_handler(int command, struct interrupt_frame* frame)
{
    void* res = 0;
    kernel_page();
    task_current_save_state(frame);
    res = isr80h_handle_command(command, frame);
    task_page();
    return res;
}