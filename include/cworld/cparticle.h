#ifndef CWORLD_CPARTICLE_H
#define CWORLD_CPARTICLE_H

#include "types.h"

struct CParticle {
    mfloat_t position[VEC2_SIZE];
    mfloat_t linearVelocity[VEC2_SIZE];
    mfloat_t mass;
};
typedef struct CParticle CParticle;

CParticle cparticle(Vec2 position, Vec2 velocity, float mass);
CParticle *cparticle_new(Vec2 position, Vec2 velocity, float mass);
void cparticle_free(CParticle *t);

#endif //CWORLD_CPARTICLE_H
