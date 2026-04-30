#ifndef FEM_H
#define FEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   FEM.h — Fila Estática com Movimentação (memmove)
   Resolve o desperdício da FES: ao desenfileirar, todos
   os elementos restantes são movidos uma posição para
   a esquerda, de modo que o início sempre fica em [0].

   DESVANTAGEM: desenfileirar é O(n) — lento para filas
   grandes. Solução definitiva: use FEC (circular).
   ========================================================= */

#ifndef SUCESSO
#define SUCESSO  1
#define FRACASSO 0
#endif

typedef struct {
    int   fim;       /* número de elementos / próxima posição livre  */
    int   tamVetor;
    int   tamInfo;
    void *vet;
} FEM;

/* ---------------------------------------------------------
   Criação. O início é sempre 0, por isso não precisamos
   armazená-lo — os dados vivem em vet[0..fim-1].
   --------------------------------------------------------- */
FEM *cria_FEM(FEM *f, int tamVetor, int tamInfo) {
    f->vet = malloc(tamVetor * tamInfo);
    if (!f->vet) return NULL;
    f->fim      = 0;
    f->tamVetor = tamVetor;
    f->tamInfo  = tamInfo;
    return f;
}

FEM *destroi_FEM(FEM *f) {
    free(f->vet);
    f->vet = NULL;
    f->fim = 0;
    return f;
}

int reinicia_FEM(FEM *f) { f->fim = 0; return SUCESSO; }

int testaVazia_FEM(FEM *f) { return f->fim == 0; }
int testaCheia_FEM(FEM *f) { return f->fim == f->tamVetor; }

/* ---------------------------------------------------------
   Enfileira: insere na posição fim (igual à FES).
   --------------------------------------------------------- */
int enfileira_FEM(FEM *f, void *reg) {
    if (testaCheia_FEM(f)) return FRACASSO;
    memcpy((char*)f->vet + f->fim * f->tamInfo, reg, f->tamInfo);
    f->fim++;
    return SUCESSO;
}

/* ---------------------------------------------------------
   Desenfileira: remove vet[0] e desloca tudo para a
   esquerda com memmove. Custo O(n).
   --------------------------------------------------------- */
int desenfileira_FEM(FEM *f, void *dest) {
    if (testaVazia_FEM(f)) return FRACASSO;

    memcpy(dest, f->vet, f->tamInfo);    /* copia o primeiro elemento */

    /* desloca todos os elementos uma posição para a esquerda         */
    memmove(
        f->vet,                                   /* destino: posição 0 */
        (char*)f->vet + f->tamInfo,               /* origem:  posição 1 */
        (f->fim - 1) * f->tamInfo                 /* bytes a mover      */
    );
    f->fim--;   /* agora há um elemento a menos                       */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Busca no início: copia vet[0] sem remover.
   --------------------------------------------------------- */
int buscaNoInicio_FEM(FEM *f, void *dest) {
    if (testaVazia_FEM(f)) return FRACASSO;
    memcpy(dest, f->vet, f->tamInfo);
    return SUCESSO;
}

int numElementos_FEM(FEM *f) { return f->fim; }

#endif /* FEM_H */
