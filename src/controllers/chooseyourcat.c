
#include "debug.h"
#include "input.h"
#include "controller.h"
#include "scenes/chooseyourcat.h"
#include "controllers/chooseyourcat.h"

#include <stdio.h>
#include <stdlib.h>
#include "utility/bool.h"

NEW_CONTROLLER(ChooseYourCat);

static void p1_confirm() {
    ChooseYourCat_chooseForPlayer(false);
}

static void p2_confirm() {
    ChooseYourCat_chooseForPlayer(true);
}

static void p1_up() {
    ChooseYourCat_changeChoice(false, DIR_UP);
}
static void p1_right() {
    ChooseYourCat_changeChoice(false, DIR_RIGHT);
}
static void p1_down() {
    ChooseYourCat_changeChoice(false, DIR_DOWN);
}
static void p1_left() {
    ChooseYourCat_changeChoice(false, DIR_LEFT);
}

static void p2_up() {
    ChooseYourCat_changeChoice(true, DIR_UP);
}
static void p2_right() {
    ChooseYourCat_changeChoice(true, DIR_RIGHT);
}
static void p2_down() {
    ChooseYourCat_changeChoice(true, DIR_DOWN);
}
static void p2_left() {
    ChooseYourCat_changeChoice(true, DIR_LEFT);
}

static void ChooseYourCatController_init() {
    EVENT_ASSOCIATE(press, P1_MARU, p1_confirm);
    EVENT_ASSOCIATE(press, P2_MARU, p2_confirm);

    EVENT_ASSOCIATE(press, P1_UP, p1_up);
    EVENT_ASSOCIATE(press, P1_RIGHT, p1_right);
    EVENT_ASSOCIATE(press, P1_DOWN, p1_down);
    EVENT_ASSOCIATE(press, P1_LEFT, p1_left);

    EVENT_ASSOCIATE(press, P2_UP, p2_up);
    EVENT_ASSOCIATE(press, P2_RIGHT, p2_right);
    EVENT_ASSOCIATE(press, P2_DOWN, p2_down);
    EVENT_ASSOCIATE(press, P2_LEFT, p2_left);
    logprint(success_msg);
}
