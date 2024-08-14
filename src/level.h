#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "vector2.h"
#include "constants.h"
#include "colour.h"

typedef struct {
    Vector2 pos;
    Vector2 direction;
    unsigned size;
    bool moving;
} Ball;

typedef struct {
    Vector2 pos;
    unsigned width;
} Bouncer;

typedef struct {
    Vector2 pos;
    Colour colour;
} Brick;

typedef struct {
    bool stop;
    Ball ball;
    Bouncer bouncer;
    Brick bricks[BRICK_COLUMNS][BRICK_ROWS];
} Level;


void level_init(Level* level);
void level_update(Level* level, bool* keys);
