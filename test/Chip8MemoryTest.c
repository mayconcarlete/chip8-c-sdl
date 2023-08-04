#include <stdlib.h>
#include <memory.h>

#include "acutest.h"
#include "Chip8Memory.h"

// TEST_CHECK_(2+2 == 2+2, "It should have the same size of struct chip8_memory"); - Roda todos os testes e mostra os que quebraram.
// TEST_ASSERT(2+2 == 4); - quebra quando primeiro teste falhar, e para a execuçao dos proximos.
// TEST_MSG("Expected: %s", expected);
// TEST_MSG("Produced: %s", produced);


void test_create_chip8_memory(void){
    // act
    struct Chip8Memory* memory = create_chip8_memory();
    memset(memory, 0, CHIP8_MEMORY_SIZE);

    // assert
    TEST_CHECK_(sizeof(*memory) == sizeof(struct Chip8Memory), "It should have the same size of struct chip8_memory");
    
    free_chip8_memory(memory);
}

void test_set_chip8_memory(void){
    // arrange
    struct Chip8Memory* memory = create_chip8_memory();
    memset(memory, 0, CHIP8_MEMORY_SIZE);
    int position = 10;
    unsigned char value = 0x0ff;

    // act
    unsigned char recevied_value = set_chip8_memory(memory, position, value); 
    
    // assert
    TEST_CHECK_( recevied_value == value, "It should set the position 10 to value 0x0ff");
    
    free_chip8_memory(memory);
}

void test_get_chip8_memory(void){
    // arrange
    struct Chip8Memory* memory = create_chip8_memory();
    memset(memory, 0, CHIP8_MEMORY_SIZE);
    int position = 10;
    unsigned char value = 0x0ff;
    set_chip8_memory(memory, position, value); 
    
    // act
    unsigned char received_value = get_chip8_memory(memory, position);

    // assert
    TEST_CHECK_(received_value == value, "It should get the memory given the position");

    free_chip8_memory(memory);
}

TEST_LIST = {
    {"create_chip8_memory", test_create_chip8_memory},
    {"set_chip8_memory", test_set_chip8_memory},
    {"get_chip8_memory", test_get_chip8_memory},
    {0}
};