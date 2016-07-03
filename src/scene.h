#ifndef GAME_SCENE_H
#define GAME_SCENE_H

typedef struct _scene {
    void (*load)();
    void (*pause)();
    void (*close)();
} Scene;

typedef void (*SceneMethod)();

enum _scene_names {
    SCENE_DEFAULT,
    SCENE_GAMEPLAY,
    SCENE_PRESSSTART,
    SCENE_CHOOSEYOURCAT,
    SCENE_TOTAL
};

#define SCENE_INITIALIZE(ID, SNAME) \
    SCENE_LIST[ID].load = SNAME##_load; \
    SCENE_LIST[ID].pause = SNAME##_pause; \
    SCENE_LIST[ID].close = SNAME##_close

void Scene_init();
/* () -> void
Inicializa todas as cenas do jogo. */

void Scene_load(int sname);
/* () -> void
Recebe o nome de uma cena, e a torna atual. */

void Scene_close();
/* () -> void
Fecha a cena atual, liberando sua memória alocada. */

void Scene_pause();
/* () -> void
Pausa a cena atual. Não libera a memória.
Usada para guardar um estado de cena. */

#endif
