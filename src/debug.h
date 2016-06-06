#ifndef GAME_DEBUG_H
#define GAME_DEBUG_H

void logprint(char const *fmt, ...);
/* (char* const, ...) -> void
Recebe uma string formatada e parâmetros a serem formatados.
Escreve na saída padrão. Funciona apenas se o compilador
recebeu "-DDEBUG_MODE" como parâmetro. Ler README. */

#endif
