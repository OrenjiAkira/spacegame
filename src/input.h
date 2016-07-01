#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#define MAX_SCENE_DEPTH 16

typedef void(*Keyevent)(int key);
/* Keyevent (int) -> void
Tipo de ponteiro de função. Recebe um int
representando um input e retorna void.
Executa algum código com base no valor recebido. */

typedef struct _input_controller {
    Keyevent keyPressed;
    Keyevent keyReleased;
    Keyevent keyHeld;
} InputController;
/* InputController
Struct que guarda funções que gerenciam o input.
Possuem três ponteiros de função, um para cada
tipo de input (press, release, e hold). */

enum _keymap {
    DEFAULT,
    P1_MARU,
    P1_BATSU,
    P1_PAUSE,
    P1_UP,
    P1_DOWN,
    P1_LEFT,
    P1_RIGHT,
    P2_MARU,
    P2_BATSU,
    P2_PAUSE,
    P2_UP,
    P2_DOWN,
    P2_LEFT,
    P2_RIGHT,
    KEYMAP_SIZE
};

void Input_init();
/* () -> void
Inicializa as funções de input do jogo.
Por padrão as inicializa com uma função nula
(que não faz nada) para evitar que eventos de
input tentem executar um ponteiro de função nulo. */

void Input_update();
/* () -> void
Verifica os inputs do usuário e chama os
ponteiros de função que guardam os eventos
de input da cena atual de jogo. */

void Input_loadSceneController(InputController *controller);
/* (InputController*) -> void
Recebe e empilha um ponteiro de InputController na pilha de controles. */

void Input_unloadSceneController();
/* () -> void
Desempilha um ponteiro de InputController da pilha de controles. */

#endif
