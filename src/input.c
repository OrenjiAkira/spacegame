
#include "game.h"
#include "input.h"

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

static SDL_Event e;

static bool isHeld[KEYMAP_SIZE];

static Keyevent keyPressed = NULL;
static Keyevent keyReleased = NULL;
static Keyevent keyHeld = NULL;

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
    keyReleased = __nothing;
    keyPressed = __nothing;
    keyHeld = __nothing;
}

void Input_update() {
    int key;

    while( SDL_PollEvent( &e ) != 0 )
        if (e.type == SDL_QUIT) {
            Game_quit();
        } else if (e.type == SDL_KEYDOWN) {
            key = keyRead(e.key.keysym.sym);
            keyPressed(key);
            isHeld[key] = true;
        } else if (e.type == SDL_KEYUP) {   
            key = keyRead(e.key.keysym.sym);
            keyReleased(key);
            isHeld[key] = false;
        }

    for (key = 0; key < KEYMAP_SIZE; ++key)
        if (isHeld[key]) keyHeld(key);
}

void Input_registerPress(Keyevent pressFunc) {
    keyPressed = pressFunc;
}

void Input_registerRelease(Keyevent releaseFunc) {
    keyReleased = releaseFunc;
}

void Input_registerHold(Keyevent holdFunc) {
    keyHeld = holdFunc;
}

void __nothing(int key) {}

