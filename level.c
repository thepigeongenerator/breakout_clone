#include "level.h"

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "constants.h"

//prepares the level to be in a playable state
void level_init(Level* level) {
    // initialize ball
    level->ball.pos.x = (SCREEN_WIDTH / 2) - (BALL_SIZE_DEFAULT / 2);
    level->ball.pos.y = (SCREEN_HEIGHT / 2) - (BALL_SIZE_DEFAULT / 2);
    level->ball.size = BALL_SIZE_DEFAULT;

    // initialize bouncer
    level->bouncer.pos.x = (SCREEN_WIDTH / 2) - (BOUNCER_WIDTH_DEFAULT / 2);
    level->bouncer.pos.y = SCREEN_HEIGHT - (BOUNCER_HEIGHT * 2);
    level->bouncer.width = BOUNCER_WIDTH_DEFAULT;
}

//updates the level
void level_update(Level* level, bool* keys) {
    Position* bouncer_pos = &level->bouncer.pos;
    // if move bouncer LEFT
    if (keys[SDLK_a]) {
        bouncer_pos->x--;

        if (bouncer_pos->x == 0) {
            bouncer_pos->x = SCREEN_WIDTH - level->bouncer.width;
        }
    }

    // if move bouncer RIGHT
    if (keys[SDLK_d]) {
        bouncer_pos->x++; // increase the bouncer pos

        if ((bouncer_pos->x + level->bouncer.width) > SCREEN_WIDTH) {
            bouncer_pos->x = 1; //set the bouncer pos to 1
        }
    }
}
