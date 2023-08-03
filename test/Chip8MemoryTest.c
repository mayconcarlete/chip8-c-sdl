#include <stdlib.h>
#include "acutest.h"
#include "Chip8Memory.h"

// TEST_CHECK_(2+2 == 2+2, "It should have the same size of struct chip8_memory"); - Roda todos os testes e mostra os que quebraram.
// TEST_ASSERT(2+2 == 4); - quebra quando primeiro teste falhar, e para a execuçao dos proximos.

void test_create_chip8_memory(void){
    struct Chip8Memory* memory = create_chip8_memory();

    TEST_CHECK_(sizeof(*memory) == sizeof(struct Chip8Memory), "It should have the same size of struct chip8_memory");
    
    free_chip8_memory(memory);
}

void test_chip8_set_memory(void){
    struct Chip8Memory* memory = create_chip8_memory();
    

    free_chip8_memory(memory);
}

TEST_LIST = {
    {"struct chip8_memory* create_chip8_memory", test_create_chip8_memory},
    {"unsigned char set_chip8_memory(struct Chip8Memory* memory, int index, unsigned char value)", test_chip8_set_memory},
    {0}
};