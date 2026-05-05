/*
 * arq.h
 * -----
 * Arquivo de cabeçalho compartilhado entre pilha.c e aplicacao.c.
 * Define os tipos e estruturas usados no projeto.
 *
 * Disciplina: EDA - Estruturas de Dados e Algoritmos
 */

#ifndef ARQ_H
#define ARQ_H

/* --------------------------------------------------------------------------
 * Tipo genérico armazenado na pilha.
 * A PDE é genérica: armazena qualquer dado via ponteiro void*.
 * Aqui definimos o tipo concreto que a aplicação vai empilhar:
 * uma coordenada (linha, coluna) de um pixel da matriz.
 * -------------------------------------------------------------------------- */
typedef struct
{
    int lin; /* linha   da célula */
    int col; /* coluna  da célula */
} Coord;

/* --------------------------------------------------------------------------
 * Dimensões máximas suportadas para a matriz de entrada.
 * Ajuste MAX_DIM se precisar de matrizes maiores.
 * -------------------------------------------------------------------------- */
#define MAX_DIM 512

/* --------------------------------------------------------------------------
 * Estrutura que representa a matriz lida do arquivo.
 * -------------------------------------------------------------------------- */
typedef struct
{
    int dados[MAX_DIM][MAX_DIM]; /* valores 0 ou 1         */
    int M;                       /* número de linhas       */
    int N;                       /* número de colunas      */
} Matriz;

/* --------------------------------------------------------------------------
 * Protótipos das funções de E/S de matriz (implementadas em aplicacao.c)
 * -------------------------------------------------------------------------- */
int lerMatriz(const char *nomeArq, Matriz *mat);
void salvarMatriz(const char *nomeArq, const Matriz *mat);
void imprimirMatriz(const Matriz *mat);

#endif /* ARQ_H */