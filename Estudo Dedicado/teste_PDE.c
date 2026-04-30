/* =========================================================
   teste_PDE.c — Testes da Pilha Duplamente Encadeada
   Compile: gcc teste_PDE.c -o teste_PDE
   Execute: ./teste_PDE
   ========================================================= */
#include <stdio.h>
#include "PDE.h"

/* Imprime do topo à base usando ponteiro "abaixo" */
void imprime_de_cima(descritorPDE *p) {
    if (testaVazia_PDE(p)) { printf("  [vazia]\n"); return; }
    printf("  topo → ");
    NoPDE *aux = p->topo;
    while (aux != NULL) {
        int v; memcpy(&v, aux->dados, p->tamInfo);
        printf("[%d] ", v);
        aux = aux->abaixo;
    }
    printf("← base\n");
}

/* Imprime da base ao topo usando ponteiro "acima"
   Para isso, desce até a base primeiro. */
void imprime_de_baixo(descritorPDE *p) {
    if (testaVazia_PDE(p)) { printf("  [vazia]\n"); return; }
    /* desce até a base */
    NoPDE *aux = p->topo;
    while (aux->abaixo != NULL) aux = aux->abaixo;
    /* sobe usando "acima" */
    printf("  base → ");
    while (aux != NULL) {
        int v; memcpy(&v, aux->dados, p->tamInfo);
        printf("[%d] ", v);
        aux = aux->acima;
    }
    printf("← topo\n");
}

/* Verifica consistência dos ponteiros acima/abaixo */
void verifica_links(descritorPDE *p) {
    NoPDE *aux = p->topo;
    int ok = 1;
    while (aux != NULL && aux->abaixo != NULL) {
        /* o nó abaixo deve ter "acima" apontando de volta para aux */
        if (aux->abaixo->acima != aux) { ok = 0; break; }
        aux = aux->abaixo;
    }
    printf("  Links acima/abaixo consistentes? %s\n", ok ? "SIM" : "NAO");
}

int main(void) {
    descritorPDE pilha;
    int val, ret;

    printf("=== TESTE DA PILHA DUPLAMENTE ENCADEADA (PDE) ===\n\n");

    /* --- 1. Criação --- */
    cria_PDE(&pilha, sizeof(int));
    printf("1. PDE criada.\n");
    printf("   Vazia? %s\n\n", testaVazia_PDE(&pilha) ? "SIM" : "NAO");

    /* --- 2. Empilha --- */
    printf("2. Empilhando 10, 20, 30, 40, 50:\n");
    for (int i = 1; i <= 5; i++) {
        val = i * 10;
        empilha_PDE(&pilha, &val);
    }
    printf("   De cima: "); imprime_de_cima(&pilha);
    printf("   De baixo:"); imprime_de_baixo(&pilha);
    verifica_links(&pilha);
    printf("   Total: %d nós\n\n", contaNos_PDE(&pilha));

    /* --- 3. Busca no topo --- */
    printf("3. Busca no topo:\n");
    buscaNoTopo_PDE(&pilha, &val);
    printf("   Topo = %d (esperado: 50)\n\n", val);

    /* --- 4. Inversão (questão 4) --- */
    printf("4. Inversão (Q4):\n");
    printf("   Antes:  "); imprime_de_cima(&pilha);
    inverte_PDE(&pilha);
    printf("   Depois: "); imprime_de_cima(&pilha);
    printf("   (topo deve ser 10, base deve ser 50)\n");
    verifica_links(&pilha);
    printf("\n");

    /* --- 5. Inverte de volta --- */
    printf("5. Inverte novamente (deve voltar ao original):\n");
    inverte_PDE(&pilha);
    printf("   "); imprime_de_cima(&pilha);
    verifica_links(&pilha);
    printf("\n");

    /* --- 6. Desempilha --- */
    printf("6. Desempilhando 2 elementos:\n");
    for (int i = 0; i < 2; i++) {
        desempilha_PDE(&pilha, &val);
        printf("   removeu %d\n", val);
    }
    printf("   "); imprime_de_cima(&pilha);
    verifica_links(&pilha);
    printf("\n");

    /* --- 7. Esvazia --- */
    printf("7. Esvaziando tudo:\n");
    while (!testaVazia_PDE(&pilha)) {
        desempilha_PDE(&pilha, &val);
        printf("   removeu %d\n", val);
    }
    printf("   Vazia? %s\n\n", testaVazia_PDE(&pilha) ? "SIM" : "NAO");

    /* --- 8. Inversão com pilha vazia --- */
    printf("8. Inversão com pilha vazia:\n");
    ret = inverte_PDE(&pilha);
    printf("   resultado: %s (esperado: FRACASSO)\n\n",
           ret ? "SUCESSO" : "FRACASSO");

    /* --- 9. Destruição --- */
    destroi_PDE(&pilha);
    printf("9. PDE destruída.\n");

    return 0;
}
