#include "chip8memory.h"

void chip8_memory_set(struct chip8_memory* memory, int index, unsigned char value){
    memory->memory[index] = value;
}
unsigned char chip8_memory_get(struct chip8_memory* memory, int index){
    return memory->memory[index];
}
