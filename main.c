#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "error_codes.h"
#include "renderer.h"
#include "level.h"

#define UPDATES_PER_SEC 50
#define CLOCKS_PER_UPDATE (CLOCKS_PER_SEC / UPDATES_PER_SEC)
#define CLOCKS_PER_UPDATE_F (((float)CLOCKS_PER_SEC) / UPDATES_PER_SEC)

// initializes the game
static int init(SDL_Window** window, SDL_Renderer** renderer, Level* level) {
    level_init(level);
    return renderer_init(window, renderer);
}

// called on each game update
static bool update(Level* level, bool* keys, RenderData* render_data) {
    const clock_t clock_start = clock();

    //update the event keys
    {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return false;
                break;

            case SDL_KEYDOWN:
                keys[e.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                keys[e.key.keysym.sym] = false;
                break;
            }
        }
    }

    // preform updates
    {
        level_update(level, keys); //update the level
        renderer_update(render_data); //update the render
    }

    const clock_t clock_end = clock();

    // provide a delay if needed, otherwise log a warning
    const clock_t clock_diff = clock_end - clock_start;  // difference / how long the operations took
    const int remaining_ms = (int)((CLOCKS_PER_UPDATE_F - clock_diff) / CLOCKS_PER_SEC) * 1000;

    if (remaining_ms < 0) {
        (void)printf("delay between updates was %dms too long.", -remaining_ms);
    }
    else {
        SDL_Delay(remaining_ms);  // wait the time in ms
    }

    return true;
}

// cleans up resources
static void close(SDL_Window* window, SDL_Renderer* renderer) {
    renderer_destroy(window, renderer);
}

// entry-point of the application
int main(void) {
    Level level = { 0 };            //stores the game's state
    SDL_Window* window = NULL;      //the window that is given to the OS
    SDL_Renderer* renderer = NULL;  //the renderer used to draw to the window
    bool keys[322] = { 0 };         //stores the key states

    // initialize
    {
        const int code = init(&window, &renderer, &level);
        if (code != SUCCESS)
            exit(code);
    }

    // TEMP: tell me that the program has been initialized
    (void)printf("initialized!\n");

    // game-loop
    RenderData render_data = { window, renderer, &level }; //contains the data which is used to render the game
    while (update(&level, keys, &render_data));

    // frees media and shuts down SDL
    close(window, renderer);
    return 0;
}