#include "convert.h"

/**
 * Convert 2d vector to degrees
 *
 * @param v
 * @return
 */
mfloat_t vec2_to_deg(mfloat_t *v) {
    return to_degrees(vec2_angle(v));
}


/**
 * Convert 2d vector to degrees
 *
 * @param v
 * @return
 */
mfloat_t svec2_to_deg(Vec2 v) {
    return to_degrees(svec2_angle(v));
}

/**
 * Convert 2d matrix to degrees
 *
 * @param m
 * @return
 */
mfloat_t mat2_to_deg(mfloat_t *m) {
    mfloat_t v[VEC2_SIZE];
    vec2(v, m[0], m[1]);
    return to_degrees(vec2_angle(v));
}


/**
 * Convert 2d matrix to degrees
 *
 * @param m
 * @return
 */
mfloat_t smat2_to_deg(Mat2 m) {
    return to_degrees(svec2_angle(svec2(m.m11, m.m12)));
}
