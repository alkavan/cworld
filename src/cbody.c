#include "cbody.h"

CBody *cbody_new(Vec2 position, Vec2 velocity, float mass) {
    CBody *body = (CBody*) malloc(sizeof(CBody));

    vec2(body->position, position.x, position.y);
    vec2(body->velocity, velocity.x, velocity.y);
    body->mass = mass;

    return body;
}

CBody cbody(Vec2 position, Vec2 velocity, float mass) {
    return (CBody){{position.x, position.y}, {velocity.x, velocity.y}, mass };
}

void cbody_free(CBody *t) {
    free(t);
}
