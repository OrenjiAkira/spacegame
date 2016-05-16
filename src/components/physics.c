
#include "utility/macros.h"
#include "utility/messages.h"
#include "utility/queue.h"
#include "utility/vector.h"
#include "utility/direction.h"
#include "components/physics.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

struct _physics {
    Vector pos;
    Vector speed;
    float mass;
    float radius;
    int direction;
    bool active;
};

static Physics PHYSICS[PHYSICS_POOL_SIZE];

static void Physics_wraparound(int id) {
    while (PHYSICS[id].pos.x > MAP_WIDTH/2)
        PHYSICS[id].pos.x -= MAP_WIDTH;
    while (PHYSICS[id].pos.x < -MAP_WIDTH/2)
        PHYSICS[id].pos.x += MAP_WIDTH;
    while (PHYSICS[id].pos.y > MAP_HEIGHT/2)
        PHYSICS[id].pos.y -= MAP_HEIGHT;
    while (PHYSICS[id].pos.y < -MAP_HEIGHT/2)
        PHYSICS[id].pos.y += MAP_HEIGHT;
}

static void Physics_slowdown(int id) {
    if ( Vector_get_sqrlen(&PHYSICS[id].speed) > SPEEDLIMIT*SPEEDLIMIT )
        Vector_magnitude(&PHYSICS[id].speed, SPEEDLIMIT);
}

void Physics_init() {
    int id;
    for (id = 0; id < PHYSICS_POOL_SIZE; ++id)
        PHYSICS[id].active = false;
}

int Physics_new(float m, float r, float x, float y, float vx, float vy) {
    int id;
    for (id = 0; id < PHYSICS_POOL_SIZE; ++id) {
        if (!PHYSICS[id].active) {
            Vector_set(&PHYSICS[id].pos, x, y);
            Vector_set(&PHYSICS[id].speed, vx, vy);
            PHYSICS[id].mass = m;
            PHYSICS[id].radius = r;
            PHYSICS[id].active = true;
            return id;
        }
    }
    pool_overflow(Physics);
}

void Physics_update() {
    int id;
    for (id = 0; id < PHYSICS_POOL_SIZE; ++id) {
        if (PHYSICS[id].active) {
            Physics_slowdown(id);
            Vector_add(&PHYSICS[id].pos, &PHYSICS[id].speed);
            Physics_wraparound(id);
        }
    }
}

Vector* Physics_getPos(int id) {
    return (PHYSICS[id].active ? &PHYSICS[id].pos : NULL);
}

void Physics_kill(int id) {
    if (id < 0 || id >= PHYSICS_POOL_SIZE) {
        printf("%d not within pool range\n", id);
        return;
    }
    PHYSICS[id].active = false;
}

void Physics_gravitate(int id) {
    Vector accvec;
    float acc;
    int jd;
    
    for (jd = 0; jd < PHYSICS_POOL_SIZE; ++jd) {
        /* Iteramos por todos os elementos físicos. */
        if (jd != id && PHYSICS[jd].alive) {

            /* Adquirindo vetor distância */
            Vector_copy(&accvec, &PHYSICS[jd].pos);
            Vector_sub(&accvec, &PHYSICS[id].pos);

            /* Verificando plano toroidal */
            if (fabs(accvec.x) > MAP_WIDTH/2)
                accvec.x = MAP_WIDTH - accvec.x;
            if (fabs(accvec.y) > MAP_HEIGHT/2)
                accvec.y = MAP_HEIGHT - accvec.y;
                
            /* Calculando aceleração:
            F = R = acc * mass_a = (mass_a * mass_b * GCONST / dist^2)
            => acc = F/mass_a
            => acc = (mass_a * mass_b * GCONST / dist^2) / mass_a
            => acc = mass_b * GCONST / dist^2 */
            acc = PHYSICS[jd].mass * GCONST / Vector_get_sqrlen(&accvec);
            Vector_magnitude(&accvec, acc);
            Vector_add(&PHYSICS[id].speed, &accvec);
        }
    }
}

void Physics_accelerate(int id) {
    Vector accvec;

    /* Verificar se o corpo está vivo */
    if (!PHYSICS[id].alive) return;

    Vector_copy(&accvec, Direction_getVector(PHYSICS[id].direction));
    Vector_mult(&accvec, ACC);
    Vector_add(&PHYSICS[id].speed, &accvec);
}

void Physics_changedir(int id, int dir) {
    if (!PHYSICS[id].alive) return;

    PHYSICS[id].direction = (dir);
}

void Physics_print(int id) {
    printf("Body has %f units of mass and %f units of radius. It is in position:\n", PHYSICS[id].mass, PHYSICS[id].radius);
    Vector_print(&PHYSICS[id].pos);
    printf("It has speed of:\n");
    Vector_print(&PHYSICS[id].speed);
}


