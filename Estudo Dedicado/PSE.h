#ifndef PSE_H
#define PSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   PSE.h — Pilha Simplesmente Encadeada
   Cada nó é alocado individualmente no heap.
   O campo "abaixo" encadeia os nós do topo à base.
   topo == NULL  →  pilha vazia
   Não há limite de capacidade (só a memória disponível).
   ========================================================= */

#ifndef SUCESSO
#define SUCESSO  1
#define FRACASSO 0
#endif

/* Nó da pilha encadeada */
typedef struct NoPSE {
    void          *dados;   /* ponteiro para os dados deste nó       */
    struct NoPSE  *abaixo;  /* ponteiro para o nó mais antigo        */
} NoPSE;

/* Descritor da PSE */
typedef struct {
    NoPSE *topo;     /* aponta para o nó do topo (NULL = vazia)      */
    int    tamInfo;  /* tamanho em bytes de cada elemento             */
} descritorPSE;

/* ---------------------------------------------------------
   Criação: inicializa o descritor (não aloca nós ainda).
   --------------------------------------------------------- */
descritorPSE *cria_PSE(descritorPSE *p, int tamInfo) {
    p->topo    = NULL;
    p->tamInfo = tamInfo;
    return p;
}

/* ---------------------------------------------------------
   Empilha: aloca um novo nó e o coloca no topo.
   --------------------------------------------------------- */
int empilha_PSE(descritorPSE *p, void *novo) {
    NoPSE *temp = (NoPSE*)malloc(sizeof(NoPSE));
    if (!temp) return FRACASSO;              /* sem memória           */

    temp->dados = malloc(p->tamInfo);        /* aloca espaço p/ dados */
    if (!temp->dados) { free(temp); return FRACASSO; }

    memcpy(temp->dados, novo, p->tamInfo);   /* copia os dados        */
    temp->abaixo = p->topo;  /* novo nó aponta para o antigo topo     */
    p->topo      = temp;     /* novo nó passa a ser o topo            */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Desempilha: copia dados do topo, remove e libera o nó.
   --------------------------------------------------------- */
int desempilha_PSE(descritorPSE *p, void *dest) {
    if (!p->topo) return FRACASSO;           /* pilha vazia           */

    NoPSE *temp = p->topo;                   /* salva o nó do topo    */
    memcpy(dest, temp->dados, p->tamInfo);   /* copia os dados        */
    p->topo = temp->abaixo;                  /* topo desce um nível   */
    free(temp->dados);                       /* libera dados          */
    free(temp);                              /* libera o nó           */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Busca no topo: copia sem remover.
   --------------------------------------------------------- */
int buscaNoTopo_PSE(descritorPSE *p, void *dest) {
    if (!p->topo) return FRACASSO;
    memcpy(dest, p->topo->dados, p->tamInfo);
    return SUCESSO;  /* topo não é alterado                           */
}

/* ---------------------------------------------------------
   Busca na base (questão 1): percorre até o último nó.
   --------------------------------------------------------- */
int buscaNaBase_PSE(descritorPSE *p, void *dest) {
    if (!p->topo) return FRACASSO;
    NoPSE *aux = p->topo;
    while (aux->abaixo != NULL)   /* desce até o nó sem filho        */
        aux = aux->abaixo;
    memcpy(dest, aux->dados, p->tamInfo);
    return SUCESSO;
}

/* ---------------------------------------------------------
   Conta nós (questão 5): percorre sem modificar a pilha.
   --------------------------------------------------------- */
int contaNos_PSE(descritorPSE *p) {
    int cont = 0;
    NoPSE *aux = p->topo;
    while (aux != NULL) {
        cont++;
        aux = aux->abaixo;
    }
    return cont;  /* pilha preservada — nenhum nó foi removido        */
}

/* ---------------------------------------------------------
   Testa vazia / cheia (encadeada nunca está "cheia").
   --------------------------------------------------------- */
int testaVazia_PSE(descritorPSE *p) { return p->topo == NULL; }
int testaCheia_PSE(descritorPSE *p) { (void)p; return 0; } /* sempre cabe mais */

/* ---------------------------------------------------------
   Inversão (questão 2): inverte os ponteiros "abaixo".
   Não move dados entre nós — apenas redireciona os links.
   --------------------------------------------------------- */
int inverte_PSE(descritorPSE *p) {
    if (!p->topo) return FRACASSO;  /* vazia, nada a fazer            */

    NoPSE *anterior = NULL;         /* será o novo "abaixo" do atual  */
    NoPSE *atual    = p->topo;
    NoPSE *proximo;

    while (atual != NULL) {
        proximo        = atual->abaixo; /* GUARDA próximo antes de perder */
        atual->abaixo  = anterior;      /* INVERTE o link                 */
        anterior       = atual;         /* avança anterior                */
        atual          = proximo;       /* avança atual                   */
    }
    p->topo = anterior; /* último visitado = antiga base = novo topo  */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Destruição: libera todos os nós da pilha.
   --------------------------------------------------------- */
descritorPSE *destroi_PSE(descritorPSE *p) {
    NoPSE *aux;
    while (p->topo != NULL) {
        aux     = p->topo;
        p->topo = aux->abaixo;
        free(aux->dados);
        free(aux);
    }
    return p;
}

#endif /* PSE_H */
