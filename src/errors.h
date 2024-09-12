#pragma once

typedef unsigned char ErrorCode;
enum {
    SUCCESS = 0,
    FAILURE = -1,

    FAILURE_STD = 1 << 0,                    // 1  : marks a generic C library error
    FAILURE_MEMORY = FAILURE_STD | (1 << 1), // 3  : marks a memory related error

    // SDL ERRORS
    FAILURE_SDL = 1 << 1,                          // 2  : marks a generic SDL error
    FAILURE_SDL_INIT = FAILURE_SDL | (1 << 2),     // 6  : marks an error during SDL initialisation
    FAILURE_SDL_WINDOW = FAILURE_SDL | (1 << 3),   // 10 : marks an error with the window
    FAILURE_SDL_RENDERER = FAILURE_SDL | (1 << 4), // 18 : marks an error with the renderer
    FAILURE_SDL_AUDIO = FAILURE_SDL | (1 << 5),    // 34 : marks an error with audio

    // GAME ERRORS
    FAILURE_GAME = 1 << 2, // 4  : marks a generic game error
};

// call when a fatal error has occurred, the program will immediately terminate when called
void error(const ErrorCode error_code, const char* format, ...);
void warn(const char* format, ...);
