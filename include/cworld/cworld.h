#ifndef CWORLD_CWORLD_H
#define CWORLD_CWORLD_H

#include "cvector.h"
#include "types.h"
#include "cbody.h"
#include "cparticle.h"

struct CWorld {
    struct {
        void (*simulate)(struct CWorld *const, float dt);
        void (*apply_force)(struct CWorld *const, const Vec2 force);
        void (*add_body)(struct CWorld *const, CBody *const body);
        void (*remove_body)(struct CWorld *const, CBody *const body);
        void (*add_particle)(struct CWorld *const, CParticle *const particle);
        void (*remove_particle)(struct CWorld *const, CParticle *const particle);
    };

    mfloat_t gravity[VEC2_SIZE];
    mfloat_t force[VEC2_SIZE];
    cvector_vector_type(CParticle) particles;
    cvector_vector_type(CBody) bodies;
};

typedef struct CWorld CWorld;

CWorld *cworld_new(Vec2 gravity);
void cworld_free(CWorld *t);

#endif //CWORLD_CWORLD_H
