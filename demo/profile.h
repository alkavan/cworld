#ifndef SDL2_C17_PROFILE_H
#define SDL2_C17_PROFILE_H

#include "timer.h"

struct Profile {
    struct {
        void (*init)(struct Profile *const);
        void (*update)(struct Profile *const);
        void (*start)(struct Profile *const);
        void (*end)(struct Profile *const);
        Uint32 (*get_frame_ticks)(struct Profile *const);
    };

    Timer* fps_timer;
    Timer* cap_timer;

    float current_fps;
    Uint32 counted_frames;
    bool is_performance;

    Uint64 performance_start;
    Uint64 performance_count;
};

typedef struct Profile Profile;

Profile *profile_new(bool is_performance);
void profile_free(Profile *t);

#endif //SDL2_C17_PROFILE_H
