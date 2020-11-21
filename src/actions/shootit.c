
#include "entity.h"
#include "action.h"
#include "sound.h"
#include "config/conf.h"
#include "components/physics.h"
#include "actions/shootit.h"
#include "scenes/gameplay.h"

#include "utility/bool.h"
#include <stdlib.h>

static float MASS = 0, RADIUS = 0, LIFETIME = 0;
static bool isSet = false;

static void load_bullet_values() {
    Conf_getBulletValues(&MASS, &RADIUS, &LIFETIME);
    isSet = true;
}

void ShootIt(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_SHOOTIT);
        if (!isSet) load_bullet_values();
        Sound_playSE(FX_SHOOT);
        GamePlay_newBullet(entity->physics, MASS, RADIUS, LIFETIME);
        Action_remove(ACTION_SHOOTIT, POOL[i]);
    }
}
