#include "cworld/cparticle.h"

CParticle cparticle(Vec2 position, Vec2 velocity, float mass) {
    return (CParticle){
        {position.x, position.y},
        {velocity.x, velocity.y},
        mass
    };
}

CParticle *cparticle_new(Vec2 position, Vec2 velocity, float mass) {
    CParticle *particle = (CParticle*) malloc(sizeof(CParticle));

    vec2(particle->position, position.x, position.y);
    vec2(particle->linearVelocity, velocity.x, velocity.y);
    particle->mass = mass;

    return particle;
}

void cparticle_free(CParticle *t) {
    free(t);
}
