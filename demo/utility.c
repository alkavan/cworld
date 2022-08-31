#include <stdlib.h>
#include "utility.h"

float random_until(long range) {
    return (float)(random() % range);
}

float random_between(long range, long min) {
    return random_until(range) + (float)(min);
}
