#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

typedef void (*KeyHandler)();

#define EVENT_ASSOCIATE(EVENT, KEY, FUNCTION) EVENT##_keyhandlers[KEY] = FUNCTION

#define DECALRE_EVENTS(EVENT) static KeyHandler EVENT##_keyhandlers[KEYMAP_SIZE] = { \
    __null_handler__, /* default */ \
    __null_handler__, /* P1_MARU */ \
    __null_handler__, /* P1_BATSU */ \
    __null_handler__, /* P1_PAUSE */ \
    __null_handler__, /* P1_UP */ \
    __null_handler__, /* P1_DOWN */ \
    __null_handler__, /* P1_LEFT */ \
    __null_handler__, /* P1_RIGHT */ \
    __null_handler__, /* P2_MARU */ \
    __null_handler__, /* P2_BATSU */ \
    __null_handler__, /* P2_PAUSE */ \
    __null_handler__, /* P2_UP */ \
    __null_handler__, /* P2_DOWN */ \
    __null_handler__, /* P2_LEFT */ \
    __null_handler__  /* P2_RIGHT */ }

#define NEW_CONTROLLER(NAME) \
    static bool init = false; \
    static InputController NAME##Controller; \
    static void __null_handler__() {} \
    static void NAME##Controller_init(); \
    DECALRE_EVENTS(press); \
    DECALRE_EVENTS(release); \
    DECALRE_EVENTS(hold); \
    static void keypress(int key) { press_keyhandlers[key](); } \
    static void keyrelease(int key) { release_keyhandlers[key](); } \
    static void keyhold(int key) { hold_keyhandlers[key](); } \
    void NAME##Controller_load() { \
        if (!init) { NAME##Controller_init(); } \
        NAME##Controller.keyPressed = keypress; \
        NAME##Controller.keyReleased = keyrelease; \
        NAME##Controller.keyHeld = keyhold; \
        logprint("Stacking " #NAME " scene...\n"); \
        Input_loadSceneController(&NAME##Controller); } \
    static char *success_msg = "> Controller " #NAME " initialized\n"

/* Essa última linha de código serve para o uso
da macro pedir o caracter ";" no fim da linha.
Isso só faz meu syntax-highlighting não zuar huehue. */

#endif
