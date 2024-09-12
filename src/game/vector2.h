#pragma once

#define VECTOR2_UP ((Vector2){0, 1})
#define VECTOR2_DOWN ((Vector2){0, -1})
#define VECTOR2_LEFT ((Vector2){-1, 0})
#define VECTOR2_RIGHT ((Vector2){1, 0})
#define VECTOR2_ZERO ((Vector2){0, 0})
#define VECTOR2_ONE ((Vector2){1, 1})

#define vec2_add(v1, v2) ((Vector2){v1.x + v2.x, v1.y + v2.y})
#define vec2_subt(v1, v2) ((Vector2){v1.x - v2.x, v1.y - v2.y})
#define vec2_mult(v, a) ((Vector2){v.x * a, v.y * a})
#define vec2_div(v, a) ((Vector2){v.x / a, v.y / a})

typedef struct {
    float x;
    float y;
} Vector2;
