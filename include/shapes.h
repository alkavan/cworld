#ifndef CWORLD_SHAPES_H
#define CWORLD_SHAPES_H

#include "types.h"

struct BoxShape {
    mfloat_t size[VEC2_SIZE];
    mfloat_t inertiaMoment;
};
typedef struct BoxShape BoxShape;

static inline BoxShape box_shape(Vec2 size) {
    return (BoxShape){
        {size.x, size.y},
        0.f
    };
}

#endif //CWORLD_SHAPES_H
