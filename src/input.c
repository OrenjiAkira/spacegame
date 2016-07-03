
#include "debug.h"
#include "game.h"
#include "input.h"
#include "action.h"

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

static SDL_Event e;

static InputController *CURRENT_CONTROLLER;
static bool isHeld[KEYMAP_SIZE];

static InputController __noController__;
static void __null_keyevent__(int key) {}

static int keyRead(SDL_Keycode key) {
    switch (key) {
        case SDLK_RSHIFT:
            return P2_MARU;
            break;
        case SDLK_RALT:
            return P2_BATSU;
            break;
        case SDLK_p:
            return P2_PAUSE;
            break;
        case SDLK_UP:
            return P2_UP;
            break;
        case SDLK_DOWN:
            return P2_DOWN;
            break;
        case SDLK_LEFT:
            return P2_LEFT;
            break;
        case SDLK_RIGHT:
            return P2_RIGHT;
            break;
        case SDLK_LSHIFT:
            return P1_MARU;
            break;
        case SDLK_LALT:
            return P1_BATSU;
            break;
        case SDLK_ESCAPE:
            return P1_PAUSE;
            break;
        case SDLK_w:
            return P1_UP;
            break;
        case SDLK_s:
            return P1_DOWN;
            break;
        case SDLK_a:
            return P1_LEFT;
            break;
        case SDLK_d:
            return P1_RIGHT;
            break;
        default:
            return DEFAULT;
            break;
    }
}

void Input_init() {
    __noController__.keyPressed = __null_keyevent__;
    __noController__.keyReleased = __null_keyevent__;
    __noController__.keyHeld = __null_keyevent__;
    Input_loadSceneController(&__noController__);
    logprint("Empty controller loaded for security.\n");
}

void Input_update() {
    int key;

    while( SDL_PollEvent( &e ) != 0 )
        if (e.type == SDL_QUIT) {
            logprint("\t> Game quit by input\n");
            Game_quit();
        } else if (e.type == SDL_KEYDOWN) {
            key = keyRead(e.key.keysym.sym);
            CURRENT_CONTROLLER->keyPressed(key);
            isHeld[key] = true;
        } else if (e.type == SDL_KEYUP) {
            key = keyRead(e.key.keysym.sym);
            CURRENT_CONTROLLER->keyReleased(key);
            isHeld[key] = false;
        }

    for (key = 0; key < KEYMAP_SIZE; ++key)
        if (isHeld[key]) CURRENT_CONTROLLER->keyHeld(key);
}

void Input_unloadSceneController() {
    CURRENT_CONTROLLER = &__noController__;
}

void Input_loadSceneController(InputController *controller) {
    CURRENT_CONTROLLER = controller;
}
