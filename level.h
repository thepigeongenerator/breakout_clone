#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    unsigned x;
    unsigned y;
} Position;

typedef struct {
    Position ball_pos;
    Position bouncer_pos;
} Level;


void level_init(Level* level);
void level_update(Level* level, bool* keys);
