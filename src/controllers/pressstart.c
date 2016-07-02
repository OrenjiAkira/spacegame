
#include "debug.h"
#include "scene.h"
#include "sound.h"
#include "input.h"
#include "controller.h"
#include "scenes/pressstart.h"
#include "controllers/pressstart.h"

#include <stdbool.h>

/* Criamos um código pedante de mapeamento de controle usando macros */
NEW_CONTROLLER(PressStart);

static void press_any_shift() {
    Sound_playSE(FX_SELECT);
    Scene_load(SCENE_GAMEPLAY);
}

static void PressStartController_init() {
    EVENT_ASSOCIATE(press, P1_MARU, press_any_shift);
    EVENT_ASSOCIATE(press, P2_MARU, press_any_shift);
    logprint(success_msg);
}
