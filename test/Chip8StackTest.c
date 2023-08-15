#include <stdlib.h>
#include <memory.h>

#include "acutest.h"
#include "Chip8Stack.h"

void test_stack_chip8_push(void){
    // arrange
    struct Chip8Stack* stack = create_chip8_stack();
    memset(stack, 0, sizeof(struct Chip8Stack));

    // act
    stack_chip8_push(stack, 0x0ff);

    // assert
    TEST_CHECK_(stack->stack_pointer_register == 1, "it should increment the stack value");
    TEST_CHECK_(stack->stack[stack->stack_pointer_register - 1] = 0xff, "it should get the value pointed by the stack register.");

    stack_chip8_pop(stack);
    // assert
    TEST_CHECK_(stack->stack[stack->stack_pointer_register] == 0x0ff, "it should return the value of address in position 0 of stack");
    TEST_CHECK_(stack->stack_pointer_register == 0, "it should point to position 0 after pop.");

    // after all
    free_chip8_stack(stack);
}

TEST_LIST = {
    {"stack_chip8_push", test_stack_chip8_push},
    {0}
};