
#include "debug.h"
#include "input.h"
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
        ChooseYourCat_chooseForPlayer(true);
        P1_HAS_CHOSEN = true;
    }
}

static void p2_confirm() {
    if (P1_HAS_CHOSEN) {
        /* code */
        ChooseYourCat_chooseForPlayer(false);
    }
}

static void nextChoice() {
    ChooseYourCat_changeChoice(true);
}

static void prevChoice() {
    ChooseYourCat_changeChoice(false);
}

static void ChooseYourCatController_init() {
    EVENT_ASSOCIATE(press, P1_MARU, p1_confirm);
    EVENT_ASSOCIATE(press, P2_MARU, p2_confirm);

    EVENT_ASSOCIATE(press, P1_UP, prevChoice);
    EVENT_ASSOCIATE(press, P1_LEFT, prevChoice);
    EVENT_ASSOCIATE(press, P2_UP, prevChoice);
    EVENT_ASSOCIATE(press, P2_LEFT, prevChoice);

    EVENT_ASSOCIATE(press, P1_DOWN, nextChoice);
    EVENT_ASSOCIATE(press, P1_RIGHT, nextChoice);
    EVENT_ASSOCIATE(press, P2_DOWN, nextChoice);
    EVENT_ASSOCIATE(press, P2_RIGHT, nextChoice);
    logprint(success_msg);
}
