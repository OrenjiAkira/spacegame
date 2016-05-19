
#include "utility/vector.h"

#include <stdio.h>
#include <float.h>
#include <math.h>

void Vector_set(Vector *v, float x, float y) {
    v->x = x;
    v->y = y;
}

void Vector_copy(Vector *v, Vector *w) {
    v->x = w->x;
    v->y = w->y;
}

void Vector_add(Vector *v, Vector *w) {
    v->x += w->x;
    v->y += w->y;
}

void Vector_sub(Vector *v, Vector *w) {
    v->x -= w->x;
    v->y -= w->y;
}

void Vector_mult(Vector *v, float p) {
    v->x *= p;
    v->y *= p;
}

void Vector_magnitude(Vector *v, float mag) {
    float sqrlen = Vector_get_sqrlen(v);
    if (sqrlen < FLT_EPSILON) return;

    /* Normaliza e multiplica */
    Vector_mult( v, 1/sqrt(sqrlen) );
    Vector_mult( v, mag );
}

void Vector_print(Vector *v) {
    printf("[ %f, %f ]\n", v->x, v->y);
}

float Vector_get_sqrlen(Vector *v) {
    return (v->x * v->x) + (v->y * v->y);
}


