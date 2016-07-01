
#include "debug.h"
#include "game.h"
#include "input.h"
#include "action.h"
#include "entity.h"
#include "config/conf.h"
#include "config/font.h"
#include "utility/direction.h"
#include "utility/vector.h"
#include "components/physics.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "components/textbox.h"
#include "controllers/chooseyourcat.h"
#include "scenes/chooseyourcat.h"

#include <stdio.h>
#include <string.h>

void ChooseYourCat_load() {
    ChooseYourCatController_load();
}

void ChooseYourCat_pause() {}

void ChooseYourCat_unpause() {}

void ChooseYourCat_close() {

}
