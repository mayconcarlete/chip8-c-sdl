#ifndef CHIP8SCREEN_H
#define CHIP8SCREEN_H

#include <stdbool.h>
#include "config.h"

struct chip8_screen {
    bool pixels[CHIP8_HEIGHT][CHIP8_WIDTH];
};

void chip8_set_screen(struct chip8_screen* screen, int x, int y);
bool chip8_screen_is_set(struct chip8_screen* screen, int x, int y);

void chip8_clear_screen(struct chip8_screen* screen){
    memset(screen->pixels, 0, sizeof(screen->pixels));
}
#endif