
#include "debug.h"
#include "scene.h"
#include "sound.h"
#include "config/map.h"
#include "config/font.h"
#include "config/glob.h"
#include "utility/vector.h"
#include "utility/string.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "components/textbox.h"
#include "scenes/chooseyourcat.h"
#include "controllers/chooseyourcat.h"

#include <stdbool.h>

static int CAT_PANEL = -1, CONTROL_PANEL = -1;
static int CHOICE = 0;
static int CATS[CATS_TOTAL];
static int TEXT_P1 = -1, TEXT_P2 = -1;

static void ChooseYourCat_updateChoiceDisplay() {
    int i;
    for (i = 0; i < CATS_TOTAL; ++i) {
        Sprite_hide(CATS[i]);
    }
    Sprite_show(CATS[CHOICE]);
}

static void ChooseYourCat_updateChoosingPlayer(int text) {
    logprint("Making textbox #%d visible\n", text);
    Textbox_hide(TEXT_P1);
    Textbox_hide(TEXT_P2);
    Textbox_show(text);
}

static void ChooseYourCat_loadControlPanel() {
    Vector pos;
    int dpos, sprite;

    Vector_set(&pos, Map_getWidth()/4, 0);
    dpos = DrawPos_new(-1, 192, 224, 96, 112);
    DrawPos_setPos(dpos, &pos);
    sprite = Sprite_new("controls_frame.png", dpos, -1, LAYER_MIDGROUND1);
    CONTROL_PANEL = Entity_new(-1, -1, dpos, sprite, -1);
}

static void ChooseYourCat_loadCatPanel() {
    Vector pos;
    int dpos, sprite;

    Vector_set(&pos, -Map_getWidth()/4, 0);
    dpos = DrawPos_new(-1, 192, 224, 96, 112);
    DrawPos_setPos(dpos, &pos);
    sprite = Sprite_new("choose_bg.png", dpos, -1, LAYER_MIDGROUND1);
    CAT_PANEL = Entity_new(-1, -1, dpos, sprite, -1);
}

static void ChooseYourCat_loadCatDisplay() {
    Vector pos;
    int i;
    int dpos, dquad;
    char catfilepath[32], id[2];

    Vector_set(&pos, 0, 0);
    dpos = DrawPos_new(-1, 64, 64, 32, 32);
    DrawPos_setPos(dpos, &pos);
    dquad = DrawQuad_new(768, 64, 64, 64);
    for (i = 0; i < CATS_TOTAL; ++i) {
        catfilepath[0] = '\0';
        id[0] = '0' + (char)i;
        id[1] = '\0';
        String_join(catfilepath, "cat0", id);
        String_join(catfilepath, catfilepath, ".png\0");
        CATS[i] = Sprite_new(catfilepath, dpos, dquad, LAYER_MIDGROUND2);
    }
    ChooseYourCat_updateChoiceDisplay();
}

static void ChooseYourCat_loadPlayerDisplay() {
    Vector pos;
    int dpos1, dpos2;
    Vector_set(&pos, 0, 0);
    dpos1 = DrawPos_new(-1, 0, 0, 0, -32);
    dpos2 = DrawPos_new(-1, 0, 0, 0, -32);
    TEXT_P1 = Textbox_new("player 1", dpos1, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    TEXT_P2 = Textbox_new("player 2", dpos2, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    DrawPos_setPos(dpos1, &pos);
    DrawPos_setPos(dpos2, &pos);
    Textbox_hide(TEXT_P1);
    Textbox_hide(TEXT_P2);
    ChooseYourCat_updateChoosingPlayer(TEXT_P1);
}

void ChooseYourCat_chooseForPlayer(bool isP1) {
    Sound_playSE(FX_MARU);
    if (isP1) {
        Globals_set(GLOBAL_P1CAT, CHOICE);
        CHOICE = 0;
        ChooseYourCat_updateChoiceDisplay();
        ChooseYourCat_updateChoosingPlayer(TEXT_P2);
    }
    else {
        Globals_set(GLOBAL_P2CAT, CHOICE);
        Scene_close();
        Scene_load(SCENE_PRESSSTART);
    }
}

void ChooseYourCat_changeChoice(bool next) {
    Sound_playSE(FX_SELECT);
    if (next) {
        CHOICE = (CHOICE + 1) % CATS_TOTAL;
    } else {
        CHOICE = (CATS_TOTAL + (CHOICE - 1)) % CATS_TOTAL;
    }
    ChooseYourCat_updateChoiceDisplay();
}

void ChooseYourCat_load() {
    ChooseYourCatController_load();
    ChooseYourCat_loadCatPanel();
    ChooseYourCat_loadControlPanel();
    ChooseYourCat_loadCatDisplay();
    ChooseYourCat_loadPlayerDisplay();
}

void ChooseYourCat_pause() {}

void ChooseYourCat_close() {
    int i;
    for (i = 0; i < CATS_TOTAL; ++i) Sprite_kill(CATS[i]);
    Textbox_kill(TEXT_P1);
    Textbox_kill(TEXT_P2);
    Entity_destroy(CONTROL_PANEL);
    Entity_destroy(CAT_PANEL);
}
