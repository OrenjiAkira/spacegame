
#include "debug.h"
#include "input.h"
#include "controller.h"
#include "scenes/chooseyourcat.h"
#include "controllers/chooseyourcat.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

NEW_CONTROLLER(ChooseYourCat);

static void p1_confirm() {
    ChooseYourCat_chooseForPlayer(false);
}

static void p2_confirm() {
    ChooseYourCat_chooseForPlayer(true);
}

static void p1_nextChoice() {
    ChooseYourCat_changeChoice(false, true);
}

static void p1_prevChoice() {
    ChooseYourCat_changeChoice(false, false);
}

static void p2_nextChoice() {
    ChooseYourCat_changeChoice(true, true);
}

static void p2_prevChoice() {
    ChooseYourCat_changeChoice(true, false);
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
