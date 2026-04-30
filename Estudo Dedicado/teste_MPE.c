/* =========================================================
   teste_MPE.c — Testes da Multipilha Estática
   Duas pilhas concorrendo pelo mesmo vetor.
   Compile: gcc teste_MPE.c -o teste_MPE
   Execute: ./teste_MPE
   ========================================================= */
#include <stdio.h>
#include "MPE.h"

void status(MultiPilha *mp) {
    printf("  topo1=%d  topo2=%d  P1:%d elementos  P2:%d elementos\n",
           mp->topo1, mp->topo2,
           numElementos_MPE(mp, 1),
           numElementos_MPE(mp, 2));
}

int main(void) {
    MultiPilha mp;
    int val, ret;

    printf("=== TESTE MULTIPILHA ESTÁTICA (MPE) ===\n\n");

    /* --- 1. Criação --- */
    cria_MPE(&mp, 8, sizeof(int));
    printf("1. Multipilha criada (vetor de 8 posições).\n");
    status(&mp);
    printf("\n");

    /* --- 2. Empilha na P1 (esquerda → direita) --- */
    printf("2. Empilhando 10, 20, 30 na Pilha 1:\n");
    for (int i = 1; i <= 3; i++) {
        val = i * 10;
        empilha_MPE(&mp, 1, &val);
    }
    status(&mp);
    printf("\n");

    /* --- 3. Empilha na P2 (direita → esquerda) --- */
    printf("3. Empilhando 100, 200, 300 na Pilha 2:\n");
    for (int i = 1; i <= 3; i++) {
        val = i * 100;
        empilha_MPE(&mp, 2, &val);
    }
    status(&mp);
    printf("\n");

    /* --- 4. Busca nos topos --- */
    printf("4. Topo da P1: ");
    buscaNoTopo_MPE(&mp, 1, &val);
    printf("%d (esperado: 30)\n", val);

    printf("   Topo da P2: ");
    buscaNoTopo_MPE(&mp, 2, &val);
    printf("%d (esperado: 300)\n\n", val);

    /* --- 5. Enche o vetor --- */
    printf("5. Enchendo o vetor (2 posições restantes):\n");
    val = 40; ret = empilha_MPE(&mp, 1, &val);
    printf("  empilha(40) P1 → %s\n", ret?"SUCESSO":"FRACASSO");
    val = 400; ret = empilha_MPE(&mp, 2, &val);
    printf("  empilha(400) P2 → %s\n", ret?"SUCESSO":"FRACASSO");
    status(&mp);
    printf("  Cheio? %s\n\n", testaCheia_MPE(&mp) ? "SIM" : "NAO");

    /* --- 6. Tenta empilhar com vetor cheio --- */
    printf("6. Tenta empilhar mais (vetor cheio):\n");
    val = 50; ret = empilha_MPE(&mp, 1, &val);
    printf("  empilha(50) P1 → %s (esperado: FRACASSO)\n\n",
           ret?"SUCESSO":"FRACASSO");

    /* --- 7. Desempilha das duas --- */
    printf("7. Desempilhando 2 de cada pilha:\n");
    for (int i = 0; i < 2; i++) {
        desempilha_MPE(&mp, 1, &val);
        printf("  P1 desempilhou: %d\n", val);
    }
    for (int i = 0; i < 2; i++) {
        desempilha_MPE(&mp, 2, &val);
        printf("  P2 desempilhou: %d\n", val);
    }
    status(&mp);
    printf("\n");

    /* --- 8. Reinicializa apenas P1 --- */
    printf("8. Reinicializa apenas P1:\n");
    reiniciaPilha_MPE(&mp, 1);
    printf("  P1 vazia? %s  |  P2 vazia? %s\n",
           testaVazia_MPE(&mp, 1) ? "SIM" : "NAO",
           testaVazia_MPE(&mp, 2) ? "SIM" : "NAO");
    status(&mp);
    printf("\n");

    /* --- 9. Reinicializa tudo --- */
    printf("9. Reinicializa tudo:\n");
    reinicia_MPE(&mp);
    status(&mp);
    printf("\n");

    /* --- 10. Destruição --- */
    destroi_MPE(&mp);
    printf("10. Multipilha destruída.\n");

    return 0;
}
