/*
 * pilha.h
 * -------
 * Interface pública da Pilha Duplamente Encadeada (PDE) genérica.
 * Inclua este arquivo em qualquer módulo que precise usar a pilha.
 *
 * A implementação está em pilha.c.
 *
 * Disciplina: EDA - Estruturas de Dados e Algoritmos
 */

#ifndef PILHA_H
#define PILHA_H

#include <stddef.h> /* size_t */

/* ------------------------------------------------------------------
 * Nó da pilha duplamente encadeada
 * Cada nó sabe quem está acima e quem está abaixo de si na pilha.
 * ------------------------------------------------------------------ */
typedef struct No
{
    void *dados;       /* ponteiro para a cópia do dado armazenado   */
    struct No *acima;  /* nó empilhado depois  (mais próximo do topo) */
    struct No *abaixo; /* nó empilhado antes   (mais próximo da base) */
} No;

/* ------------------------------------------------------------------
 * Cabeçalho da pilha
 * Guarda o topo, o tamanho de cada elemento e o total de elementos.
 * ------------------------------------------------------------------ */
typedef struct
{
    No *topo;       /* aponta para o nó no topo (NULL se vazia)       */
    size_t tamInfo; /* tamanho em bytes de cada elemento armazenado   */
    int tamanho;    /* quantidade atual de elementos na pilha         */
} Pilha;

/* ------------------------------------------------------------------
 * Protótipos da interface pública
 * ------------------------------------------------------------------ */

/* Cria e retorna uma nova pilha. tamInfo = sizeof(tipo a armazenar). */
Pilha *criarPilha(size_t tamInfo);

/* Libera todos os recursos alocados pela pilha. */
void destruirPilha(Pilha *p);

/* Empilha uma cópia do dado apontado por 'dado'. Retorna 1/0. */
int push(Pilha *p, const void *dado);

/* Desempilha e copia o dado para 'destino'. Retorna 1/0. */
int pop(Pilha *p, void *destino);

/* Consulta o topo sem remover. Retorna 1/0. */
int topo(const Pilha *p, void *destino);

/* Retorna 1 se a pilha estiver vazia, 0 caso contrário. */
int pilhaVazia(const Pilha *p);

/* Retorna o número de elementos na pilha. */
int tamanhoPilha(const Pilha *p);

#endif /* PILHA_H */