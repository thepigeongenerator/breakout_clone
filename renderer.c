#include "renderer.h"

#include <SDL2/SDL.h>
#include <stdio.h>

#include "error_codes.h"
#include "level.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

// initializes the window and renderer
int renderer_init(SDL_Window** window, SDL_Renderer** renderer) {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        (void)printf("SDL Failed to initialize! SDL_Error: %s\n", SDL_GetError());
        return FAILURE_SDL_INIT;
    }

    // init the window
    *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        (void)printf("Window failed to be created! SDL_Error: %s\n", SDL_GetError());
        return FAILURE_SDL_WINDOW;
    }

    // create a renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (*renderer == NULL) {
        (void)printf("Renderer failed to be created! SDL_Error: %s\n", SDL_GetError());
        return FAILURE_SDL_RENDERER;
    }

    return SUCCESS;
}

// renders the screen
void renderer_update(RenderData* render_data) {
    int success = 0x0;
    success | SDL_SetRenderDrawColor(render_data->renderer, 0x00, 0x00, 0x00, 0xFF);
    success | SDL_RenderClear(render_data->renderer);
    SDL_RenderPresent(render_data->renderer);

    if (success != 0) {
        printf("something went wrong during the render update! -> %d", success);
    }
}

void renderer_destroy(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}