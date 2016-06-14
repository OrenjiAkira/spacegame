#ifndef GAME_SCENE_H
#define GAME_SCENE_H

typedef struct _scene {
    void (*load)();
    void (*pause)();
    void (*close)();
} Scene;

enum _scene_names {
    SCENE_GAMEPLAY,
    SCENE_PRESSSTART,
    SCENE_PAUSE,
    SCENE_TEXT,
    SCENE_TOTAL
};

#define SCENE_STACK_SIZE SCENE_TOTAL*2

void Scene_init();
/* () -> void */

void Scene_load(Scene* scene);
/* () -> void */

void Scene_stack(Scene* scene);
/* () -> void */

void Scene_close();
/* () -> void */


#endif
