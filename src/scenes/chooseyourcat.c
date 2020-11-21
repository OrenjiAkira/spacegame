
#include "debug.h"
#include "scene.h"
#include "action.h"
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

#include "utility/bool.h"

/* LOGIC */
static int CHOICE = 0;
static int P1_HAS_CHOSEN = false;
/*  false -> P1 escolhe o gato;
    true -> P2 escolhe o gato. */

/* UI */
static int CAT_PANEL = -1, CONTROL_PANEL = -1, CAT_CURSOR = -1;
static int TEXT_P1 = -1, TEXT_P1_DISABLE = -1, TEXT_P2 = -1, TEXT_P2_DISABLE = -1;
static int CAT1[CAT_NUM] = { -1, -1, -1 };
static int CAT2[CAT_NUM] = { -1, -1, -1 };
static char* CATNAMES[] = {
    "Grumpy Cat\0",
    "Nyan Cat\0",
    "???\0"
};

static Vector cursor_pos[CATS_TOTAL];

static char* get_player_cat_filename(char *string, int cat_id) {
    char id[2] = { '0', '\0' };
    id[0] += cat_id;
    String_join(string, "cat0", id);
    String_join(string, string, ".png\0");
    return string;
}

static void UI_loadControlPanel() {
    Vector pos;
    int dpos, dquad, sprite;

    dpos = DrawPos_new(-1, 192, 160, 96, 80);
    dquad = DrawQuad_new(384, 160, 192, 160);
    sprite = Sprite_new("controls_frame.png", dpos, dquad, LAYER_MIDGROUND1);

    Vector_set(&pos, Map_getWidth()/6, Map_getHeight()/6);
    DrawPos_setPos(dpos, &pos);

    CONTROL_PANEL = Entity_new(-1, dquad, dpos, sprite, -1);
}

static void UI_updateControlPanel() {
    Entity *entity = Entity_get(CONTROL_PANEL);
    DrawQuad_next(entity->drawquad);
}

static void UI_loadCatPanel() {
    Vector pos;
    int dpos, sprite;

    Vector_set(&pos, -Map_getWidth()/6, Map_getHeight()/6);
    dpos = DrawPos_new(-1, 192, 160, 96, 80);
    DrawPos_setPos(dpos, &pos);
    sprite = Sprite_new("choose_bg.png", dpos, -1, LAYER_MIDGROUND1);
    CAT_PANEL = Entity_new(-1, -1, dpos, sprite, -1);
}

static void UI_loadPlayerTextDisplay() {
    Vector pos;
    int dpos1, dpos2, dpos3, dpos4;

    dpos1 = DrawPos_new(-1, 0, 0, 0, 48);
    dpos2 = DrawPos_new(-1, 0, 0, 0, 48);
    dpos3 = DrawPos_new(-1, 0, 0, 0, 48);
    dpos4 = DrawPos_new(-1, 0, 0, 0, 48);

    TEXT_P1         = Textbox_new("PLAYER 1", dpos1, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    TEXT_P1_DISABLE = Textbox_new("PLAYER 1", dpos2, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_GREY);
    TEXT_P2         = Textbox_new("PLAYER 2", dpos3, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    TEXT_P2_DISABLE = Textbox_new("PLAYER 2", dpos4, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_GREY);

    Vector_set(&pos, -Map_getWidth()/6, -Map_getHeight()/6);
    DrawPos_setPos(dpos1, &pos);
    DrawPos_setPos(dpos2, &pos);

    Vector_set(&pos, Map_getWidth()/6, -Map_getHeight()/6);
    DrawPos_setPos(dpos3, &pos);
    DrawPos_setPos(dpos4, &pos);

    DrawPos_print(dpos1);
    DrawPos_print(dpos2);
    DrawPos_print(dpos3);
    DrawPos_print(dpos4);

    Textbox_show(TEXT_P1);
    Textbox_hide(TEXT_P1_DISABLE);
    Textbox_hide(TEXT_P2);
    Textbox_show(TEXT_P2_DISABLE);
}

static void UI_newCat(int cat_id, bool isP1) {
    Vector pos;
    int dpos_spr, dpos_txt, dquad, sprite, textbox;
    char filename[64];

    dquad = DrawQuad_new(768, 64, 64, 64);
    dpos_spr = DrawPos_new(-1, 64, 64, 32, 32);
    dpos_txt = DrawPos_new(-1,  0,  0,  0, -24);
    sprite = Sprite_new(get_player_cat_filename(filename, cat_id), dpos_spr, dquad, LAYER_MIDGROUND2);
    textbox = Textbox_new(CATNAMES[cat_id], dpos_txt, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);

    if (isP1) Vector_set(&pos, -Map_getWidth()/6, -Map_getHeight()/6);
    else      Vector_set(&pos,  Map_getWidth()/6, -Map_getHeight()/6);

    DrawPos_setPos(dpos_spr, &pos);
    DrawPos_setPos(dpos_txt, &pos);

    if (isP1) CAT1[cat_id] = Entity_new(-1, dquad, dpos_spr, sprite, textbox);
    else      CAT2[cat_id] = Entity_new(-1, dquad, dpos_spr, sprite, textbox);
}

static void UI_animateUnknownCats() {
    Action_add(ACTION_ANIMATE, CAT1[CAT_UNKNOWN]);
    Action_add(ACTION_ANIMATE, CAT2[CAT_UNKNOWN]);
}

static void UI_loadPlayerCatDisplay() {
    int cat_id;
    for (cat_id = 0; cat_id < CAT_NUM; ++cat_id) {
        UI_newCat(cat_id, true);
        UI_newCat(cat_id, false);
    }
    UI_animateUnknownCats();
}

static void UI_updatePlayerCatDisplay() {
    int cat_id;
    for (cat_id = 0; cat_id < CAT_NUM; ++cat_id) {
        if (!P1_HAS_CHOSEN) Entity_hide(CAT1[cat_id]);
        Entity_hide(CAT2[cat_id]);
    }
    switch (CHOICE) {
        case CAT_GRUMPY:
            if (!P1_HAS_CHOSEN) Entity_show(CAT1[CAT_GRUMPY]);
            else Entity_show(CAT2[CAT_GRUMPY]);
            break;
        case CAT_NYAN:
            if (!P1_HAS_CHOSEN) Entity_show(CAT1[CAT_NYAN]);
            else Entity_show(CAT2[CAT_NYAN]);
            break;
        default:
            if (!P1_HAS_CHOSEN) Entity_show(CAT1[CAT_UNKNOWN]);
            else Entity_show(CAT2[CAT_UNKNOWN]);
            break;
    }
}

static void UI_initCursor() {
    Vector_set(&cursor_pos[0], -Map_getWidth()/6 - 1.6 - 3.2, Map_getHeight()/6 + 0   );
    Vector_set(&cursor_pos[1], -Map_getWidth()/6 - 1.6 - 0  , Map_getHeight()/6 + 0   );
    Vector_set(&cursor_pos[2], -Map_getWidth()/6 - 1.6 + 3.2, Map_getHeight()/6 + 0   );
    Vector_set(&cursor_pos[3], -Map_getWidth()/6 - 1.6 + 6.4, Map_getHeight()/6 + 0   );
    Vector_set(&cursor_pos[4], -Map_getWidth()/6 - 1.6 - 3.2, Map_getHeight()/6 + 3.2 );
    Vector_set(&cursor_pos[5], -Map_getWidth()/6 - 1.6 - 0  , Map_getHeight()/6 + 3.2 );
    Vector_set(&cursor_pos[6], -Map_getWidth()/6 - 1.6 + 3.2, Map_getHeight()/6 + 3.2 );
    Vector_set(&cursor_pos[7], -Map_getWidth()/6 - 1.6 + 6.4, Map_getHeight()/6 + 3.2 );
}

static void UI_loadCursor() {
    int dpos, dquad, sprite;
    dpos = DrawPos_new(-1, 34, 34, 17, 17);
    dquad = DrawQuad_new(136, 34, 34, 34);
    DrawPos_setPos(dpos, &cursor_pos[0]);
    sprite = Sprite_new("cursor.png", dpos, dquad, LAYER_FOREGROUND);
    CAT_CURSOR = Entity_new(-1, dquad, dpos, sprite, -1);
    Action_add(ACTION_ANIMATE, CAT_CURSOR);
}

static void UI_updateCursor() {
    Entity *cursor = Entity_get(CAT_CURSOR);
    DrawPos_setPos(cursor->drawpos, &cursor_pos[CHOICE]);
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
            UI_updateCursor();
            UI_updatePlayerCatDisplay();
            UI_updateControlPanel();
        }
        else {
            Globals_set(GLOBAL_P2CAT, CHOICE);
            Scene_close();
            Scene_load(SCENE_PRESSSTART);
        }
    }
}

void ChooseYourCat_changeChoice(bool isP2, int dir) {
    if (isP2 != P1_HAS_CHOSEN) {
        Sound_playSE(FX_BATSU);
        return;
    }
    Sound_playSE(FX_SELECT);
    switch (dir) {
        case DIR_UP:
            CHOICE = (CATS_TOTAL + (CHOICE - CATS_TOTAL/2)) % CATS_TOTAL;
            break;
        case DIR_RIGHT:
            CHOICE = (CHOICE + 1) % CATS_TOTAL;
            break;
        case DIR_DOWN:
            CHOICE = (CHOICE + CATS_TOTAL/2) % CATS_TOTAL;
            break;
        case DIR_LEFT:
            CHOICE = (CATS_TOTAL + (CHOICE - 1)) % CATS_TOTAL;
            break;
        default:
            break;
    }
    UI_updateCursor();
    UI_updatePlayerCatDisplay();
}

void ChooseYourCat_load() {
    ChooseYourCatController_load();
    UI_loadCatPanel();
    UI_loadControlPanel();
    UI_loadPlayerTextDisplay();
    UI_loadPlayerCatDisplay();
    UI_updatePlayerCatDisplay();
    UI_initCursor();
    UI_loadCursor();
}

void ChooseYourCat_pause() {}

void ChooseYourCat_close() {
    int i;
    for (i = 0; i < CAT_NUM; i++) {
        Entity_destroy(CAT1[i]);
        Entity_destroy(CAT2[i]);
    }
    Entity_destroy(CONTROL_PANEL);
    Entity_destroy(CAT_CURSOR);
    Entity_destroy(CAT_PANEL);
    Textbox_kill(TEXT_P1);
    Textbox_kill(TEXT_P2);
    Textbox_kill(TEXT_P1_DISABLE);
    Textbox_kill(TEXT_P2_DISABLE);
}
