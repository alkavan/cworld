#include <SDL2/SDL_timer.h>
#include "profile.h"

#define MAX_FPS_VALUE 2000000.0f

static void init(struct Profile *const t) {
    t->fps_timer->start(t->fps_timer);
    t->counted_frames = 0;
}

static void start(struct Profile *const t) {
    t->cap_timer->start(t->cap_timer);
    if(t->is_performance) {
        t->performance_start = SDL_GetPerformanceCounter();
    }
}

static void end(struct Profile *const t) {
    ++t->counted_frames;

    if(t->is_performance) {
        t->performance_count = SDL_GetPerformanceCounter() - t->performance_start;
    }
}

static void update(struct Profile *const t) {
    // calculate and correct fps
    t->current_fps = (float)t->counted_frames / ((float)t->fps_timer->get_ticks(t->fps_timer) / 1000.f );

    if(t->current_fps > MAX_FPS_VALUE)
    {
        t->current_fps = 0;
    }
}

Uint32 get_frame_ticks(struct Profile *const t) {
    return t->cap_timer->get_ticks(t->cap_timer);
}

Profile *profile_new(bool is_performance) {
    Profile *profile = (Profile*) malloc(sizeof(Profile));

    profile->init = &init;
    profile->start = &start;
    profile->end = &end;
    profile->update = &update;
    profile->get_frame_ticks = &get_frame_ticks;

    // frames per second timer
    profile->fps_timer = timer_new();

    // frames per second cap timer
    profile->cap_timer = timer_new();

    // some initial values
    profile->current_fps = 0.0f;
    profile->counted_frames = 0;

    profile->is_performance = is_performance;
    profile->performance_start = 0;
    profile->performance_count = 0;

    return profile;
}

void profile_free(Profile *t) {
    free(t);
}
