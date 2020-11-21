
#include "input.h"
#include "action.h"
#include "entity.h"
#include "controller.h"
#include "scenes/gameplay.h"
#include "controllers/gameplay.h"

#include <stdio.h>
#include <stdlib.h>
#include "utility/bool.h"

/* Criamos um código pedante de mapeamento de controle usando macros */
NEW_CONTROLLER(GamePlay);

static void p1_shoot() {
    Action_add(ACTION_SHOOTIT, GamePlay_getPlayer1());
}

static void p1_gofwd() {
    Action_add(ACTION_MOVEFWD, GamePlay_getPlayer1());
}

static void p1_turnleft() {
    if ( GamePlay_getPlayer1() != -1 && Entity_isTimerDone(GamePlay_getPlayer1(), TIMER_INPUTDELAY1) ) {
        Entity_addTimer(GamePlay_getPlayer1(), TIMER_INPUTDELAY1, 0.1);
        Action_add(ACTION_TURNLFT, GamePlay_getPlayer1());
    }
}

static void p1_turnright() {
    if ( GamePlay_getPlayer1() != -1 && Entity_isTimerDone(GamePlay_getPlayer1(), TIMER_INPUTDELAY1) ) {
        Entity_addTimer(GamePlay_getPlayer1(), TIMER_INPUTDELAY1, 0.1);
        Action_add(ACTION_TURNRGT, GamePlay_getPlayer1());
    }
}

static void p2_shoot() {
    Action_add(ACTION_SHOOTIT, GamePlay_getPlayer2());
}

static void p2_gofwd() {
    Action_add(ACTION_MOVEFWD, GamePlay_getPlayer2());
}

static void p2_turnleft() {
    if ( GamePlay_getPlayer2() != -1 && Entity_isTimerDone(GamePlay_getPlayer2(), TIMER_INPUTDELAY1) ) {
        Entity_addTimer(GamePlay_getPlayer2(), TIMER_INPUTDELAY1, 0.1);
        Action_add(ACTION_TURNLFT, GamePlay_getPlayer2());
    }
}

static void p2_turnright() {
    if ( GamePlay_getPlayer2() != -1 && Entity_isTimerDone(GamePlay_getPlayer2(), TIMER_INPUTDELAY1) ) {
        Entity_addTimer(GamePlay_getPlayer2(), TIMER_INPUTDELAY1, 0.1);
        Action_add(ACTION_TURNRGT, GamePlay_getPlayer2());
    }
}

static void GamePlayController_init() {
    EVENT_ASSOCIATE(press, P1_MARU, p1_shoot);
    EVENT_ASSOCIATE(press, P2_MARU, p2_shoot);
    EVENT_ASSOCIATE(hold, P1_UP, p1_gofwd);
    EVENT_ASSOCIATE(hold, P1_LEFT, p1_turnleft);
    EVENT_ASSOCIATE(hold, P1_RIGHT, p1_turnright);
    EVENT_ASSOCIATE(hold, P2_UP, p2_gofwd);
    EVENT_ASSOCIATE(hold, P2_LEFT, p2_turnleft);
    EVENT_ASSOCIATE(hold, P2_RIGHT, p2_turnright);
    logprint(success_msg);
}
