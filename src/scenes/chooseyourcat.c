
#include "debug.h"
#include "scene.h"
#include "config/map.h"
#include "config/glob.h"
#include "utility/vector.h"
#include "utility/string.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "scenes/chooseyourcat.h"
#include "controllers/chooseyourcat.h"

#include <stdbool.h>

static int CAT_PANEL = -1, CONTROL_PANEL = -1;
static int CHOICE = 0;
static int CATS[CATS_TOTAL];

static void ChooseYourCat_updateChoiceDisplay() {
    int i;
    for (i = 0; i < CATS_TOTAL; ++i) {
        Sprite_hide(CATS[i]);
    }
    Sprite_show(CATS[CHOICE]);
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

    Vector_set(&pos, -Map_getWidth()/4, 0);
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

void ChooseYourCat_chooseForPlayer(bool isP1) {
    if (isP1) {
        Globals_set(GLOBAL_P1CAT, CHOICE);
        CHOICE = 0;
        ChooseYourCat_updateChoiceDisplay();
    }
    else Globals_set(GLOBAL_P2CAT, CHOICE);
}

void ChooseYourCat_changeChoice(bool next) {
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
}

void ChooseYourCat_pause() {}

void ChooseYourCat_close() {
    int i;
    for (i = 0; i < CATS_TOTAL; ++i) Sprite_kill(CATS[i]);
    Entity_destroy(CONTROL_PANEL);
    Entity_destroy(CAT_PANEL);
}
