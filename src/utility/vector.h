#ifndef GAME_VECTOR_H
#define GAME_VECTOR_H

#define EPSILON 2e-8

typedef struct _vector {
    float x;
    float y;
} Vector;
/* Vector
Struct de vetor.
Todo elemento que usa cálculos vetoriais
contém uma instância deste struct. */

void Vector_set(Vector *v, float x, float y);
/* (Vector*, float, float) -> void
Define os parâmetros de um vetor. */

void Vector_copy(Vector *v, Vector *w);
/* (Vector*, Vector) -> void
Copia o vetor w no vetor v. */

void Vector_add(Vector *v, Vector *w);
/* (Vector*, Vector*) -> void
Calcula a soma de dois vetores.
Apenas o primeiro é modificado. */

void Vector_sub(Vector *v, Vector *w);
/* (Vector*, Vector*) -> void
Calcula a subtração de dois vetores.
Apenas o primeiro é modificado. */

void Vector_mult(Vector *v, float p);
/* (Vector*, float) -> void
Multiplica um vetor por um valor escalar. */

void Vector_magnitude(Vector *v, float mag);
/* (Vector*, float) -> void
Muda a magnitude de um vetor sem mudar sua direção ou sentido. */

void Vector_print(Vector *v);
/* (Vector*) -> void
Imprime as informações do vetor */

float Vector_get_sqrlen(Vector *v);
/* (Vector*) -> float
Calcula a magnitude quadrada de um vetor e a retorna. */

#endif
