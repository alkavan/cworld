#include "cworld/cbody.h"
#include "cworld/convert.h"

void calc_box_inertia(BoxShape *const box_shape, float mass) {
    float m = mass;
    float w = box_shape->size[0];
    float h = box_shape->size[1];
    box_shape->inertiaMoment = m * (w * w + h * h) / 12;
}

CBody cbody(Vec2 position, Vec2 velocity, float mass, BoxShape shape, float angle) {
    calc_box_inertia(&shape, mass);

    Mat2 rotation = smat2_rotation_z(to_radians(angle));

    return (CBody){
        {position.x, position.y},
        {velocity.x, velocity.y},
        mass,
        {rotation.m11, rotation.m21},
        0.f,
        0.f,
        shape,
    };
}

CBody *cbody_new(Vec2 position, Vec2 velocity, float mass, BoxShape shape, float angle) {
    CBody *body = (CBody*) malloc(sizeof(CBody));

    vec2(body->position, position.x, position.y);
    vec2(body->linearVelocity, velocity.x, velocity.y);
    body->mass = mass;

    Mat2 rotation = smat2_rotation_z(to_radians(angle));
    vec2(body->rotation, rotation.m11, rotation.m21);

    body->angularVelocity = 0.f;
    body->torque = 0.f;

    calc_box_inertia(&shape, mass);
    body->shape = shape;

    return body;
}

void cbody_free(CBody *t) {
    free(t);
}
