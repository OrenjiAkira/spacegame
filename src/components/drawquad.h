#ifndef GAME_DRAWQUAD_H
#define GAME_DRAWQUAD_H

#include "utility/entity.h"

#define DRAWQUAD_POOL_SIZE ENTITY_POOL_SIZE

typedef struct _drawquad DrawQuad;
/* DrawQuad
Struct de "quads". Guarda informação sobre os
recortes de uma imagem. Servem para desenhar
apenas parte de imagens, podendo assim utilizar
spritesheets e evitar carregamento de muitas
imagens ao mesmo tempo. Chamamos esses recortes
de "quads". */

void DrawQuad_init();
/* () -> void
Inicializa pool de DrawQuads. */

int DrawQuad_new(int w, int h, int qw, int qh);
/* (int, int, int, int) -> int
Cria um novo DrawQuad e retorna o seu id. */

void DrawQuad_kill(int id);
/* (int) -> void
Destrói um DrawQuad  */

void DrawQuad_next(int id);
/* (int) -> void
Altera o quad ativo de um DrawQuad para o quad posterior. */

void DrawQuad_prev(int id);
/* (int) -> void
Altera o quad ativo de um DrawQuad para o quad anterior. */

void DrawQuad_change(int id, int quad);
/* (int, int) -> void
Altera o quad ativo de um DrawQuad para um quad especificado. */

SDL_Rect* DrawQuad_getQuad(int id);
/* (int) -> SDL_Rect*
Retorna o quad ativo de um DrawQuad. */

#endif
