
#include "input.h"
#include "action.h"
#include "entity.h"
#include "config/map.h"
#include "config/font.h"
#include "utility/vector.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "components/textbox.h"
#include "scenes/pressstart.h"
#include "controllers/pressstart.h"

static int FRONTTEXT, TUTORIAL1, TUTORIAL2;

static void PressStart_loadFrontText() {
    Vector pos;
    int dpos, textbox;

    dpos = DrawPos_new(-1, 0, 0, 0, 0);
    textbox = Textbox_new("[ PRESS ANY SHIFT ]", dpos, TEXTALIGN_CENTER, FONTSIZE_MEDIUM, FONTCOLOR_WHITE);
    Vector_set(&pos, 0, 0);
    Vector_print(&pos);
    DrawPos_setPos(dpos, &pos);
    FRONTTEXT = Entity_new(-1, -1, dpos, -1, textbox);
}

static void PressStart_loadTutorialText2() {
    Vector pos;
    int dpos, dquad, textbox, sprite;

    dpos = DrawPos_new(-1, 64, 64, 32, 32);
    dquad = DrawQuad_new(768, 64, 64, 64);
    sprite = Sprite_new("cat01.png", dpos, dquad, LAYER_MIDGROUND1);
    Vector_set(&pos, -Map_getWidth()/4, Map_getHeight()/4 - 3);
    DrawPos_setPos(dpos, &pos);
    dpos = DrawPos_new(-1, 0, 0, 0, 0);
    textbox = Textbox_new("use WASD keys to move", dpos, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    Vector_set(&pos, -Map_getWidth()/4, Map_getHeight()/4);
    Vector_print(&pos);
    DrawPos_setPos(dpos, &pos);
    TUTORIAL2 = Entity_new(-1, dquad, dpos, sprite, textbox);
}

static void PressStart_loadTutorialText1() {
    Vector pos;
    int dpos, dquad, textbox, sprite;

    dpos = DrawPos_new(-1, 64, 64, 32, 32);
    dquad = DrawQuad_new(768, 64, 64, 64);
    sprite = Sprite_new("cat00.png", dpos, dquad, LAYER_MIDGROUND1);
    Vector_set(&pos, Map_getWidth()/4, Map_getHeight()/4 - 3);
    DrawPos_setPos(dpos, &pos);
    dpos = DrawPos_new(-1, 0, 0, 0, 0);
    textbox = Textbox_new("use directional keys to move", dpos, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    Vector_set(&pos, Map_getWidth()/4, Map_getHeight()/4);
    Vector_print(&pos);
    DrawPos_setPos(dpos, &pos);
    TUTORIAL1 = Entity_new(-1, dquad, dpos, sprite, textbox);
}

void PressStart_load() {
    PressStart_loadTutorialText1();
    PressStart_loadTutorialText2();
    PressStart_loadFrontText();
    PressStartController_load();
}

void PressStart_pause() {}

void PressStart_unpause() {}

void PressStart_close() {
    Input_unloadSceneController();
    Entity_destroy(FRONTTEXT);
    Entity_destroy(TUTORIAL1);
    Entity_destroy(TUTORIAL2);
}
