#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    unsigned x;
    unsigned y;
} Position;

typedef struct {
    struct {
        unsigned radius;
        Position pos;
    } ball;

    struct {
        unsigned width;
        Position pos;
    } bouncer;
} Level;


void level_init(Level* level);
void level_update(Level* level, bool* keys);
