/* =========================================================
   teste_PSE.c — Testes da Pilha Simplesmente Encadeada
   Compile: gcc teste_PSE.c -o teste_PSE
   Execute: ./teste_PSE
   ========================================================= */
#include <stdio.h>
#include "PSE.h"

void imprime_PSE(descritorPSE *p) {
    if (testaVazia_PSE(p)) { printf("  [pilha vazia]\n"); return; }
    printf("  topo → ");
    NoPSE *aux = p->topo;
    while (aux != NULL) {
        int val;
        memcpy(&val, aux->dados, p->tamInfo);
        printf("[%d] ", val);
        aux = aux->abaixo;
    }
    printf("← base\n");
}

int main(void) {
    descritorPSE pilha;
    int val, ret;

    printf("=== TESTE DA PILHA SIMPLESMENTE ENCADEADA (PSE) ===\n\n");

    /* --- 1. Criação --- */
    cria_PSE(&pilha, sizeof(int));
    printf("1. PSE criada.\n");
    printf("   Vazia? %s\n\n", testaVazia_PSE(&pilha) ? "SIM" : "NAO");

    /* --- 2. Empilha 5 valores --- */
    printf("2. Empilhando 10, 20, 30, 40, 50:\n");
    for (int i = 1; i <= 5; i++) {
        val = i * 10;
        empilha_PSE(&pilha, &val);
        printf("   empilhou %d\n", val);
    }
    imprime_PSE(&pilha);
    printf("   Total de nós: %d\n\n", contaNos_PSE(&pilha));

    /* --- 3. Busca no topo --- */
    printf("3. Busca no topo:\n");
    buscaNoTopo_PSE(&pilha, &val);
    printf("   Topo = %d (esperado: 50)\n\n", val);

    /* --- 4. Busca na base (questão 1) --- */
    printf("4. Busca na base (Q1):\n");
    buscaNaBase_PSE(&pilha, &val);
    printf("   Base = %d (esperado: 10)\n\n", val);

    /* --- 5. Contagem (questão 5) --- */
    printf("5. Contagem de nós (Q5):\n");
    printf("   contaNos = %d (esperado: 5)\n", contaNos_PSE(&pilha));
    printf("   Pilha preservada após contagem:\n");
    imprime_PSE(&pilha);
    printf("\n");

    /* --- 6. Inversão (questão 2) --- */
    printf("6. Inversão (Q2):\n");
    printf("   Antes:  "); imprime_PSE(&pilha);
    inverte_PSE(&pilha);
    printf("   Depois: "); imprime_PSE(&pilha);
    printf("   (topo deve ser 10, base deve ser 50)\n\n");

    /* --- 7. Desempilha --- */
    printf("7. Desempilhando 3 elementos:\n");
    for (int i = 0; i < 3; i++) {
        desempilha_PSE(&pilha, &val);
        printf("   removeu %d\n", val);
    }
    imprime_PSE(&pilha);
    printf("\n");

    /* --- 8. Esvazia --- */
    printf("8. Esvaziando tudo:\n");
    while (!testaVazia_PSE(&pilha)) {
        desempilha_PSE(&pilha, &val);
        printf("   removeu %d\n", val);
    }
    printf("   Vazia? %s\n\n", testaVazia_PSE(&pilha) ? "SIM" : "NAO");

    /* --- 9. Desempilha com vazia --- */
    printf("9. Desempilha com pilha vazia:\n");
    ret = desempilha_PSE(&pilha, &val);
    printf("   resultado: %s (esperado: FRACASSO)\n\n",
           ret ? "SUCESSO" : "FRACASSO");

    /* --- 10. Inversão de pilha com 1 elemento --- */
    printf("10. Inversão com 1 elemento:\n");
    val = 42; empilha_PSE(&pilha, &val);
    inverte_PSE(&pilha);
    buscaNoTopo_PSE(&pilha, &val);
    printf("    Topo após inverter: %d (esperado: 42)\n\n", val);

    /* --- 11. Destruição --- */
    destroi_PSE(&pilha);
    printf("11. PSE destruída.\n");

    return 0;
}
