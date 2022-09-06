#include "input.h"
#include "types.h"
#include "config.h"

void handle_input(App *app, GameInputContext *context)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                app->running = false;
                break;
            default:
                break;
        }

        if(event.type == SDL_MOUSEMOTION) {
            vec2(context->mouse_position, event.motion.x, event.motion.y);

            mfloat_t center[VEC2_SIZE];
            vec2(center,(float)SCREEN_HALF_WIDTH, (float)SCREEN_HALF_HEIGHT);

            mfloat_t direction[VEC2_SIZE];
            vec2_subtract(direction, context->mouse_position, center);
            context->mouse_length = vec2_length(direction);
            context->mouse_length_squared = vec2_length_squared(direction);
            vec2_normalize(context->mouse_direction, direction);
        }

        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if(event.button.button == SDL_BUTTON_LEFT) {
                context->mouse_left_button.pressed = true;
                context->mouse_left_button.press_ticks = SDL_GetTicks();
            }
            if(event.button.button == SDL_BUTTON_RIGHT) {
                context->mouse_right_button.pressed = true;
                context->mouse_right_button.press_ticks = SDL_GetTicks();
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP) {
            if(event.button.button == SDL_BUTTON_LEFT) {
                context->mouse_left_button.pressed = false;
                context->mouse_left_button.press_ticks = 0;
            }
            if(event.button.button == SDL_BUTTON_RIGHT) {
                context->mouse_right_button.pressed = false;
                context->mouse_right_button.press_ticks = 0;
            }
        }

        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE: {
                    app->running = false;
                    break;
                }
                default:
                    break;
            }
        }
    }
}
