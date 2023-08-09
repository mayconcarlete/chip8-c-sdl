#ifndef CHIP8STACK_H
#define CHIP8STACK_H

#include "config.h"


struct Chip8Stack {
    unsigned short stack[CHIP8_TOTAL_STACK_DEPTH];
    unsigned char stack_pointer_register;
};

struct Chip8Stack* create_chip8_stack();
void free_chip8_stack(struct Chip8Stack* stack);

void stack_chip8_push(struct Chip8Stack* stack, unsigned short value);
unsigned short stack_chip8_pop(struct Chip8Stack* stack);


#endif
