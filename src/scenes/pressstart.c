
#include "action.h"
#include "entity.h"
#include "config/map.h"
#include "config/font.h"
#include "utility/vector.h"
#include "components/drawpos.h"
#include "components/textbox.h"
#include "controllers/pressstart.h"
#include "scenes/pressstart.h"

static FRONTTEXT;

static void PressStart_loadFrontText() {
    Vector pos;
    int dpos, textbox;

    dpos = DrawPos_new(-1, 0, 0, 0, 0);
    textbox = Textbox_new("[ PRESS SHIFT ]", dpos, TEXTALIGN_CENTER, FONTSIZE_MEDIUM, FONTCOLOR_WHITE);
    Vector_set(&pos, 0, 0);
    Vector_print(&pos);
    DrawPos_setPos(dpos, &pos);
    FRONTTEXT = Entity_new(-1, -1, dpos, -1, textbox);
}

void PressStart_load() {
    PressStart_loadFrontText();
    PressStartController_load();
}

void PressStart_close() {
    Entity_destroy(FRONTTEXT);
}
