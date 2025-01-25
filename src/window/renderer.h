#pragma once

#include <SDL_render.h>
#include <SDL_video.h>

#include "../game/level.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Level* level;
} RenderData;

int renderer_init(SDL_Window** window, SDL_Renderer** renderer);
void renderer_update(RenderData* render_data);
void renderer_destroy(SDL_Window* window, SDL_Renderer* renderer);
