

typedef void(*Keyevent)(int key);

enum _keymap {
    DEFAULT,
    P1_MARU,
    P1_BATSU,
    P1_PAUSE,
    P1_UP,
    P1_DOWN,
    P1_LEFT,
    P1_RIGHT,
    P2_MARU,
    P2_BATSU,
    P2_PAUSE,
    P2_UP,
    P2_DOWN,
    P2_LEFT,
    P2_RIGHT,
    KEYMAP_SIZE
};

void Input_init();
/* () -> void
 */

void Input_update();
/* () -> void
 */

void Input_registerPress(Keyevent pressFunc);
/* (Keyevent) -> void
 */

void Input_registerRelease(Keyevent releaseFunc);
/* (Keyevent) -> void
 */

void Input_registerHold(Keyevent holdFunc);
/* (Keyevent) -> void 
 */

void __nothing(int key);
/* (int) -> void
Faz nada. */












