
#include "debug.h"
#include "scene.h"
#include "config/map.h"
#include "utility/vector.h"
#include "components/drawpos.h"
#include "components/sprite.h"
#include "scenes/chooseyourcat.h"
#include "controllers/chooseyourcat.h"

static int CAT_PANEL = -1, CONTROL_PANEL = -1;

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

void ChooseYourCat_load() {
    ChooseYourCatController_load();
    ChooseYourCat_loadCatPanel();
    ChooseYourCat_loadControlPanel();
}

void ChooseYourCat_pause() {}

void ChooseYourCat_unpause() {}

void ChooseYourCat_close() {
    Entity_destroy(CONTROL_PANEL);
    Entity_destroy(CAT_PANEL);
}
