
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

static void p1_nextChoice() {
    if (!P1_HAS_CHOSEN) ChooseYourCat_changeChoice(true);
}

static void p1_prevChoice() {
    if (!P1_HAS_CHOSEN) ChooseYourCat_changeChoice(false);
}

static void p2_nextChoice() {
    if (P1_HAS_CHOSEN) ChooseYourCat_changeChoice(true);
}

static void p2_prevChoice() {
    if (P1_HAS_CHOSEN) ChooseYourCat_changeChoice(false);
}

static void ChooseYourCatController_init() {
    EVENT_ASSOCIATE(press, P1_MARU, p1_confirm);
    EVENT_ASSOCIATE(press, P2_MARU, p2_confirm);

    EVENT_ASSOCIATE(press, P1_UP, p1_prevChoice);
    EVENT_ASSOCIATE(press, P1_LEFT, p1_prevChoice);
    EVENT_ASSOCIATE(press, P2_UP, p2_prevChoice);
    EVENT_ASSOCIATE(press, P2_LEFT, p2_prevChoice);

    EVENT_ASSOCIATE(press, P1_DOWN, p1_nextChoice);
    EVENT_ASSOCIATE(press, P1_RIGHT, p1_nextChoice);
    EVENT_ASSOCIATE(press, P2_DOWN, p2_nextChoice);
    EVENT_ASSOCIATE(press, P2_RIGHT, p2_nextChoice);
    logprint(success_msg);
}
