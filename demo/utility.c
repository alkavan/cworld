#include <stdlib.h>

#if defined(WIN32)
#define _USE_MATH_DEFINES
#endif

#include <math.h>

#include "utility.h"
#include <mathc.h>

float random_until(int range) {
    return (float)(rand() % range);
}

float random_between(int range, int min) {
    return random_until(range) + (float)(min);
}

float random_angle(int range) {
    return roundf(to_degrees(random_until(range) / 360.f * (float)M_PI * 2.f));
}
