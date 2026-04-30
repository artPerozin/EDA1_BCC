#ifndef MPE_H
#define MPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   MPE.h — Multipilha Estática (duas pilhas, mesmo vetor)
   Pilha1 cresce da esquerda para a direita (topo1 sobe).
   Pilha2 cresce da direita para a esquerda (topo2 desce).
   Estão cheias quando topo1+1 == topo2 (se encontram).

   topo1 começa em -1          topo2 começa em tamVetor
   vet: [P1→→→→ ... ←←←←P2]
   ========================================================= */

#ifndef SUCESSO
#define SUCESSO  1
#define FRACASSO 0
#endif

typedef struct {
    int   topo1;     /* índice do topo da Pilha1 (-1 = vazia)        */
    int   topo2;     /* índice do topo da Pilha2 (tamVetor = vazia)  */
    int   tamVetor;  /* tamanho total do vetor compartilhado         */
    int   tamInfo;   /* ambas pilhas usam o mesmo tamInfo aqui       */
    void *vet;
} MultiPilha;

/* ---------------------------------------------------------
   Criação.
   --------------------------------------------------------- */
MultiPilha *cria_MPE(MultiPilha *mp, int tamVetor, int tamInfo) {
    mp->vet = malloc(tamVetor * tamInfo);
    if (!mp->vet) return NULL;
    mp->topo1     = -1;        /* P1 começa vazia                    */
    mp->topo2     = tamVetor;  /* P2 começa vazia                    */
    mp->tamVetor  = tamVetor;
    mp->tamInfo   = tamInfo;
    return mp;
}

MultiPilha *destroi_MPE(MultiPilha *mp) {
    free(mp->vet);
    mp->vet = NULL;
    return mp;
}

/* Reinicializa ambas as pilhas */
int reinicia_MPE(MultiPilha *mp) {
    mp->topo1 = -1;
    mp->topo2 = mp->tamVetor;
    return SUCESSO;
}

/* Reinicializa apenas uma pilha (1 ou 2) */
int reiniciaPilha_MPE(MultiPilha *mp, int idPilha) {
    if (idPilha == 1) { mp->topo1 = -1;             return SUCESSO; }
    if (idPilha == 2) { mp->topo2 = mp->tamVetor;   return SUCESSO; }
    return FRACASSO;
}

/* ---------------------------------------------------------
   Cheia: os dois topos se encontraram.
   --------------------------------------------------------- */
int testaCheia_MPE(MultiPilha *mp) {
    return mp->topo1 + 1 == mp->topo2;
}

int testaVazia_MPE(MultiPilha *mp, int idPilha) {
    if (idPilha == 1) return mp->topo1 == -1;
    if (idPilha == 2) return mp->topo2 == mp->tamVetor;
    return FRACASSO;
}

/* ---------------------------------------------------------
   Empilha na pilha idPilha.
   --------------------------------------------------------- */
int empilha_MPE(MultiPilha *mp, int idPilha, void *reg) {
    if (testaCheia_MPE(mp)) return FRACASSO;  /* vetor lotado        */

    if (idPilha == 1) {
        mp->topo1++;                           /* avança para direita */
        memcpy((char*)mp->vet + mp->topo1 * mp->tamInfo, reg, mp->tamInfo);
        return SUCESSO;
    }
    if (idPilha == 2) {
        mp->topo2--;                           /* avança para esquerda*/
        memcpy((char*)mp->vet + mp->topo2 * mp->tamInfo, reg, mp->tamInfo);
        return SUCESSO;
    }
    return FRACASSO;
}

/* ---------------------------------------------------------
   Desempilha da pilha idPilha.
   --------------------------------------------------------- */
int desempilha_MPE(MultiPilha *mp, int idPilha, void *dest) {
    if (testaVazia_MPE(mp, idPilha)) return FRACASSO;

    if (idPilha == 1) {
        memcpy(dest, (char*)mp->vet + mp->topo1 * mp->tamInfo, mp->tamInfo);
        mp->topo1--;
        return SUCESSO;
    }
    if (idPilha == 2) {
        memcpy(dest, (char*)mp->vet + mp->topo2 * mp->tamInfo, mp->tamInfo);
        mp->topo2++;
        return SUCESSO;
    }
    return FRACASSO;
}

/* ---------------------------------------------------------
   Busca no topo da pilha idPilha (sem remover).
   --------------------------------------------------------- */
int buscaNoTopo_MPE(MultiPilha *mp, int idPilha, void *dest) {
    if (testaVazia_MPE(mp, idPilha)) return FRACASSO;

    if (idPilha == 1) {
        memcpy(dest, (char*)mp->vet + mp->topo1 * mp->tamInfo, mp->tamInfo);
        return SUCESSO;
    }
    if (idPilha == 2) {
        memcpy(dest, (char*)mp->vet + mp->topo2 * mp->tamInfo, mp->tamInfo);
        return SUCESSO;
    }
    return FRACASSO;
}

/* ---------------------------------------------------------
   Número de elementos de uma pilha específica.
   --------------------------------------------------------- */
int numElementos_MPE(MultiPilha *mp, int idPilha) {
    if (idPilha == 1) return mp->topo1 + 1;
    if (idPilha == 2) return mp->tamVetor - mp->topo2;
    return -1;
}

#endif /* MPE_H */
