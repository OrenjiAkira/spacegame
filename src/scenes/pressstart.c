
#include "input.h"
#include "action.h"
#include "entity.h"
#include "scene.h"
#include "sound.h"
#include "config/map.h"
#include "config/font.h"
#include "config/glob.h"
#include "utility/string.h"
#include "utility/vector.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "components/textbox.h"
#include "scenes/pressstart.h"
#include "controllers/pressstart.h"

static int FRONTTEXT, PLAYER1, PLAYER2;

static void PressStart_loadFrontText() {
    Vector pos;
    int dpos, textbox;

    dpos = DrawPos_new(-1, 0, 0, 0, 0);
    textbox = Textbox_new("[ PRESS ANY SHIFT, ENTER, OR SPACE ]", dpos, TEXTALIGN_CENTER, FONTSIZE_MEDIUM, FONTCOLOR_WHITE);
    Vector_set(&pos, 0, 0);
    Vector_print(&pos);
    DrawPos_setPos(dpos, &pos);
    FRONTTEXT = Entity_new(-1, -1, dpos, -1, textbox);
}

static char* get_player_cat_filename(char *string, bool isP1) {
    char id[2] = { '0', '\0' };
    if (isP1) id[0] += Globals_get(GLOBAL_P1CAT);
    else id[0] += Globals_get(GLOBAL_P2CAT);
    String_join(string, "cat0", id);
    String_join(string, string, ".png\0");
    return string;
}

static void PressStart_loadPlayer(bool isP1) {
    Vector pos;
    char filename[32];
    int dpos, dquad, sprite, textbox;

    dpos = DrawPos_new(-1, 64, 64, 32, 32);
    dquad = DrawQuad_new(768, 64, 64, 64);
    sprite = Sprite_new(get_player_cat_filename(filename, isP1), dpos, dquad, LAYER_MIDGROUND1);
    if (isP1) Vector_set(&pos, -Map_getWidth()/6, Map_getHeight()/4);
    else Vector_set(&pos, Map_getWidth()/6, Map_getHeight()/4);
    DrawPos_setPos(dpos, &pos);
    dpos = DrawPos_new(-1, 0, 0, 0, -24);
    if (isP1) textbox = Textbox_new("PLAYER 1", dpos, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    else textbox = Textbox_new("PLAYER 2", dpos, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    DrawPos_setPos(dpos, &pos);
    PLAYER1 = Entity_new(-1, dquad, dpos, sprite, textbox);
}

void PressStart_load() {
    PressStart_loadPlayer(true);
    PressStart_loadPlayer(false);
    PressStart_loadFrontText();
    PressStartController_load();
}

void PressStart_confirm() {
    Sound_playSE(FX_MARU);
    Scene_close();
    Scene_load(SCENE_GAMEPLAY);
}

void PressStart_pause() {}

void PressStart_close() {
    Input_unloadSceneController();
    Entity_destroy(FRONTTEXT);
    Entity_destroy(PLAYER1);
    Entity_destroy(PLAYER2);
}
