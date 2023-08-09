#include <assert.h>
#include "Chip8Stack.h"

    

struct Chip8Stack* create_chip8_stack(){
    return (struct Chip8Stack*)malloc(sizeof(struct Chip8Stack));
}

void free_chip8_stack(struct Chip8Stack* stack){
    free(stack);
}

static void stack_chip8_in_bounds(struct Chip8Stack* stack){
    if(stack->stack_pointer_register < CHIP8_TOTAL_STACK_DEPTH);
}

void stack_chip8_push(struct Chip8Stack* stack, unsigned short value){
    stack->stack_pointer_register += 1;
    stack_chip8_in_bounds(stack);
    stack->stack[stack->stack_pointer_register];
}

unsigned short stack_chip8_pop(struct Chip8Stack* stack){
    stack_chip8_in_bounds(stack);
    unsigned short value = stack->stack[stack->stack_pointer_register];
    stack->stack_pointer_register -= 1;
    return value;
}
