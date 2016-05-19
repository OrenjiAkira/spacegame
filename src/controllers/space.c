
#include "game.h"
#include "input.h"
#include "entities/ship.h"
#include "controllers/space.h"

static int P1, P2;

static void keypress(int key) {

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
            Ship_accelerate(P1);
            break;
        case P1_DOWN:
            break;
        case P1_LEFT:
            Ship_turnLeft(P1);
            break;
        case P1_RIGHT:
            Ship_turnRight(P1);
            break;
        case P2_MARU:
            break;
        case P2_BATSU:
            break;
        case P2_PAUSE:
            break;
        case P2_UP:
            Ship_accelerate(P2);
            break;
        case P2_DOWN:
            break;
        case P2_LEFT:
            Ship_turnLeft(P2);
            break;
        case P2_RIGHT:
            Ship_turnRight(P2);
            break;
        default:
            break;
    }
}

void SpaceController_load() {
    P1 = Game_getPlayer1();
    P2 = Game_getPlayer2();
    Input_registerPress(keypress);
    Input_registerRelease(keyrelease);
    Input_registerHold(keyhold);
}
