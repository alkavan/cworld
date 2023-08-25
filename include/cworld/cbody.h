#ifndef CWORLD_CBODY_H
#define CWORLD_CBODY_H

#include "types.h"
#include "shapes.h"

typedef enum {
    BodyStatic = 0,
    BodyDynamic = 1,
} BodyType;

struct CBody {
    mfloat_t position[VEC2_SIZE];
    mfloat_t linearVelocity[VEC2_SIZE];
    mfloat_t mass;
    mfloat_t rotation[VEC2_SIZE];
    mfloat_t angularVelocity;
    mfloat_t torque;
    BoxShape shape;
    BodyType type;
};

typedef struct CBody CBody;

CBody cbody(BodyType type, Vec2 position, Vec2 velocity, float mass, BoxShape shape, float angle);
CBody *cbody_new(BodyType type, Vec2 position, Vec2 velocity, float mass, BoxShape shape, float angle);
void cbody_free(CBody *t);

void cbody_set_type(CBody *body, BodyType type);

#endif //CWORLD_CBODY_H
