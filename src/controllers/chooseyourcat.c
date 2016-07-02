
#include "debug.h"
#include "input.h"
#include "scene.h"
#include "sound.h"
#include "controller.h"
#include "controllers/chooseyourcat.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

NEW_CONTROLLER(ChooseYourCat);

static void p1_confirm() {
    Sound_playSE(FX_SELECT);
    Scene_load(SCENE_PRESSSTART);
}

static void p2_confirm() {
    Sound_playSE(FX_SELECT);
    Scene_load(SCENE_PRESSSTART);
}

static void ChooseYourCatController_init() {
    EVENT_ASSOCIATE(press, P1_MARU, p1_confirm);
    EVENT_ASSOCIATE(press, P2_MARU, p2_confirm);
    logprint(success_msg);
}
