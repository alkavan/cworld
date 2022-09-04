#ifndef CWORLD_CBODY_H
#define CWORLD_CBODY_H

#include "types.h"
#include "shapes.h"

struct CBody {
    mfloat_t position[VEC2_SIZE];
    mfloat_t linearVelocity[VEC2_SIZE];
    mfloat_t mass;
    mfloat_t angularVelocity;
    mfloat_t angle;
    mfloat_t torque;
    BoxShape shape;
};
typedef struct CBody CBody;

CBody cbody(Vec2 position, Vec2 velocity, float mass, BoxShape shape, float angle);
CBody *cbody_new(Vec2 position, Vec2 velocity, float mass, BoxShape shape, float angle);
void cbody_free(CBody *t);

#endif //CWORLD_CBODY_H
