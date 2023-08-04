#ifndef CHIP8_MEMORY
#define CHIP8_MEMORY

#include "config.h"

struct Chip8Memory{
    unsigned char memory[CHIP8_MEMORY_SIZE];
};

struct Chip8Memory* create_chip8_memory();

void free_chip8_memory(struct Chip8Memory* memory);

unsigned char set_chip8_memory(struct Chip8Memory* memory, int index, unsigned char value);
unsigned char get_chip8_memory(struct Chip8Memory* memory, int index);

#endif