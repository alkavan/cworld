#include "cworld.h"

static void apply_force(CWorld *const t, const Vec2 force) {
    mfloat_t f[VEC2_SIZE];
    vec2(f, force.x, force.y);
    vec2_add(t->force, t->force, f);
}

static Vec2 compute_force(CBody *const body, const Vec2 force) {
    return svec2(body->mass * force.x, body->mass * force.y);
}

static void simulate(CWorld *const t, float dt) {
    for (CBody *body = cvector_begin(t->bodies); body != cvector_end(t->bodies); ++body) {
        Vec2 gravity = svec2(t->gravity[0], -t->gravity[1]);
        Vec2 global = svec2(t->force[0], -t->force[1]);
        Vec2 force = compute_force(body, svec2_add(gravity, global));
        Vec2 acceleration = svec2(force.x / body->mass, force.y / body->mass);

        mfloat_t velocity[VEC2_SIZE];
        vec2(velocity, acceleration.x * dt, acceleration.y * dt);
        vec2_add(body->velocity, body->velocity, velocity);

        mfloat_t position[VEC2_SIZE];
        vec2(position, body->velocity[0] * dt, body->velocity[1] * dt);
        vec2_add(body->position, body->position, position);
    }

    // zero applied force
    vec2_zero(t->force);
}

static void add_body(CWorld *const t, CBody *const body) {
    cvector_push_back(t->bodies, *body);
}

static void remove_body(CWorld *const t, CBody *const body) {
    CBody *it;
    int i = 0;
    for (it = cvector_begin(t->bodies); it != cvector_end(t->bodies); ++it) {
        if(body == it) {
            cvector_erase(t->bodies, i);
        }
        ++i;
    }
}

CWorld *cworld_new(Vec2 gravity) {
    CWorld *world = (CWorld*) malloc(sizeof(CWorld));

    world->simulate = &simulate;
    world->apply_force = &apply_force;
    world->add_body = &add_body;
    world->remove_body = &remove_body;

    vec2(world->gravity, gravity.x, gravity.y);
    vec2(world->force, 0.0f, 0.0f);

    world->bodies = NULL;

    return world;
}

void cworld_free(CWorld *t) {
    cvector_free(t->bodies);
    free(t);
}
