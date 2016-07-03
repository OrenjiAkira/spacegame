#ifndef GAME_CHOOSEYOURCAT_H
#define GAME_CHOOSEYOURCAT_H

#include <stdbool.h>

#define CATS_TOTAL 8

enum _cat_choices {
    CAT_GRUMPY,
    CAT_NYAN,
    CAT_UNKNOWN,
    CAT_NUM
};

enum _cursor_dirs {
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
};

void ChooseYourCat_load();
/* () -> void
Carrega os elementos da cena e seu controller.
São elementos visuais de UI, principalmente. */

void ChooseYourCat_pause();
/* () -> void
Faz nada. Cena não foi feita para ser pausada. */

void ChooseYourCat_close();
/* () -> void
Libera os elementos da cena. */

void ChooseYourCat_chooseForPlayer(bool isP2);
/* (bool) -> void
Confirma a escolha do gato em destaque para um jogador. */

void ChooseYourCat_changeChoice(bool isP2, int dir);
/* (bool) -> void
Modifica o gato em destaque. */


 #endif
