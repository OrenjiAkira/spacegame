
#include "debug.h"
#include "input.h"
#include "scene.h"
#include "sound.h"
#include "controller.h"
#include "scenes/chooseyourcat.h"
#include "controllers/chooseyourcat.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int P1_HAS_CHOSEN = false;
/*  false -> P1 escolhe o gato;
    true -> P2 escolhe o gato. */

NEW_CONTROLLER(ChooseYourCat);

static void p1_confirm() {
    if (!P1_HAS_CHOSEN) {
        Sound_playSE(FX_MARU);
        P1_HAS_CHOSEN = true;
    }
}

static void p2_confirm() {
    if (P1_HAS_CHOSEN) {
        /* code */
        Sound_playSE(FX_MARU);
        Scene_close();
        Scene_load(SCENE_PRESSSTART);
    }
}

static void ChooseYourCatController_init() {
    EVENT_ASSOCIATE(press, P1_MARU, p1_confirm);
    EVENT_ASSOCIATE(press, P2_MARU, p2_confirm);
    logprint(success_msg);
}
