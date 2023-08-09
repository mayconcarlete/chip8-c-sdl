#include <stdlib.h>
#include <memory.h>

#include "acutest.h"
#include "Chip8Stack.h"

void test_stack_chip8_push(void){
    // arrange
    struct Chip8Stack* stack = create_chip8_stack();
    stack->stack_pointer_register = 0;
    memset(stack, 0, sizeof(struct Chip8Stack));
    
    // act
    stack_chip8_push(stack, 0x0ff);
    
    // assert
    TEST_CHECK_(stack->stack_pointer_register == 1, "it should increment the stack value");

    // after all
    free_chip8_stack(stack);
}

TEST_LIST = {
    {"stack_chip8_push", test_stack_chip8_push},
    {0}
};