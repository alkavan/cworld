#ifndef SDL2_C17_TIMER_H
#define SDL2_C17_TIMER_H

#include <stdbool.h>
#include <SDL2/SDL_types.h>

struct Timer {
    struct {
        void (*start)(struct Timer *const);
        void (*stop)(struct Timer *const);
        void (*pause)(struct Timer *const);
        void (*unpause)(struct Timer *const);
        Uint32 (*get_ticks)(struct Timer *const);
        bool (*is_started)(struct Timer *const);
        bool (*is_paused)(struct Timer *const);
    };

    // clock time when the timer started
    Uint32 start_ticks;

    // ticks stored when the timer was paused
    Uint32 paused_ticks;

    // timer status
    bool paused;
    bool started;
};

typedef struct Timer Timer;

Timer *timer_new();
void timer_free(Timer *t);

#endif //SDL2_C17_TIMER_H
