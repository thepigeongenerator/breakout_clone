#include "main.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "game/level.h"
#include "window/audio.h"
#include "window/renderer.h"

#ifdef __EMSCRIPTEN__ // for web builds
#include <emscripten.h>
#endif


bool playing = true;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Level* level = NULL;

// handles game application initialisation
static void init(void) {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        error(FAILURE_SDL_INIT, "SDL could not initialize! SDL Error: %s", SDL_GetError());
        return;
    }

    // initialize the renderer
    if (renderer_init(&window, &renderer) < 0) {
        error(FAILURE_SDL_RENDERER, SDL_GetError());
        return;
    }

    // initialize level
    level = malloc(sizeof(Level));
    level_init(level);

    // initialize audio
    level->audio_device = audio_device_init(32000, AUDIO_S16, 1, 4096);
    level->bounce_sfx = audio_load_wav(level->audio_device, "./bounce.wav");
}

// handles game application updating
static void update(void) {
    // update the input
    {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                exit(SUCCESS);
                break;
            }
        }
    }

    // preform updates
    level_update(level, SDL_GetKeyboardState(NULL));
    renderer_update(&(RenderData){window, renderer, level});
}

// handles game application quitting
void stop(void) {
    playing = false;

#if __EMSCRIPTEN__
    emscripten_cancel_main_loop();
#endif
}

// entry point of the application
int main(int argc, char** argv) {
    init();

#if __EMSCRIPTEN__
    emscripten_set_main_loop(update, 0, 1);
#else
    while (playing)
        update();
#endif

    // cleanup of resources
    SDL_FreeWAV(level->bounce_sfx.buffer);
    SDL_CloseAudioDevice(level->audio_device->id);
    free(level);
    SDL_Quit();

    return 0;
}
