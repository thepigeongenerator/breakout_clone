#pragma once
#include <stdbool.h>
#include <stdint.h>

#include "../constants.h"
#include "../window/audio.h"
#include "../window/colour.h"
#include "vector2.h"

typedef struct {
    Vector2 pos;
    Vector2 direction;
    uint32_t size;
    bool moving;
} Ball;

typedef struct {
    Vector2 pos;
    uint32_t width;
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
void level_update(Level* level, const uint8_t* keys);
