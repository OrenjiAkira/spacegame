
#include "input.h"
#include "action.h"
#include "entity.h"
#include "scenes/gameplay.h"
#include "controllers/gameplay.h"

#include <stdio.h>
#include <stdlib.h>

static void keypress(int key) {
    switch (key) {
        case P1_MARU:
            printf("\n\n[ PLAYER1: %d ]\\n", GamePlay_getPlayer1());
            Action_add(ACTION_SHOOTIT, GamePlay_getPlayer1());
            break;
        case P1_BATSU:
            break;
        case P1_PAUSE:
            break;
        case P1_UP:
            break;
        case P1_DOWN:
            break;
        case P1_LEFT:
            break;
        case P1_RIGHT:
            break;
        case P2_MARU:
            printf("\n\n[ PLAYER2: %d ]\\n", GamePlay_getPlayer2());
            Action_add(ACTION_SHOOTIT, GamePlay_getPlayer2());
            break;
        case P2_BATSU:
            break;
        case P2_PAUSE:
            break;
        case P2_UP:
            break;
        case P2_DOWN:
            break;
        case P2_LEFT:
            break;
        case P2_RIGHT:
            break;
        default:
            break;
    }
}

static void keyrelease(int key) {
}

static void keyhold(int key) {
    switch (key) {
        case P1_MARU:
            break;
        case P1_BATSU:
            break;
        case P1_PAUSE:
            break;
        case P1_UP:
            Action_add(ACTION_MOVEFWD, GamePlay_getPlayer1());
            break;
        case P1_DOWN:
            break;
        case P1_LEFT:
            if ( GamePlay_getPlayer1() != -1 && Entity_isTimerDone(GamePlay_getPlayer1(), TIMER_INPUTDELAY1) ) {
                Entity_addTimer(GamePlay_getPlayer1(), TIMER_INPUTDELAY1, 0.1);
                Action_add(ACTION_TURNLFT, GamePlay_getPlayer1());
            }
            break;
        case P1_RIGHT:
            if ( GamePlay_getPlayer1() != -1 && Entity_isTimerDone(GamePlay_getPlayer1(), TIMER_INPUTDELAY1) ) {
                Entity_addTimer(GamePlay_getPlayer1(), TIMER_INPUTDELAY1, 0.1);
                Action_add(ACTION_TURNRGT, GamePlay_getPlayer1());
            }
            break;
        case P2_MARU:
            break;
        case P2_BATSU:
            break;
        case P2_PAUSE:
            break;
        case P2_UP:
            Action_add(ACTION_MOVEFWD, GamePlay_getPlayer2());
            break;
        case P2_DOWN:
            break;
        case P2_LEFT:
            if ( GamePlay_getPlayer2() != -1 && Entity_isTimerDone(GamePlay_getPlayer2(), TIMER_INPUTDELAY1) ) {
                Entity_addTimer(GamePlay_getPlayer2(), TIMER_INPUTDELAY1, 0.1);
                Action_add(ACTION_TURNLFT, GamePlay_getPlayer2());
            }
            break;
        case P2_RIGHT:
            if ( GamePlay_getPlayer2() != -1 && Entity_isTimerDone(GamePlay_getPlayer2(), TIMER_INPUTDELAY1) ) {
                Entity_addTimer(GamePlay_getPlayer2(), TIMER_INPUTDELAY1, 0.1);
                Action_add(ACTION_TURNRGT, GamePlay_getPlayer2());
            }
            break;
        default:
            break;
    }
}

void GamePlayController_load() {
    Input_registerPress(keypress);
    Input_registerRelease(keyrelease);
    Input_registerHold(keyhold);
}
