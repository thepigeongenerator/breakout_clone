#include "renderer.h"

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdio.h>

#include "../constants.h"
#include "../errors.h"
#include "../game/level.h"



// initializes the window and renderer
int renderer_init(SDL_Window** window, SDL_Renderer** renderer) {
    // init the window
    *window = SDL_CreateWindow("Quinn's Breakout Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        error(FAILURE_SDL_WINDOW, "Window failed to be created! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    // create a renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (*renderer == NULL) {
        error(FAILURE_SDL_RENDERER, "Renderer failed to be created! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    return SUCCESS;
}

// renders the screen
void renderer_update(RenderData* render_data) {
    SDL_Renderer* renderer = render_data->renderer;
    Level* level = render_data->level;

    int success = 0; // if an error occurs, this value is <0

    // render background
    success |= SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    success |= SDL_RenderClear(renderer);

    // draw player components
    success |= SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    success |= SDL_RenderFillRectF(renderer, &(SDL_FRect){level->bouncer.pos.x, level->bouncer.pos.y, level->bouncer.width, 5});      // draw bouncer
    success |= SDL_RenderFillRectF(renderer, &(SDL_FRect){level->ball.pos.x, level->ball.pos.y, level->ball.size, level->ball.size}); // draw ball

    // draw bricks
    for (int x = 0; x < BRICK_COLUMNS; x++) {
        for (int y = 0; y < BRICK_ROWS; y++) {
            Brick* brick = &level->bricks[x][y];

            if (brick->destroyed == true) {
                continue;
            }

            success |= SDL_SetRenderDrawColor(renderer, brick->colour.r, brick->colour.g, brick->colour.b, brick->colour.a);
            success |= SDL_RenderFillRectF(renderer, &(SDL_FRect){brick->pos.x, brick->pos.y, BRICK_WIDTH, BRICK_HEIGHT}); // draw brick
        }
    }

    if (success < 0) {
        error(FAILURE_SDL_RENDERER, "something went wrong whilst rendering: %s\n", SDL_GetError());
        return;
    }

    // present the result to the renderer
    SDL_RenderPresent(renderer);
}

void renderer_destroy(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
