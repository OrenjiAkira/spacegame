
#include "game.h"
#include "input.h"
#include "action.h"
#include "factory.h"
#include "entity.h"
#include "controllers/space.h"

#include <stdlib.h>

static void keypress(int key) {
    switch (key) {
        case P1_MARU:
            Action_add(ACTION_SHOOTIT, Game_getPlayer1());
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
            Action_add(ACTION_SHOOTIT, Game_getPlayer2());
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
            Action_add(ACTION_MOVEFWD, Game_getPlayer1());
            break;
        case P1_DOWN:
            break;
        case P1_LEFT:
            if ( Game_getPlayer1() != -1 && Entity_isTimerDone(Game_getPlayer1(), TIMER_INPUTDELAY1) ) {
                Entity_addTimer(Game_getPlayer1(), TIMER_INPUTDELAY1, 0.1);
                Action_add(ACTION_TURNLFT, Game_getPlayer1());
            }
            break;
        case P1_RIGHT:
            if ( Game_getPlayer1() != -1 && Entity_isTimerDone(Game_getPlayer1(), TIMER_INPUTDELAY1) ) {
                Entity_addTimer(Game_getPlayer1(), TIMER_INPUTDELAY1, 0.1);
                Action_add(ACTION_TURNRGT, Game_getPlayer1());
            }
            break;
        case P2_MARU:
            break;
        case P2_BATSU:
            break;
        case P2_PAUSE:
            break;
        case P2_UP:
            Action_add(ACTION_MOVEFWD, Game_getPlayer2());
            break;
        case P2_DOWN:
            break;
        case P2_LEFT:
            if ( Game_getPlayer2() != -1 && Entity_isTimerDone(Game_getPlayer2(), TIMER_INPUTDELAY1) ) {
                Entity_addTimer(Game_getPlayer2(), TIMER_INPUTDELAY1, 0.1);
                Action_add(ACTION_TURNLFT, Game_getPlayer2());
            }
            break;
        case P2_RIGHT:
            if ( Game_getPlayer2() != -1 && Entity_isTimerDone(Game_getPlayer2(), TIMER_INPUTDELAY1) ) {
                Entity_addTimer(Game_getPlayer2(), TIMER_INPUTDELAY1, 0.1);
                Action_add(ACTION_TURNRGT, Game_getPlayer2());
            }
            break;
        default:
            break;
    }
}

void SpaceController_load() {
    Input_registerPress(keypress);
    Input_registerRelease(keyrelease);
    Input_registerHold(keyhold);
}
