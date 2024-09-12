#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../constants.h"
#include "../window/colour.h"
#include "../window/audio.h"
#include "vector2.h"

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
    bool destroyed;
} Brick;

typedef struct {
    Ball ball;
    Bouncer bouncer;
    Brick bricks[BRICK_COLUMNS][BRICK_ROWS];
    AudioDevice* audio_device;
    AudioData bounce_sfx;
} Level;


void level_init(Level* level);
void level_update(Level* level, const Uint8* keys);
