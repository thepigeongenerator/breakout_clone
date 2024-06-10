#include "level.h"

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "vector2.h"
#include "constants.h"

//prepares the level to be in a playable state
void level_init(Level* level) {
    level->stop = false;

    // initialize ball
    level->ball.pos.x = (SCREEN_WIDTH / 2) - (BALL_SIZE_DEFAULT / 2);
    level->ball.pos.y = (SCREEN_HEIGHT / 2) - (BALL_SIZE_DEFAULT / 2);
    level->ball.size = BALL_SIZE_DEFAULT;
    level->ball.direction = (Vector2){ 0, BALL_SPEED};

    // initialize bouncer
    level->bouncer.pos.x = (SCREEN_WIDTH / 2) - (BOUNCER_WIDTH_DEFAULT / 2);
    level->bouncer.pos.y = SCREEN_HEIGHT - (BOUNCER_HEIGHT * 2);
    level->bouncer.width = BOUNCER_WIDTH_DEFAULT;
}


void ball_collisions(struct Ball* ball) {

}

//updates the level
void level_update(Level* level, bool* keys) {
    struct Bouncer* bouncer = &level->bouncer;
    struct Ball* ball = &level->ball;

    // if move bouncer LEFT
    if (keys[SDLK_a]) {
        ball->moving = true;

        if (bouncer->pos.x < 0 == false) {
            bouncer->pos.x -= 0.5F;
        }
    }

    // if move bouncer RIGHT
    if (keys[SDLK_d]) {
        ball->moving = true;

        if ((bouncer->pos.x + bouncer->width) > SCREEN_WIDTH == false) {
            bouncer->pos.x += 0.5F; // increase the bouncer pos
        }
    }

    if (ball->moving == false)
        return;

    // update ball position
    ball->pos.x += ball->direction.x;
    ball->pos.y += ball->direction.y;


    // check X axis out of bounds collisions
    if ((ball->pos.x + ball->size) > SCREEN_WIDTH || ball->pos.x < 0) {
        ball->direction.x *= -1;
    }

    // check Y axis out of bounds collisions
    if (ball->pos.y < 0) {
        ball->direction.y *= -1;
    }


    // check bouncer collisions
    if ((ball->pos.x + ball->size) > bouncer->pos.x && ball->pos.x < (bouncer->pos.x + bouncer->width) &&
        (ball->pos.y + ball->size) > bouncer->pos.y && ball->pos.y < (bouncer->pos.y + BOUNCER_HEIGHT)) {
        float x = ball->pos.x - bouncer->pos.x + (ball->size / 2);
        unsigned max = bouncer->width;
        float angle = (x - (0.5F * max)) / max * PI;

        ball->direction.x = SDL_sinf(angle) * BALL_SPEED;
        ball->direction.y = -SDL_cosf(angle) * BALL_SPEED;
    }

    // check lose condition
    if ((ball->pos.y + ball->size) > SCREEN_HEIGHT) {
        level->stop = true;
        ball->moving = false;
    }
}
