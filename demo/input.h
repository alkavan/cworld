#ifndef SDL2_C17_INPUT_H
#define SDL2_C17_INPUT_H

#include <SDL2/SDL.h>
#include <cworld/types.h>

#include "app.h"

struct MouseButton {
    bool pressed;
    Uint32 press_ticks;
};
typedef struct MouseButton MouseButton;

struct GameInputContext {
    mfloat_t mouse_position[VEC2_SIZE];
    mfloat_t mouse_direction[VEC2_SIZE];
    MouseButton mouse_left_button;
    MouseButton mouse_right_button;
};
typedef struct GameInputContext GameInputContext;

void handle_input(App *app, GameInputContext *context);

#endif //SDL2_C17_INPUT_H
