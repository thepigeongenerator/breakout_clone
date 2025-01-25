#pragma once

#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 640

#define BOUNCER_HEIGHT        5
#define BOUNCER_WIDTH_DEFAULT 75
#define BOUNCER_SPEED         10.0F

#define BALL_SIZE_DEFAULT 10
#define BALL_SPEED        5.0F

#define BRICK_WIDTH       30
#define BRICK_HEIGHT      15
#define BRICK_PADDING     2
#define BRICK_PADDING_TOP 30
#define BRICK_ROWS        5
#define BRICK_COLUMNS     (int)(SCREEN_WIDTH / (BRICK_WIDTH + BRICK_PADDING))

#define PI 3.14159265358979323846F // pi was being fucky! :D
