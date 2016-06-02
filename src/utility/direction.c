
#include "utility/vector.h"
#include "utility/direction.h"

#include <math.h>

static Vector DIRECTIONS[DIRECTION_POOL_SIZE];

void Direction_init() {
    double angle = 0.;
    int id;

    for (id = 0; id < DIRECTION_POOL_SIZE; ++id) {
        Vector_set( &DIRECTIONS[id], cos(angle), -sin(angle) );
        angle -= 2 * PI / DIRECTION_POOL_SIZE;
    }
}

Vector* Direction_getVector(int id) {
    return &DIRECTIONS[id];
}
