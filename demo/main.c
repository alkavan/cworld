#include <version_config.h>
#include <stdlib.h>
#include <mathc.h>
#include <time.h>

// cworld
#include <cworld/cworld.h>
#include <cworld/cbody.h>
#include <cworld/shapes.h>
#include <cworld/convert.h>

// demo
#include "config.h"
#include "app.h"
#include "draw.h"
#include "input.h"
#include "timer.h"
#include "profile.h"
#include "text.h"
#include "utility.h"


#define NUM_BODIES 10

int main()
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "loading cworld demo ...");

    // initialize random numbers
    srand(time(NULL));

    // create application object
    App* app = app_new();

    // init game application
    int init_code = app_init(app, "cworld demo", PROJECT_VERSION,
                             SCREEN_WIDTH, SCREEN_HEIGHT);

    // if application failed to load exit
    if(init_code != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create application (code: %d)", init_code);
        return init_code;
    }

    // load font
    TTF_Font* font = TTF_OpenFont("../res/Ac437_IBM_EGA_8x8.ttf", FONT_DEFAULT_SIZE);
    if ( ! font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create font (%s)", TTF_GetError());
        return EXIT_FAILURE;
    }

    // create text objects
    Text* text1 = text_new(16, 16, font);
    char text1_buffer[TEXT_BUFFER_SIZE] = "";

    Text* text2 = text_new(16, 32, font);
    char text2_buffer[TEXT_BUFFER_SIZE] = "";

    Text* text3 = text_new(16, 48, font);
    char text3_buffer[TEXT_BUFFER_SIZE] = "";

    // initialize context objects
    GameInputContext input_context = (GameInputContext) {
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {false, 0},
            {false, 0},
    };

    // create world
    CWorld *world = cworld_new(svec2(0.f, -9.81f));

    {
        BoxShape shape = box_shape(svec2(50.0f, 50.0f));
        CBody box1 = cbody(
                svec2((float)SCREEN_HALF_WIDTH, (float)SCREEN_HALF_HEIGHT),
                svec2(0, 0),
                10.0f,
                shape,
                random_angle(360)
        );

        world->add_body(world, &box1);
    }

    // create profile object
    Profile* profile = profile_new(true);

    // initialize profiler and start fps timer
    profile->init(profile);

    // delta time
    float dt;

    // render loop
    while (app->running)
    {
        // start profile session
        profile->start(profile);

        // update delta time (if fps is not zero)
        if(profile->current_fps > 0) {
            dt = 1.0f / profile->current_fps;
        }

        // handle input
        handle_input(app, &input_context);

        // calculate current fps after handling input
        profile->update(profile);

        // fps text
        sprintf(text1_buffer, "fps: %.2f (dt: %.3f)", profile->current_fps, dt);
        text1->update(text1, text1_buffer, COLOR_WHITE);

        Uint32 left_button_press_duration = input_context.mouse_left_button.pressed
                                            ? SDL_GetTicks() - input_context.mouse_left_button.press_ticks : 0;
        Uint32 right_button_press_duration = input_context.mouse_right_button.pressed
                                             ? SDL_GetTicks() - input_context.mouse_right_button.press_ticks : 0;

        sprintf(text2_buffer, "mouse (%d, %d) direction (%.2f, %.2f) left[%s, %u] right[%s, %u]",
                (int)input_context.mouse_position[0], (int)input_context.mouse_position[1],
                input_context.mouse_direction[0], input_context.mouse_direction[1],
                input_context.mouse_left_button.pressed ? "+" : "-", left_button_press_duration,
                input_context.mouse_right_button.pressed ? "+" : "-", right_button_press_duration
                );
        text2->update(text2, text2_buffer, COLOR_WHITE);

        float body0_angle = vec2_to_deg(world->bodies[0].rotation);

        sprintf(text3_buffer, "body#1"
                              " position (%.3f, %.3f)"
                              " velocity (%.3f, %.3f)"
                              " angular velocity (%.3f) angle (%.3f)",
                world->bodies[0].position[0], world->bodies[0].position[1],
                world->bodies[0].linearVelocity[0], world->bodies[0].linearVelocity[1],
                world->bodies[0].angularVelocity, body0_angle
                );
        text3->update(text3, text3_buffer, COLOR_WHITE);

        // if left mouse button pressed add world force
        if(input_context.mouse_left_button.pressed) {
            Vec2 mouse_force = svec2((float)left_button_press_duration*dt, (float)left_button_press_duration*dt);
            Vec2 mouse_direction = svec2(input_context.mouse_direction[0], -input_context.mouse_direction[1]);
            mouse_force = svec2_multiply(mouse_force, mouse_direction);
            world->apply_force(world, mouse_force);

            // create world bodies at random location range from screen center
            for (int i = 0; i < NUM_BODIES; ++i) {
                float random_x = random_between(100, SCREEN_HALF_WIDTH-50);
                float random_y = random_between(100, SCREEN_HALF_HEIGHT-50);

                CParticle particle = cparticle(svec2(random_x, random_y), svec2(0, 0), 1.0f);
                world->add_particle(world, &particle);
            }

        }

        if(dt > 0.f && dt < 0.1f) world->simulate(world, dt);

        // prepare and clear scene
        prepare_scene(app->renderer);

        draw_debug_line(app->renderer, COLOR_GREEN,
                        svec2(input_context.mouse_position[0], input_context.mouse_position[1]),
                        svec2((float)SCREEN_HALF_WIDTH, (float)SCREEN_HALF_HEIGHT));

        for (CParticle *particle = cvector_begin(world->particles); particle != cvector_end(world->particles); ++particle) {
            draw_debug_point(app->renderer,COLOR_RED,
                             svec2(particle->position[0], particle->position[1]));
        }

        for (CBody *body = cvector_begin(world->bodies); body != cvector_end(world->bodies); ++body) {
            Vec2 offset = svec2(body->shape.size[0]/2, body->shape.size[1]/2);

            draw_debug_rect(
                    app->renderer,
                    COLOR_BLUE,
                    svec2_subtract(svec2(body->position[0], body->position[1]), offset),
                    svec2(body->shape.size[0], body->shape.size[1]),
                    body0_angle
                    );
        }

        // render texts
        text1->render(text1, app->renderer);
        text2->render(text2, app->renderer);
        text3->render(text3, app->renderer);

        // present scene
        present_scene(app->renderer);

        // finish profile session
        profile->end(profile);

        // if frame finished early
        Uint32 frame_ticks = profile->get_frame_ticks(profile);
        if(frame_ticks < SCREEN_TICKS_PER_FRAME)
        {
            // wait remaining time
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
    }

    // clean up
    profile_free(profile);

    app_quit(app);

    return EXIT_SUCCESS;
}
