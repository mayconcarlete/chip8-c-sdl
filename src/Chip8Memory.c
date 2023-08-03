#include <stdlib.h>

#include "Chip8Memory.h"

struct Chip8Memory* create_chip8_memory(){
    return (struct Chip8Memory*)malloc(sizeof(struct Chip8Memory));
}

void free_chip8_memory(struct Chip8Memory* memory){
    free(memory);
}

// unsigned char set_memory(struct chip8_memory* memory, int index, unsigned char value){}
// unsigned char get_memory(struct chip8_memory* memory, int index){}