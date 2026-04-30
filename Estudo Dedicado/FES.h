#ifndef FES_H
#define FES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   FES.h — Fila Estática Simples
   FIFO: primeiro que entra é o primeiro que sai.
   Inserção sempre no FIM, remoção sempre no INÍCIO.

   PROBLEMA desta versão: após várias remoções, o espaço
   do início fica inutilizado. Quando fim==tamVetor a fila
   parece cheia mesmo com espaço vazio no começo.
   Solução: use FEM (com memmove) ou FEC (circular).
   ========================================================= */

#ifndef SUCESSO
#define SUCESSO  1
#define FRACASSO 0
#endif

typedef struct {
    int   inicio;    /* índice do primeiro elemento da fila          */
    int   fim;       /* índice da próxima posição livre (após último) */
    int   tamVetor;  /* capacidade máxima                            */
    int   tamInfo;   /* tamanho em bytes de cada elemento            */
    void *vet;       /* vetor de dados                               */
} FES;

/* ---------------------------------------------------------
   Criação.
   --------------------------------------------------------- */
FES *cria_FES(FES *f, int tamVetor, int tamInfo) {
    f->vet = malloc(tamVetor * tamInfo);
    if (!f->vet) return NULL;
    f->inicio   = 0;
    f->fim      = 0;   /* inicio==fim → fila vazia                   */
    f->tamVetor = tamVetor;
    f->tamInfo  = tamInfo;
    return f;
}

/* ---------------------------------------------------------
   Destruição.
   --------------------------------------------------------- */
FES *destroi_FES(FES *f) {
    free(f->vet);
    f->vet    = NULL;
    f->inicio = f->fim = 0;
    return f;
}

/* ---------------------------------------------------------
   Reinicialização.
   --------------------------------------------------------- */
int reinicia_FES(FES *f) {
    f->inicio = f->fim = 0;
    return SUCESSO;
}

/* ---------------------------------------------------------
   Testa vazia: inicio == fim.
   --------------------------------------------------------- */
int testaVazia_FES(FES *f) { return f->inicio == f->fim; }

/* ---------------------------------------------------------
   Testa cheia: fim chegou ao final do vetor.
   (Mesmo com espaço livre no começo — limitação da FES.)
   --------------------------------------------------------- */
int testaCheia_FES(FES *f) { return f->fim == f->tamVetor; }

/* ---------------------------------------------------------
   Enfileira: insere no fim.
   --------------------------------------------------------- */
int enfileira_FES(FES *f, void *reg) {
    if (testaCheia_FES(f)) return FRACASSO;
    memcpy(
        (char*)f->vet + f->fim * f->tamInfo,  /* posição do fim      */
        reg,
        f->tamInfo
    );
    f->fim++;   /* avança o fim para a próxima posição livre          */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Desenfileira: remove do início.
   O espaço antes de "inicio" fica desperdiçado!
   --------------------------------------------------------- */
int desenfileira_FES(FES *f, void *dest) {
    if (testaVazia_FES(f)) return FRACASSO;
    memcpy(
        dest,
        (char*)f->vet + f->inicio * f->tamInfo,  /* posição do início */
        f->tamInfo
    );
    f->inicio++;  /* avança início — espaço anterior não é reutilizado */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Busca no início (frente da fila): copia sem remover.
   --------------------------------------------------------- */
int buscaNoInicio_FES(FES *f, void *dest) {
    if (testaVazia_FES(f)) return FRACASSO;
    memcpy(dest, (char*)f->vet + f->inicio * f->tamInfo, f->tamInfo);
    return SUCESSO;
}

/* ---------------------------------------------------------
   Número de elementos na fila.
   --------------------------------------------------------- */
int numElementos_FES(FES *f) { return f->fim - f->inicio; }

#endif /* FES_H */
