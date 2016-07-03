
#include "debug.h"
#include "game.h"
#include "scene.h"
#include "scenes/gameplay.h"
#include "scenes/pressstart.h"
#include "scenes/chooseyourcat.h"
#include "controllers/gameplay.h"
#include "controllers/pressstart.h"
#include "controllers/chooseyourcat.h"

#include <stdlib.h>

static void null_scene_load() {}
static void null_scene_pause() {}
static void null_scene_close() {}

static Scene *CURRENT_SCENE = NULL;
static Scene SCENE_LIST[SCENE_TOTAL];

void Scene_init() {
    SCENE_INITIALIZE(SCENE_DEFAULT, null_scene);
    SCENE_INITIALIZE(SCENE_GAMEPLAY, GamePlay);
    SCENE_INITIALIZE(SCENE_PRESSSTART, PressStart);
    SCENE_INITIALIZE(SCENE_CHOOSEYOURCAT, ChooseYourCat);

    Scene_load(SCENE_DEFAULT);
}

void Scene_load(int sname) {
    CURRENT_SCENE = &SCENE_LIST[sname];
    CURRENT_SCENE->load();
}

void Scene_close() {
    logprint("\n[ Closing current scene ]\n");
    if (CURRENT_SCENE != NULL) CURRENT_SCENE->close();
    CURRENT_SCENE = NULL;
}

void Scene_pause() {
    CURRENT_SCENE->pause();
}
