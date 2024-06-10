#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "vector2.h"

typedef struct {
    bool stop;

    struct Ball {
        bool moving;
        unsigned size;
        Vector2 pos;
        Vector2 direction;
    } ball;

    struct Bouncer {
        unsigned width;
        Vector2 pos;
    } bouncer;
} Level;


void level_init(Level* level);
void level_update(Level* level, bool* keys);
