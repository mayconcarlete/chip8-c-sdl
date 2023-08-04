#include <stdlib.h>

#include "Chip8Memory.h"

struct Chip8Memory* create_chip8_memory(){
    return (struct Chip8Memory*)malloc(sizeof(struct Chip8Memory));
}

void free_chip8_memory(struct Chip8Memory* memory){
    free(memory);
}

unsigned char set_chip8_memory(struct Chip8Memory* memory, int index, unsigned char value){
    memory->memory[index] = value;
    return memory->memory[index];
}
unsigned char get_chip8_memory(struct Chip8Memory* memory, int index){
    return memory->memory[index];
}   