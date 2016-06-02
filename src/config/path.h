#ifndef GAME_PATH_H
#define GAME_PATH_H

typedef struct _path Path;
/* Path
Struct de paths. Guarda o caminho do arquivo de execução
e das pastas de assets utilizadas por outras partes do código.
Isso serve para o jogo conseguir encontrar os assets dentro
da pasta do executável. */

void Path_init(char *execpath);
/* (char*) -> void
Recebe o argv[0] do main, e armazena o caminho até a
pasta do executável a partir de onde o programa está
sendo executado. A partir dessa informação, é gerado
e armazenado o caminho para as pastas de assets
(imagens, fontes, etc). */

char* Path_toExecutable();
/* () -> char*
Retorna o caminho para a pasta do executável. */

char* Path_toSprites();
/* () -> char*
Retorna o caminho para a pasta de sprites. */

char* Path_toFonts();
/* () -> char*
Retorna o caminho para a pasta de fontes. */


#endif
