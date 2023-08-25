#include "cworld/cworld.h"

// world operations
static void apply_force(CWorld *const t, const Vec2 force) {
    mfloat_t f[VEC2_SIZE];
    vec2(f, force.x, force.y);
    vec2_add(t->force, t->force, f);
}

// body operations
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

static Vec2 compute_force_body(CBody *const body, const Vec2 force) {
    return svec2(body->mass * force.x, body->mass * force.y);
}

void compute_force_and_torque(CBody *const body, const Vec2 force) {
    Vec2 r = svec2(body->shape.size[0]/2, body->shape.size[1]/2);
    body->torque = r.x * force.y - r.y * force.x;
}

// particle operations
static void add_particle(CWorld *const t, CParticle *const particle) {
    cvector_push_back(t->particles, *particle);
}

static void remove_particle(CWorld *const t, CParticle *const particle) {
    CParticle *it;
    int i = 0;
    for (it = cvector_begin(t->particles); it != cvector_end(t->particles); ++it) {
        if(particle == it) {
            cvector_erase(t->particles, i);
        }
        ++i;
    }
}

static Vec2 compute_force_particle(CParticle *const particle, const Vec2 force) {
    return svec2(particle->mass * force.x, particle->mass * force.y);
}

// simulation
static void simulate(CWorld *const t, float dt) {
    // particles
    for (CParticle *particle = cvector_begin(t->particles); particle != cvector_end(t->particles); ++particle) {
        Vec2 gravity = svec2(t->gravity[0], -t->gravity[1]);
        Vec2 global = svec2(t->force[0], -t->force[1]);
        Vec2 force = compute_force_particle(particle, svec2_add(gravity, global));
        Vec2 acceleration = svec2(force.x / particle->mass, force.y / particle->mass);

        mfloat_t velocity[VEC2_SIZE];
        vec2(velocity, acceleration.x * dt, acceleration.y * dt);
        vec2_add(particle->linearVelocity, particle->linearVelocity, velocity);

        mfloat_t position[VEC2_SIZE];
        vec2(position, particle->linearVelocity[0] * dt, particle->linearVelocity[1] * dt);
        vec2_add(particle->position, particle->position, position);
    }

    // bodies
    for (CBody *body = cvector_begin(t->bodies); body != cvector_end(t->bodies); ++body) {
        Vec2 gravity = svec2(t->gravity[0], -t->gravity[1]);
        Vec2 global = svec2(t->force[0], -t->force[1]);
        Vec2 force = compute_force_body(body, svec2_add(gravity, global));
        compute_force_and_torque(body, force);
        Vec2 acceleration = svec2(force.x / body->mass, force.y / body->mass);

        mfloat_t velocity[VEC2_SIZE];
        vec2(velocity, acceleration.x * dt, acceleration.y * dt);
        vec2_add(body->linearVelocity, body->linearVelocity, velocity);

        mfloat_t position[VEC2_SIZE];
        vec2(position, body->linearVelocity[0] * dt, body->linearVelocity[1] * dt);
        vec2_add(body->position, body->position, position);

        float angular_acceleration = body->torque / body->shape.inertiaMoment;
        body->angularVelocity += angular_acceleration * dt;

        vec2_rotate(body->rotation, body->rotation, to_radians(body->angularVelocity * dt));
    }

    // zero applied force
    vec2_zero(t->force);
}

CWorld *cworld_new(Vec2 gravity) {
    CWorld *world = (CWorld*) malloc(sizeof(CWorld));

    world->simulate = &simulate;
    world->apply_force = &apply_force;
    world->add_body = &add_body;
    world->remove_body = &remove_body;
    world->add_particle = &add_particle;
    world->remove_particle = &remove_particle;

    vec2(world->gravity, gravity.x, gravity.y);
    vec2(world->force, 0.0f, 0.0f);

    world->bodies = NULL;
    world->particles = NULL;

    return world;
}

void cworld_free(CWorld *t) {
    cvector_free(t->bodies);
    free(t);
}
