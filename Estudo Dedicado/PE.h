#ifndef PE_H
#define PE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   PE.h — Pilha Estática (sobre vetor)
   O vetor é alocado na criação e tem tamanho fixo.
   topo == -1  →  pilha vazia
   topo == tamVetor-1  →  pilha cheia
   ========================================================= */

#define SUCESSO 1
#define FRACASSO 0

/* Descritor da pilha estática */
typedef struct
{
    int topo;     /* índice do elemento no topo (-1 = vazia)     */
    int tamVetor; /* capacidade máxima (número de elementos)      */
    int tamInfo;  /* tamanho em bytes de cada elemento            */
    void *vet;    /* vetor de dados alocado dinamicamente         */
} PE;

/* ---------------------------------------------------------
   Criação: aloca o vetor e inicializa o descritor.
   Retorna o ponteiro p preenchido, ou NULL se falhar.
   --------------------------------------------------------- */
PE *cria_PE(PE *p, int tamPilha, int tamInfo)
{
    p->vet = malloc(tamPilha * tamInfo); /* aloca o vetor inteiro de uma vez */
    if (!p->vet)
        return NULL;
    p->topo = -1; /* pilha começa vazia                   */
    p->tamVetor = tamPilha;
    p->tamInfo = tamInfo;
    return p;
}

/* ---------------------------------------------------------
   Destruição: libera o vetor e zera o descritor.
   --------------------------------------------------------- */
PE *destroi_PE(PE *p)
{
    free(p->vet); /* libera o vetor                               */
    p->vet = NULL;
    p->topo = -1;
    p->tamVetor = 0;
    return p;
}

/* ---------------------------------------------------------
   Reinicialização: volta ao estado de recém-criada (vazia).
   Não libera memória — apenas reposiciona o topo.
   --------------------------------------------------------- */
int reinicia_PE(PE *p)
{
    p->topo = -1; /* "apaga" tudo reposicionando o topo           */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Empilha: copia o conteúdo apontado por pRegNovo no topo.
   --------------------------------------------------------- */
int empilha_PE(PE *p, void *pRegNovo)
{
    if (p->topo == p->tamVetor - 1) /* topo no fim → cheia          */
        return FRACASSO;
    p->topo++; /* avança o topo                */
    memcpy(
        (char *)p->vet + p->topo * p->tamInfo, /* destino no vetor   */
        pRegNovo,                              /* origem             */
        p->tamInfo                             /* bytes a copiar     */
    );
    return SUCESSO;
}

/* ---------------------------------------------------------
   Desempilha: copia o topo em pRegExcluido e decrementa.
   --------------------------------------------------------- */
int desempilha_PE(PE *p, void *pRegExcluido)
{
    if (p->topo == -1) /* topo em -1 → vazia           */
        return FRACASSO;
    memcpy(
        pRegExcluido,                          /* destino            */
        (char *)p->vet + p->topo * p->tamInfo, /* origem: topo       */
        p->tamInfo);
    p->topo--; /* remove logicamente           */
    return SUCESSO;
}

/* ---------------------------------------------------------
   Busca no topo: copia sem remover.
   --------------------------------------------------------- */
int buscaNoTopo_PE(PE *p, void *pRegBuscado)
{
    if (p->topo == -1)
        return FRACASSO;
    memcpy(
        pRegBuscado,
        (char *)p->vet + p->topo * p->tamInfo,
        p->tamInfo);
    return SUCESSO; /* topo NÃO é decrementado                      */
}

/* ---------------------------------------------------------
   Testa vazia / cheia.
   --------------------------------------------------------- */
int testaVazia_PE(PE *p) { return p->topo == -1; }
int testaCheia_PE(PE *p) { return p->topo == p->tamVetor - 1; }

/* ---------------------------------------------------------
   Número de elementos empilhados (questão 6).
   Não percorre o vetor — usa o topo diretamente: O(1).
   --------------------------------------------------------- */
int numeroDeEmpilhados_PE(PE *p)
{
    return p->topo + 1; /* topo=-1→0 itens, topo=0→1 item, etc.    */
}

#endif /* PE_H */
