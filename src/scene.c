
#include "debug.h"
#include "game.h"
#include "scene.h"
#include "scenes/gameplay.h"
#include "scenes/pressstart.h"

#include <stdlib.h>

static Scene *SCENE[SCENE_STACK_SIZE];
static int SCENE_STACK_HEAD = -1;

static Scene __noScene__;
static void __null_scene__() {}

void Scene_init() {
    int i;
    for (i = 0; i < SCENE_STACK_SIZE; ++i) SCENE[i] = NULL;

    __noScene__.load = __null_scene__;
    __noScene__.pause = __null_scene__;
    __noScene__.close = __null_scene__;
    Scene_load(&__noScene__);
}

void Scene_load(Scene* scene) {
    if (SCENE_STACK_HEAD > 0) Scene_close();
    ++SCENE_STACK_HEAD;
    SCENE[SCENE_STACK_HEAD] = scene;
    SCENE[SCENE_STACK_HEAD]->load();
}

void Scene_stack(Scene* scene) {
    if (SCENE_STACK_HEAD >= 0) SCENE[SCENE_STACK_HEAD]->pause();
    ++SCENE_STACK_HEAD;
    SCENE[SCENE_STACK_HEAD] = scene;
    SCENE[SCENE_STACK_HEAD]->load();
}

void Scene_close() {
    if (SCENE_STACK_HEAD < 0) { GAME_ERROR("Unable to close unstacked scene"); return; }
    if (SCENE_STACK_HEAD == 0) { logprint("\t> All scenes unloaded, closing game"); Game_quit(); }
    SCENE[SCENE_STACK_HEAD]->close();
    --SCENE_STACK_HEAD;
}
