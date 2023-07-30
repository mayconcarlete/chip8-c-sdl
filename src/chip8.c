#include <assert.h>
#include <memory.h>
#include <stdbool.h>

#include "chip8.h"

const char chip8_default_character_set[] = {
    0xF0,
    0x90,
    0x90,
    0x90,
    0xF0,
    0x20,
    0x60,
    0x20,
    0x20,
    0x70,
    0xF0,
    0x10,
    0xF0,
    0x80,
    0xF0,
    0xF0,
    0x10,
    0xF0,
    0x10,
    0xF0,
    0x90,
    0x90,
    0xF0,
    0x10,
    0x10,
    0xF0,
    0x80,
    0xF0,
    0x10,
    0xF0,
    0xF0,
    0x80,
    0xF0,
    0x90,
    0xF0,
    0xF0,
    0x10,
    0x20,
    0x40,
    0x40,
    0xF0,
    0x90,
    0xF0,
    0x90,
    0xF0,
    0xF0,
    0x90,
    0xF0,
    0x10,
    0xF0,
    0xF0,
    0x90,
    0xF0,
    0x90,
    0x90,
    0xE0,
    0x90,
    0xE0,
    0x90,
    0xE0,
    0xF0,
    0x80,
    0x80,
    0x80,
    0xF0,
    0xE0,
    0x90,
    0x90,
    0x90,
    0xE0,
    0xF0,
    0x80,
    0xF0,
    0x80,
    0xF0,
    0xF0,
    0x80,
    0xF0,
    0x80,
    0x80,
};

void chip8_init(struct chip8 *chip8)
{
    memset(chip8, 0, sizeof(struct chip8));
    memcpy(&chip8->memory.memory, chip8_default_character_set, sizeof(chip8_default_character_set));
}

void chip8_load(struct chip8 *chip8, const char *buf, size_t size)
{
    assert(size + CHIP8_PROGRAM_LOAD_ADDRESS < CHIP8_MEMORY_SIZE);
    memcpy(&chip8->memory.memory[CHIP8_PROGRAM_LOAD_ADDRESS], buf, size);
    chip8->registers.PC = CHIP8_PROGRAM_LOAD_ADDRESS;
}

static void chip8_exec_extended_eight(struct chip8* chip8, unsigned short opcode){
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char y = (opcode >> 4) & 0x000f;
    unsigned char final_four_bits = opcode & 0x000f;
    unsigned short temp = 0;
    switch (final_four_bits)
    {
    // 8xy0 - LD Vx, Vy - Set Vx = Vy. Stores the value of register Vy in register Vx.
    case 0x00:
        chip8->registers.V[x] = chip8->registers.V[y];
    break;

    // xy1 - OR Vx, Vy Set Vx = Vx OR Vy. Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
    case 0x01:
        chip8->registers.V[x] = chip8->registers.V[x] | chip8->registers.V[y];
    break;

    // 8xy2 - AND Vx, Vy Set Vx = Vx AND Vy. Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
    case 0x02:
        chip8->registers.V[x] = chip8->registers.V[x] & chip8->registers.V[y];
    break;

    // 8xy3 - XOR Vx, Vy Set Vx = Vx XOR Vy. Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
    case 0x03:
        chip8->registers.V[x] = chip8->registers.V[x] ^ chip8->registers.V[y];  
    break;

    // 8xy4 - ADD Vx, Vy Set Vx = Vx + Vy, set VF = carry. The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.
    case 0x04:
        temp = chip8->registers.V[x] + chip8->registers.V[y];
        chip8->registers.V[0x0f] = false;
        if(temp > 0xff){
            chip8->registers.V[0x0f] = true;
        }
        chip8->registers.V[x] = temp;
    break;

    // 8xy5 - SUB Vx, Vy Set Vx = Vx - Vy, set VF = NOT borrow. If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
    case 0x05:
        chip8->registers.V[0x0f] = false;
        if(chip8->registers.V[x] > chip8->registers.V[y]){
            chip8->registers.V[0x0f] = true;
        }
        chip8->registers.V[x] -= chip8->registers.V[y];
    break;

    // 8xy6 - SHR Vx {, Vy} Set Vx = Vx SHR 1. If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
    case 0x06:
        chip8->registers.V[0x0f] = chip8->registers.V[x] & 0x01; // jeito para fazer mais direto em comparacao com os de cimas.
        chip8->registers.V[x] = chip8->registers.V[x] / 2;
    break;

    // 8xy7 - SUBN Vx, Vy Set Vx = Vy - Vx, set VF = NOT borrow. If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
    case 0x07:
        chip8->registers.V[0x0f] = chip8->registers.V[y] > chip8->registers.V[x];
        chip8->registers.V[x] = chip8->registers.V[y] - chip8->registers.V[x];
    break;

    // 8xyE - SHL Vx {, Vy} Set Vx = Vx SHL 1. If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
    case 0x0e:
        chip8->registers.V[0x0f] = chip8->registers.V[x] & 0b10000000;
        chip8->registers.V[x] = chip8->registers.V[x] * 2;
    break;
    }
}

static void chip8_exec_extended(struct chip8* chip8, unsigned short opcode){
    unsigned short nnn = opcode & 0x0fff;
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char y = (opcode >> 4) & 0x000f;
    unsigned char kk = opcode & 0x00ff;
    switch(opcode & 0xf000){
         // 1nnn - JP addr - JP addrs - Jump to location nnn's.
        case 0x1000:
            chip8->registers.PC = nnn;
        break;

        // 2nnn - CALL addr - Call addrs - Call subroutine at nnn.
        case 0x2000:
            chip8_stack_push(&chip8, chip8->registers.PC);
            chip8->registers.PC = nnn;
        break;

        // 3xkk - SE Vx, byte - Skip next instruction if Vx = kk.
        case 0x3000:
            if(chip8->registers.V[x] == kk){
                chip8->registers.PC += 2;
            }
        break;

        // 4xkk - SNE Vx, byte - Skip next instruction if Vx != kk.
        case 0x4000:
            if(chip8->registers.V[x] != kk){
                chip8->registers.PC += 2;
            }
        break;

        // 5xy0 - SE Vx, Vy - Skip next instruction if Vx = Vy.
        case 0x5000:
             if(chip8->registers.V[x] == chip8->registers.V[y]){
                chip8->registers.PC +=2;
             }
        break;

        // 6xkk - LD Vx, byte - The interpreter puts the value kk into register Vx.
        case 0x6000:
            chip8->registers.V[x] = kk;
        break;

        // 7xkk - ADD Vx, byte - Set Vx = Vx + kk. Adds the value kk to the value of register Vx, then stores the result in Vx.
        case 0x7000:
            chip8->registers.V[x] = chip8->registers.V[x] + kk;
        break;

        case 0x8000:
            chip8_exec_extended_eight(chip8, opcode);
        break;

        // 9xy0 - SNE Vx, Vy Skip next instruction if Vx != Vy. The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
        case 0x9000:
            if(chip8->registers.V[x] != chip8->registers.V[y]){
                chip8->registers.PC += 2;
            }
        break;

        // Annn - LD I, add Set I = nnn. The value of register I is set to nnn.
        case 0xA000:
            chip8->registers.I = nnn;
        break;
    }
}

void chip8_exec(struct chip8 *chip8, unsigned short opcode)
{
    switch(opcode){
        // Clear the display.
        case 0x00E0:
            chip8_clear_screen(&chip8->screen);
        break;

        // Return from a subroutine.
        case 0x00EE:
            chip8->registers.PC = chip8_stack_pop(&chip8);
        break;

        default:
            chip8_exec_extended(chip8, opcode);
    }
}
