#include "level.h"

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "constants.h"

//prepares the level to be in a playable state
void level_init(Level* level) {
    // initialize ball
    level->ball.pos.x = SCREEN_WIDTH / 2;
    level->ball.pos.y = SCREEN_HEIGHT / 2;
    level->ball.radius = 1;

    // initialize bouncer
    level->bouncer.pos.x = SCREEN_HEIGHT / 2;
    level->bouncer.pos.y = 5;
    level->bouncer.width = 20;
}

//updates the level
void level_update(Level* level, bool* keys) {}
