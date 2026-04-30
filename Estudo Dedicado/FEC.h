#ifndef FEC_H
#define FEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   FEC.h — Fila Estática Circular
   Usa o operador % para "dar a volta" nos índices.
   Não desperdiça espaço e não move elementos: O(1) em
   enfileira e desenfileira.

   ATENÇÃO: inicio==fim tanto para vazia quanto para cheia.
   Por isso usamos o campo "numElem" para distinguir os
   dois casos.
   ========================================================= */

#ifndef SUCESSO
#define SUCESSO  1
#define FRACASSO 0
#endif

typedef struct {
    int   inicio;    /* índice do primeiro elemento                  */
    int   fim;       /* índice da próxima posição livre              */
    int   numElem;   /* contador de elementos (resolve a ambiguidade)*/
    int   tamVetor;
    int   tamInfo;
    void *vet;
} FEC;

/* ---------------------------------------------------------
   Criação.
   --------------------------------------------------------- */
FEC *cria_FEC(FEC *f, int tamVetor, int tamInfo) {
    f->vet = malloc(tamVetor * tamInfo);
    if (!f->vet) return NULL;
    f->inicio   = 0;
    f->fim      = 0;
    f->numElem  = 0;   /* vazia                                      */
    f->tamVetor = tamVetor;
    f->tamInfo  = tamInfo;
    return f;
}

FEC *destroi_FEC(FEC *f) {
    free(f->vet);
    f->vet     = NULL;
    f->inicio  = f->fim = f->numElem = 0;
    return f;
}

int reinicia_FEC(FEC *f) {
    f->inicio = f->fim = f->numElem = 0;
    return SUCESSO;
}

/* ---------------------------------------------------------
   Vazia: numElem == 0.
   Cheia: numElem == tamVetor.
   (Não usar inicio==fim para isso — são idênticos nos dois casos.)
   --------------------------------------------------------- */
int testaVazia_FEC(FEC *f) { return f->numElem == 0; }
int testaCheia_FEC(FEC *f) { return f->numElem == f->tamVetor; }

/* ---------------------------------------------------------
   Enfileira: insere em fim, depois fim = (fim+1) % tamVetor.
   O % faz o índice "dar a volta" quando chega no final.
   --------------------------------------------------------- */
int enfileira_FEC(FEC *f, void *reg) {
    if (testaCheia_FEC(f)) return FRACASSO;
    memcpy(
        (char*)f->vet + f->fim * f->tamInfo,
        reg,
        f->tamInfo
    );
    f->fim = (f->fim + 1) % f->tamVetor;  /* avança com "volta"      */
    f->numElem++;
    return SUCESSO;
}

/* ---------------------------------------------------------
   Desenfileira: remove de inicio, depois inicio = (inicio+1) % tamVetor.
   --------------------------------------------------------- */
int desenfileira_FEC(FEC *f, void *dest) {
    if (testaVazia_FEC(f)) return FRACASSO;
    memcpy(
        dest,
        (char*)f->vet + f->inicio * f->tamInfo,
        f->tamInfo
    );
    f->inicio = (f->inicio + 1) % f->tamVetor;  /* avança com "volta" */
    f->numElem--;
    return SUCESSO;
}

/* ---------------------------------------------------------
   Busca no início: copia sem remover.
   --------------------------------------------------------- */
int buscaNoInicio_FEC(FEC *f, void *dest) {
    if (testaVazia_FEC(f)) return FRACASSO;
    memcpy(dest, (char*)f->vet + f->inicio * f->tamInfo, f->tamInfo);
    return SUCESSO;
}

int numElementos_FEC(FEC *f) { return f->numElem; }

#endif /* FEC_H */
