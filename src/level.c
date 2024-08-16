#include "level.h"

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "vector2.h"
#include "constants.h"
#include "renderer.h"

//prepares the level to be in a playable state
void level_init(Level* level) {
    level->stop = false;

    // initialize bouncer
    level->bouncer.pos.x = (SCREEN_WIDTH / 2) - (BOUNCER_WIDTH_DEFAULT / 2);
    level->bouncer.pos.y = SCREEN_HEIGHT - (BOUNCER_HEIGHT * 2);
    level->bouncer.width = BOUNCER_WIDTH_DEFAULT;

    // initialize ball
    level->ball.pos.x = (SCREEN_WIDTH / 2) - (BALL_SIZE_DEFAULT / 2);
    level->ball.pos.y = level->bouncer.pos.y - BOUNCER_HEIGHT - BALL_SIZE_DEFAULT;
    level->ball.size = BALL_SIZE_DEFAULT;
    level->ball.direction = (Vector2){ 0, -BALL_SPEED };

    // initialize bricks
    // define the colours of the brick rows
    const Colour colours[BRICK_COLUMNS] = {
        {0x5BCEFAFF},
        {0xF5A9B8FF},
        {0xFFFFFFFF},
        {0xF5A9B8FF},
        {0x5BCEFAFF}
    };

    int brick_width = BRICK_WIDTH + BRICK_PADDING;
    int brick_height = BRICK_HEIGHT + (BRICK_PADDING / 2);
    float level_padding_left = ((float)SCREEN_WIDTH - ((SCREEN_WIDTH / brick_width) * brick_width)) / 2.0F; //for centering

    // store bricks in the level
    for (int x = 0; x < BRICK_COLUMNS; x++) {
        for (int y = 0; y < BRICK_ROWS; y++) {
            Brick* brick = &level->bricks[x][y];
            brick->colour = colours[y];
            brick->pos.x = (x * brick_width) + level_padding_left;
            brick->pos.y = (y * brick_height) + BRICK_PADDING_TOP;
            brick->destroyed = false;
        }
    }
}

// updates the player's "bouncer"
static void update_player(Bouncer* bouncer, Ball* ball, const Uint8* keys) {
    // if move bouncer LEFT
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
        if (bouncer->pos.x < 0 == false) {
            bouncer->pos.x -= BOUNCER_SPEED;

            if (ball->moving == false)
                ball->pos.x -= BOUNCER_SPEED;
        }
    }

    // if move bouncer RIGHT
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
        if ((bouncer->pos.x + bouncer->width) > SCREEN_WIDTH == false) {
            bouncer->pos.x += BOUNCER_SPEED; // increase the bouncer pos

            if (ball->moving == false)
                ball->pos.x += BOUNCER_SPEED;
        }
    }

    // ball launching
    if (ball->moving == false && keys[SDL_SCANCODE_SPACE]) {
        ball->moving = true;
    }
}

// updates the player's ball
static void update_ball(Level* level, Ball* ball, Bouncer* bouncer) {
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
        float x = ball->pos.x - bouncer->pos.x + (ball->size / 2) + 2; // get the X axis relative to the bouncer (add 2, see below)
        unsigned max = bouncer->width + 4; // get the maxiumum of this X axis (add 4 to make it feel more accurate)
        float angle = (x - (max / 2.0F)) / max * (PI / 1.5F); // calculate the angle in radians where the bouncer X axis falls on -60° to 60°

        // change the ball direction
        ball->direction.x = SDL_sinf(angle) * BALL_SPEED;
        ball->direction.y = -SDL_cosf(angle) * BALL_SPEED;
    }

    // check brick collisions
    bool collided = false;
    for (int x = 0; x < BRICK_COLUMNS; x++) {
        for (int y = 0; y < BRICK_ROWS; y++) {
            const Brick* brick = &level->bricks[x][y];

            if (brick->destroyed == true) {
                continue;
            }

            const float max_brick_x = brick->pos.x + BRICK_WIDTH;
            const float brick_max_y = brick->pos.y + BRICK_HEIGHT;
            if (ball->pos.x < max_brick_x && (ball->pos.x + ball->size) > brick->pos.x &&
                ball->pos.y < brick_max_y && (ball->pos.y + ball->size) > brick->pos.y) {
                level->bricks[x][y].destroyed = true;

                // skip changing direction of we already did
                if (collided == true) {
                    continue;
                }

                //float ball_centre_x = ball->pos.x + (ball->size / 2.0F);
                float ball_centre_y = ball->pos.y + (ball->size / 2.0F);

                // manage ball bounce direction; only bounce along the X axis if the ball's Y centre is in between dthe top and bottom of the block
                if (brick->pos.y < ball_centre_y && ball_centre_y < brick_max_y) {
                    ball->direction.x *= -1;
                }
                else {
                    ball->direction.y *= -1;
                }

                collided = true;
            }
        }
    }
}

//updates the level
void level_update(Level* level, const Uint8* keys) {
    Bouncer* bouncer = &level->bouncer;
    Ball* ball = &level->ball;

    update_player(bouncer, ball, keys);

    if (ball->moving == true)
        update_ball(level, ball, bouncer);


    // check lose condition
    if ((ball->pos.y + ball->size) > SCREEN_HEIGHT) {
        level->stop = true;
        ball->moving = false;
    }
}
