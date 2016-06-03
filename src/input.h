

typedef void(*Keyevent)(int key);
/* Keyevent (int) -> void
Tipo de ponteiro de função. Recebe um int
representando um input e retorna void.
Executa algum código com base no valor recebido. */

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

void Input_registerPress(Keyevent pressFunc);
/* (Keyevent) -> void
Registra uma função Keyevent para eventos de keypress. */

void Input_registerRelease(Keyevent releaseFunc);
/* (Keyevent) -> void
Registra uma função Keyevent para eventos de keyrelease. */

void Input_registerHold(Keyevent holdFunc);
/* (Keyevent) -> void
Registra uma função Keyevent para eventos de keyhold. */

void __nothing(int key);
/* (int) -> void
Faz nada. Serve para ocupar um ponteiro de função de Keyevent
quando este não faz nada (por exemplo, quando uma cena de jogo
não utiliza input porque é uma cena em que o usuário não
tem controle do jogo). */
