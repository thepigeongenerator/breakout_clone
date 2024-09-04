#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "error_codes.h"
#include "renderer.h"
#include "level.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#define UPDATES_PER_SEC 50
#define CLOCKS_PER_UPDATE (CLOCKS_PER_SEC / UPDATES_PER_SEC)
#define CLOCKS_PER_UPDATE_F (((float)CLOCKS_PER_SEC) / UPDATES_PER_SEC)

Level level = { 0 };            // stores the game's state
SDL_Window* window = NULL;      // the window that is given to the OS
SDL_Renderer* renderer = NULL;  // the renderer used to draw to the window

// initializes the game
static int init(void) {
    level_init(&level);
    return renderer_init(&window, &renderer);
}


// called on each game update
static bool update(void) {
    const clock_t clock_start = clock();

    //update the event keys
    {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return false;
                break;
            }
        }
    }

    RenderData render_data = { window, renderer, &level }; //contains the data which is used to render the game
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    // preform updates
    {
        level_update(&level, keys); //update the level
        renderer_update(&render_data); //update the render
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

#ifdef __EMSCRIPTEN__
static void update_game(void) {
    // stop updating if update returns false
    if (update() == false) {
        emscripten_cancel_main_loop();
    }
}
#endif

// cleans up resources
static void close(SDL_Window* window, SDL_Renderer* renderer) {
    renderer_destroy(window, renderer);
}

// entry-point of the application
int main(void) {
    // initialize
    {
        const int code = init();
        if (code != SUCCESS)
            exit(code);
    }

    // TEMP: tell me that the program has been initialized
    (void)printf("initialized!\n");

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(update_game, 0, 1); // don't utilise setting the FPS, as we already do this
#else
    while (update() && (level.stop == false));
#endif

    // frees media and shuts down SDL
    close(window, renderer);
    (void)printf("finished!\n");
    return 0;
}