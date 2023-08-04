#include <assert.h>
#include <stdlib.h>

#include "Chip8Memory.h"

struct Chip8Memory* create_chip8_memory(){
    return (struct Chip8Memory*)malloc(sizeof(struct Chip8Memory));
}

void free_chip8_memory(struct Chip8Memory* memory){
    free(memory);
}

static void memory_in_bounds(int index){
    assert(index >= 0 && index < CHIP8_MEMORY_SIZE);
}

unsigned char set_chip8_memory(struct Chip8Memory* memory, int index, unsigned char value){
    memory_in_bounds(index);
    memory->memory[index] = value;
    return memory->memory[index];
}
unsigned char get_chip8_memory(struct Chip8Memory* memory, int index){
    memory_in_bounds(index);
    return memory->memory[index];
}   