
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

static int CATS_TOTAL = 8;
static int CAT_PANEL = -1, CONTROL_PANEL = -1;
static int CHOICE = 0;
static int TEXT_P1 = -1, TEXT_P1_DISABLE = -1, TEXT_P2 = -1, TEXT_P2_DISABLE = -1;
static int P1_HAS_CHOSEN = false;
/*  false -> P1 escolhe o gato;
    true -> P2 escolhe o gato. */

static void ChooseYourCat_loadControlPanel() {
    Vector pos;
    int dpos, sprite;

    Vector_set(&pos, Map_getWidth()/6, Map_getHeight()/6);
    dpos = DrawPos_new(-1, 192, 160, 96, 80);
    DrawPos_setPos(dpos, &pos);
    sprite = Sprite_new("controls_frame.png", dpos, -1, LAYER_MIDGROUND1);
    CONTROL_PANEL = Entity_new(-1, -1, dpos, sprite, -1);
}

static void ChooseYourCat_loadCatPanel() {
    Vector pos;
    int dpos, sprite;

    Vector_set(&pos, -Map_getWidth()/6, Map_getHeight()/6);
    dpos = DrawPos_new(-1, 192, 160, 96, 80);
    DrawPos_setPos(dpos, &pos);
    sprite = Sprite_new("choose_bg.png", dpos, -1, LAYER_MIDGROUND1);
    CAT_PANEL = Entity_new(-1, -1, dpos, sprite, -1);
}

static void ChooseYourCat_loadPlayerTextDisplay() {
    Vector pos1, pos2;
    int dpos1, dpos2;
    Vector_set(&pos1, -Map_getWidth()/6, -Map_getHeight()/6);
    Vector_set(&pos2, Map_getWidth()/6, -Map_getHeight()/6);
    dpos1 = DrawPos_new(-1, 0, 0, 0, 48);
    dpos2 = DrawPos_new(-1, 0, 0, 0, 48);
    TEXT_P1 = Textbox_new("PLAYER 1", dpos1, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    TEXT_P1_DISABLE = Textbox_new("PLAYER 1", dpos1, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_GREY);
    TEXT_P2 = Textbox_new("PLAYER 2", dpos2, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    TEXT_P2_DISABLE = Textbox_new("PLAYER 2", dpos2, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_GREY);
    DrawPos_setPos(dpos1, &pos1);
    DrawPos_setPos(dpos2, &pos2);
    Textbox_show(TEXT_P1);
    Textbox_hide(TEXT_P1_DISABLE);
    Textbox_hide(TEXT_P2);
    Textbox_show(TEXT_P2_DISABLE);
}

void ChooseYourCat_chooseForPlayer(bool isP2) {
    if (CHOICE >= CAT_UNKNOWN || isP2 != P1_HAS_CHOSEN) {
        Sound_playSE(FX_BATSU);
        return;
    } else {
        Sound_playSE(FX_MARU);
        if (!isP2) {
            Globals_set(GLOBAL_P1CAT, CHOICE);
            CHOICE = 0;
            P1_HAS_CHOSEN = true;
            Textbox_hide(TEXT_P1);
            Textbox_show(TEXT_P1_DISABLE);
            Textbox_show(TEXT_P2);
            Textbox_hide(TEXT_P2_DISABLE);
        }
        else {
            Globals_set(GLOBAL_P2CAT, CHOICE);
            Scene_close();
            Scene_load(SCENE_PRESSSTART);
        }
    }
}

void ChooseYourCat_changeChoice(bool isP2, bool next) {
    if (isP2 != P1_HAS_CHOSEN) {
        Sound_playSE(FX_BATSU);
        return;
    }
    Sound_playSE(FX_SELECT);
    if (next) {
        CHOICE = (CHOICE + 1) % CATS_TOTAL;
    } else {
        CHOICE = (CATS_TOTAL + (CHOICE - 1)) % CATS_TOTAL;
    }
}

void ChooseYourCat_load() {
    ChooseYourCatController_load();
    ChooseYourCat_loadCatPanel();
    ChooseYourCat_loadControlPanel();
    ChooseYourCat_loadPlayerTextDisplay();
}

void ChooseYourCat_pause() {}

void ChooseYourCat_close() {
    Textbox_kill(TEXT_P1);
    Textbox_kill(TEXT_P2);
    Textbox_kill(TEXT_P1_DISABLE);
    Textbox_kill(TEXT_P2_DISABLE);
    Entity_destroy(CONTROL_PANEL);
    Entity_destroy(CAT_PANEL);
}
