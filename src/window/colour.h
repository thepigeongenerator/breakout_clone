#pragma once
#include <stdint.h>

typedef union {
    unsigned packed;
    struct {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    };
} Colour;
