#ifndef CWORLD_CBODY_H
#define CWORLD_CBODY_H

#include "ctypes.h"

struct CBody {
    mfloat_t position[VEC2_SIZE];
    mfloat_t velocity[VEC2_SIZE];
    mfloat_t mass;
};

typedef struct CBody CBody;

CBody cbody(Vec2 position, Vec2 velocity, float mass);
CBody *cbody_new(Vec2 position, Vec2 velocity, float mass);
void cbody_free(CBody *t);

#endif //CWORLD_CBODY_H
