/*
 * pilha.c  +  pilha.h  (implementação e interface da PDE)
 * --------------------------------------------------------
 * Pilha Duplamente Encadeada (PDE) genérica.
 *
 * Cada nó possui dois ponteiros:
 *   acima  -> aponta para o nó que está acima na pilha (mais recente)
 *   abaixo -> aponta para o nó que está abaixo na pilha (mais antigo)
 *
 * O campo "Topo" do cabeçalho aponta sempre para o nó mais recente.
 * O campo "TamInfo" guarda o tamanho em bytes de cada dado armazenado,
 * permitindo que a pilha seja verdadeiramente genérica (void*).
 *
 * Interface exposta (mesma da PSE disponível no Moodle):
 *   criarPilha   – aloca e inicializa o cabeçalho
 *   destruirPilha– libera todos os nós e o cabeçalho
 *   push         – empilha um elemento
 *   pop          – desempilha um elemento
 *   topo         – consulta o topo sem remover
 *   pilhaVazia   – retorna 1 se a pilha está vazia, 0 caso contrário
 *   tamanhoPilha – retorna o número de elementos
 *
 * Disciplina: EDA - Estruturas de Dados e Algoritmos
 */

/* ══════════════════════════════════════════════════════════════════════════
 *  Implementação
 * ══════════════════════════════════════════════════════════════════════════ */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pilha.h" /* interface pública da PDE */

/* ------------------------------------------------------------------
 * criarPilha
 * Aloca e inicializa o cabeçalho da pilha.
 * tamInfo: sizeof do tipo que será armazenado (ex.: sizeof(Coord))
 * Retorna: ponteiro para a pilha criada, ou NULL em caso de falha.
 * ------------------------------------------------------------------ */
Pilha *criarPilha(size_t tamInfo)
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    if (!p)
    {
        fprintf(stderr, "[ERRO] criarPilha: falha ao alocar cabeçalho.\n");
        return NULL;
    }
    p->topo = NULL;
    p->tamInfo = tamInfo;
    p->tamanho = 0;
    return p;
}

/* ------------------------------------------------------------------
 * destruirPilha
 * Libera todos os nós e, por fim, o próprio cabeçalho.
 * Após chamar esta função, o ponteiro p não é mais válido.
 * ------------------------------------------------------------------ */
void destruirPilha(Pilha *p)
{
    if (!p)
        return;

    No *atual = p->topo;
    while (atual)
    {
        No *anterior = atual->abaixo; /* guarda referência ao nó de baixo */
        free(atual->dados);           /* libera a cópia do dado            */
        free(atual);                  /* libera o nó                       */
        atual = anterior;
    }
    free(p); /* libera o cabeçalho                                     */
}

/* ------------------------------------------------------------------
 * push
 * Empilha uma CÓPIA do dado apontado por 'dado'.
 * Retorna 1 em sucesso, 0 em falha.
 * ------------------------------------------------------------------ */
int push(Pilha *p, const void *dado)
{
    if (!p || !dado)
        return 0;

    /* Aloca o novo nó */
    No *novo = (No *)malloc(sizeof(No));
    if (!novo)
    {
        fprintf(stderr, "[ERRO] push: falha ao alocar nó.\n");
        return 0;
    }

    /* Aloca espaço para a cópia do dado e copia os bytes */
    novo->dados = malloc(p->tamInfo);
    if (!novo->dados)
    {
        fprintf(stderr, "[ERRO] push: falha ao alocar dado.\n");
        free(novo);
        return 0;
    }
    memcpy(novo->dados, dado, p->tamInfo);

    /* Encadeia: novo nó aponta para baixo (topo atual) */
    novo->abaixo = p->topo;
    novo->acima = NULL; /* novo nó é o topo: não há nada acima       */

    /* O antigo topo passa a apontar para cima (novo nó) */
    if (p->topo)
    {
        p->topo->acima = novo;
    }

    /* Atualiza o cabeçalho */
    p->topo = novo;
    p->tamanho++;
    return 1;
}

/* ------------------------------------------------------------------
 * pop
 * Remove o nó do topo e copia seu dado para 'destino'.
 * Retorna 1 em sucesso, 0 se a pilha estiver vazia.
 * ------------------------------------------------------------------ */
int pop(Pilha *p, void *destino)
{
    if (!p || !p->topo)
        return 0; /* pilha vazia                        */

    No *removido = p->topo;

    /* Copia o dado para o destino fornecido pelo chamador */
    if (destino)
    {
        memcpy(destino, removido->dados, p->tamInfo);
    }

    /* Atualiza o topo para o nó que estava abaixo */
    p->topo = removido->abaixo;
    if (p->topo)
    {
        p->topo->acima = NULL; /* novo topo não tem mais nada acima    */
    }

    /* Libera o nó removido */
    free(removido->dados);
    free(removido);
    p->tamanho--;
    return 1;
}

/* ------------------------------------------------------------------
 * topo
 * Copia o dado do topo para 'destino' SEM remover o nó.
 * Retorna 1 em sucesso, 0 se a pilha estiver vazia.
 * ------------------------------------------------------------------ */
int topo(const Pilha *p, void *destino)
{
    if (!p || !p->topo || !destino)
        return 0;
    memcpy(destino, p->topo->dados, p->tamInfo);
    return 1;
}

/* ------------------------------------------------------------------
 * pilhaVazia
 * Retorna 1 se a pilha não contém elementos, 0 caso contrário.
 * ------------------------------------------------------------------ */
int pilhaVazia(const Pilha *p)
{
    return (!p || p->tamanho == 0) ? 1 : 0;
}

/* ------------------------------------------------------------------
 * tamanhoPilha
 * Retorna o número de elementos atualmente na pilha.
 * ------------------------------------------------------------------ */
int tamanhoPilha(const Pilha *p)
{
    return p ? p->tamanho : 0;
}