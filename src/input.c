
#include "debug.h"
#include "game.h"
#include "input.h"
#include "action.h"

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

static SDL_Event e;

static bool isHeld[KEYMAP_SIZE];

static InputController *SCENE_CONTROLLER[MAX_SCENE_DEPTH];
static int SCENE_DEPTH = -1; /* -1 significa que não está nenhuma cena carregada */

static InputController __noController;
static void __nothing(int key) {}

static int keyRead(SDL_Keycode key) {
    switch (key) {
        case SDLK_RSHIFT:
            return P1_MARU;
            break;
        case SDLK_RALT:
            return P1_BATSU;
            break;
        case SDLK_p:
            return P1_PAUSE;
            break;
        case SDLK_UP:
            return P1_UP;
            break;
        case SDLK_DOWN:
            return P1_DOWN;
            break;
        case SDLK_LEFT:
            return P1_LEFT;
            break;
        case SDLK_RIGHT:
            return P1_RIGHT;
            break;
        case SDLK_LSHIFT:
            return P2_MARU;
            break;
        case SDLK_LALT:
            return P2_BATSU;
            break;
        case SDLK_r:
            return P2_PAUSE;
            break;
        case SDLK_w:
            return P2_UP;
            break;
        case SDLK_s:
            return P2_DOWN;
            break;
        case SDLK_a:
            return P2_LEFT;
            break;
        case SDLK_d:
            return P2_RIGHT;
            break;
        default:
            return DEFAULT;
            break;
    }
}

void Input_init() {
    int i;
    for (i = 0; i < MAX_SCENE_DEPTH; ++i) {
        SCENE_CONTROLLER[i] = NULL;
    }
    __noController.keyPressed = __nothing;
    __noController.keyReleased = __nothing;
    __noController.keyHeld = __nothing;
    Input_loadSceneController(&__noController);
    logprint("Empty scene 0 loaded for security.\n");
}

void Input_update() {
    int key;

    while( SDL_PollEvent( &e ) != 0 )
        if (e.type == SDL_QUIT) {
            logprint("\t> Game quit by input\n");
            Game_quit();
        } else if (e.type == SDL_KEYDOWN) {
            key = keyRead(e.key.keysym.sym);
            SCENE_CONTROLLER[SCENE_DEPTH]->keyPressed(key);
            isHeld[key] = true;
        } else if (e.type == SDL_KEYUP) {
            key = keyRead(e.key.keysym.sym);
            SCENE_CONTROLLER[SCENE_DEPTH]->keyReleased(key);
            isHeld[key] = false;
        }

    for (key = 0; key < KEYMAP_SIZE; ++key)
        if (isHeld[key]) SCENE_CONTROLLER[SCENE_DEPTH]->keyHeld(key);
}

void Input_loadSceneController(InputController *controller) {
    ++SCENE_DEPTH;
    if (SCENE_DEPTH < MAX_SCENE_DEPTH) {
        SCENE_CONTROLLER[SCENE_DEPTH] = controller;
        logprint("LOADED SCENE IN DEPTH %d\n", SCENE_DEPTH);
    } else {
        GAME_ERROR("LOADED TOO MANY SUBSCENES, SCENE STACK OVERFLOW.");
    }
}

void Input_unloadSceneController() {
    if (SCENE_DEPTH <= 0) {
        logprint("NO SCENE CONTROLLER TO UNLOAD\n");
        Game_quit();
        return;
    }
    logprint("UNLOADED SCENE IN DEPTH %d\n", SCENE_DEPTH);
    SCENE_CONTROLLER[SCENE_DEPTH] = NULL;
    --SCENE_DEPTH;
}
