#include <SDL2/SDL_timer.h>

#include "timer.h"

static void start(Timer *const t) {
    // start the timer
    t->started = true;

    // unpause the timer
    t->paused = false;

    // get the current clock time
    t->start_ticks = SDL_GetTicks();
    t->paused_ticks = 0;
}

static void stop(Timer *const t) {
    // stop the timer
    t->started = false;

    // unpause the timer
    t->paused = false;

    // clear tick variables
    t->start_ticks = 0;
    t->paused_ticks = 0;
}

static void pause(Timer *const t) {
    // if the timer is running and isn't already paused
    if( t->started && !t->paused )
    {
        // pause the timer
        t->paused = true;

        // calculate the paused ticks
        t->paused_ticks = SDL_GetTicks() - t->start_ticks;
        t->start_ticks = 0;
    }
}

static void unpause(Timer *const t) {
    // if the timer is running and paused
    if( t->started && t->paused )
    {
        // unpause the timer
        t->paused = false;

        // reset the starting ticks
        t->start_ticks = SDL_GetTicks() - t->paused_ticks;

        // reset the paused ticks
        t->paused_ticks = 0;
    }
}

static Uint32 get_ticks(Timer *const t) {
    // actual timer time
    Uint32 time = 0;

    // if the timer is running
    if(t->started)
    {
        // if the timer is paused
        if(t->paused)
        {
            // return the number of ticks when the timer was paused
            time = t->paused_ticks;
        }
        else
        {
            // return the current time minus the start time
            time = SDL_GetTicks() - t->start_ticks;
        }
    }

    return time;
}

static bool is_started(Timer *const t) {
    // timer is running and paused or unpaused
    return t->started;
}

static bool is_paused(Timer *const t) {
    // timer is running and paused
    return t->paused && t->started;
}

Timer *timer_new() {
    Timer *timer = (Timer*) malloc(sizeof(Timer));

    timer->start = &start;
    timer->stop = &stop;
    timer->pause = &pause;
    timer->unpause = &unpause;
    timer->get_ticks = &get_ticks;
    timer->is_started = &is_started;
    timer->is_paused = &is_paused;

    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->paused = false;
    timer->started = false;

    return timer;
}

void timer_free(Timer *t) {
    free(t);
}
