#ifndef GAME_CHOOSEYOURCAT_H
#define GAME_CHOOSEYOURCAT_H

#include <stdbool.h>

enum _cat_choices {
    CAT_GRUMPY,
    CAT_NYAN,
    CATS_TOTAL
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

void ChooseYourCat_chooseForPlayer(bool isP1);
/* (bool) -> void
Confirma a escolha do gato em destaque para um jogador. */

void ChooseYourCat_changeChoice(bool next);
/* (bool) -> void
Modifica o gato em destaque. */


 #endif
