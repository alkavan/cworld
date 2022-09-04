#include "cbody.h"

void calc_box_inertia(BoxShape *const box_shape, float mass) {
    float m = mass;
    float w = box_shape->size[0];
    float h = box_shape->size[1];
    box_shape->inertiaMoment = m * (w * w + h * h) / 12;
}

CBody cbody(Vec2 position, Vec2 velocity, float mass, BoxShape shape, float angle) {
    calc_box_inertia(&shape, mass);
    return (CBody){
        {position.x, position.y},
        {velocity.x, velocity.y},
        mass,
        0.f,
        angle,
        0.f,
        shape,
    };
}

CBody *cbody_new(Vec2 position, Vec2 velocity, float mass, BoxShape shape, float angle) {
    CBody *body = (CBody*) malloc(sizeof(CBody));

    vec2(body->position, position.x, position.y);
    vec2(body->linearVelocity, velocity.x, velocity.y);
    body->mass = mass;
    body->angularVelocity = 0.f;
    body->angle = angle;
    body->torque = 0.f;

    calc_box_inertia(&shape, mass);
    body->shape = shape;

    return body;
}

void cbody_free(CBody *t) {
    free(t);
}
