#ifndef PDE_H
#define PDE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   PDE.h — Pilha Duplamente Encadeada
   Igual à PSE, mas cada nó tem dois ponteiros:
     abaixo → nó mais antigo (direção da base)
     acima  → nó mais novo   (direção do topo)
   O nó do topo tem acima == NULL.
   O nó da base tem abaixo == NULL.
   ========================================================= */

#ifndef SUCESSO
#define SUCESSO  1
#define FRACASSO 0
#endif

/* Nó da pilha duplamente encadeada */
typedef struct NoPDE {
    void          *dados;   /* dados armazenados neste nó            */
    struct NoPDE  *abaixo;  /* aponta para o nó mais antigo          */
    struct NoPDE  *acima;   /* aponta para o nó mais novo            */
} NoPDE;

/* Descritor da PDE */
typedef struct {
    NoPDE *topo;     /* aponta para o nó do topo (NULL = vazia)      */
    int    tamInfo;
} descritorPDE;

/* ---------------------------------------------------------
   Criação.
   --------------------------------------------------------- */
descritorPDE *cria_PDE(descritorPDE *p, int tamInfo) {
    p->topo    = NULL;
    p->tamInfo = tamInfo;
    return p;
}

/* ---------------------------------------------------------
   Empilha: aloca novo nó e ajusta os dois ponteiros.
   --------------------------------------------------------- */
int empilha_PDE(descritorPDE *p, void *novo) {
    NoPDE *temp = (NoPDE*)malloc(sizeof(NoPDE));
    if (!temp) return FRACASSO;

    temp->dados = malloc(p->tamInfo);
    if (!temp->dados) { free(temp); return FRACASSO; }

    memcpy(temp->dados, novo, p->tamInfo);

    temp->abaixo = p->topo;   /* novo nó aponta pra baixo pro antigo topo  */
    temp->acima  = NULL;      /* novo topo não tem ninguém acima            */

    if (p->topo != NULL)
        p->topo->acima = temp; /* antigo topo passa a enxergar o novo acima */

    p->topo = temp;            /* atualiza o topo                           */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Desempilha: remove o topo e ajusta o ponteiro acima.
   --------------------------------------------------------- */
int desempilha_PDE(descritorPDE *p, void *dest) {
    if (!p->topo) return FRACASSO;

    NoPDE *temp = p->topo;
    memcpy(dest, temp->dados, p->tamInfo);

    p->topo = temp->abaixo;           /* topo desce um nível          */
    if (p->topo != NULL)
        p->topo->acima = NULL;        /* novo topo não tem mais acima */

    free(temp->dados);
    free(temp);
    return SUCESSO;
}

/* ---------------------------------------------------------
   Busca no topo: copia sem remover.
   --------------------------------------------------------- */
int buscaNoTopo_PDE(descritorPDE *p, void *dest) {
    if (!p->topo) return FRACASSO;
    memcpy(dest, p->topo->dados, p->tamInfo);
    return SUCESSO;
}

/* ---------------------------------------------------------
   Testa vazia.
   --------------------------------------------------------- */
int testaVazia_PDE(descritorPDE *p) { return p->topo == NULL; }

/* ---------------------------------------------------------
   Conta nós: percorre sem modificar.
   --------------------------------------------------------- */
int contaNos_PDE(descritorPDE *p) {
    int cont = 0;
    NoPDE *aux = p->topo;
    while (aux != NULL) { cont++; aux = aux->abaixo; }
    return cont;
}

/* ---------------------------------------------------------
   Inversão (questão 4):
   Desce até a base, depois sobe trocando acima <-> abaixo
   em cada nó. O antigo nó da base vira o novo topo.
   --------------------------------------------------------- */
int inverte_PDE(descritorPDE *p) {
    if (!p->topo) return FRACASSO;

    /* 1. Desce até a base */
    NoPDE *atual = p->topo;
    while (atual->abaixo != NULL)
        atual = atual->abaixo;

    NoPDE *novoTopo = atual;  /* base vira topo                       */

    /* 2. Sobe trocando os ponteiros de cada nó */
    while (atual != NULL) {
        NoPDE *temp  = atual->acima;   /* guarda quem estava acima    */
        atual->acima  = atual->abaixo; /* o que era abaixo vira acima */
        atual->abaixo = temp;          /* o que era acima vira abaixo */
        atual = temp;                  /* sobe (temp = acima original)*/
    }

    p->topo = novoTopo;
    return SUCESSO;
}

/* ---------------------------------------------------------
   Destruição: libera todos os nós.
   --------------------------------------------------------- */
descritorPDE *destroi_PDE(descritorPDE *p) {
    NoPDE *aux;
    while (p->topo != NULL) {
        aux     = p->topo;
        p->topo = aux->abaixo;
        free(aux->dados);
        free(aux);
    }
    return p;
}

#endif /* PDE_H */
