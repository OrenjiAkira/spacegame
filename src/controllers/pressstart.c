
#include "debug.h"
#include "sound.h"
#include "input.h"
#include "scenes/gameplay.h"
#include "scenes/pressstart.h"
#include "controllers/pressstart.h"

static InputController controller;

static void keypress(int key) {
    switch (key) {
        case P1_MARU:
            Sound_playSE(FX_SELECT);
            PressStart_close();
            GamePlay_load();
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
            Sound_playSE(FX_SELECT);
            PressStart_close();
            GamePlay_load();
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
}

void PressStartController_load() {
    controller.keyPressed = keypress;
    controller.keyReleased = keyrelease;
    controller.keyHeld = keyhold;
    logprint("Stacking press start scene...\n");
    Input_loadSceneController(&controller);
}
