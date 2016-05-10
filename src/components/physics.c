
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

static Queue QUEUE;

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

static void Physics_gravitate(int id) {
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

static void Physics_changedir(int id, int dir) {
    if (!PHYSICS[id].alive) return;

    PHYSICS[id].direction = (dir);
}

static void Physics_accelerate(int id) {
    Vector accvec;

    /* Verificar se o corpo está vivo */
    if (!PHYSICS[id].alive) return;

    /* Pegamos a direção normalizada e a
    multiplicamos pela aceleração escalar;
    e assim obtemos a aceleração vetorial.
    Por fim, somamos a aceleração na velocidade. */

    Vector_copy(&accvec, Direction_getVector(PHYSICS[id].direction));
    Vector_mult(&accvec, ACC);
    Vector_add(&PHYSICS[id].speed, &accvec);
}

static void Physics_kill(int id) {
    if (id < 0 || id >= PHYSICS_POOL_SIZE) {
        printf("%d not within pool range\n", id);
        return;
    }
    PHYSICS[id].active = false;
}

static void Physics_readqueue() {
    Message *msg;

    Queue_push(&QUEUE, STOP, NULL, NULL);
    while( (msg = Queue_pop(&QUEUE))->message != STOP) ) {
        switch (msg->message) {
            case PHYSICS_KILL:
                Physics_kill(msg->e->physics);
                break;
            case PHYSICS_UPDT:
                Physics_gravitate(msg->e->physics);
                break;
            case PHYSICS_CHNG:
                break;
            case PHYSICS_MOVE:
                Physics_accelerate(msg->e->physics);
                break;
            default:
                break;
        }
    }
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
    Physics_readqueue();
    for (id = 0; id < PHYSICS_POOL_SIZE; ++id) {
        if (PHYSICS[id].active) {
            Physics_slowdown(id);
            Vector_add(&PHYSICS[id].pos, &PHYSICS[id].speed);
            Physics_wraparound(id);
        }
    }
}


void Physics_print(int id) {
    printf("Body has %f units of mass and %f units of radius. It is in position:\n", PHYSICS[i].mass, PHYSICS[i].radius);
    Vector_print(&PHYSICS[i].pos);
    printf("It has speed of:\n");
    Vector_print(&PHYSICS[i].speed);
}


