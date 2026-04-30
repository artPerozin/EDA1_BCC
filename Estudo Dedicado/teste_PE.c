/* =========================================================
   teste_PE.c — Testes da Pilha Estática (PE)
   Compile: gcc teste_PE.c -o teste_PE
   Execute: ./teste_PE
   ========================================================= */
#include <stdio.h>
#include "PE.h"

/* Imprime o conteúdo atual da pilha (do topo à base) */
void imprime_PE(PE *p) {
    if (testaVazia_PE(p)) {
        printf("  [pilha vazia]\n");
        return;
    }
    printf("  topo → ");
    /* percorre do topo (índice alto) até a base (índice 0) */
    for (int i = p->topo; i >= 0; i--) {
        int val;
        memcpy(&val, (char*)p->vet + i * p->tamInfo, p->tamInfo);
        printf("[%d] ", val);
    }
    printf("← base\n");
}

int main(void) {
    PE pilha;          /* descritor da pilha (variável local)        */
    int val, ret;

    printf("=== TESTE DA PILHA ESTÁTICA (PE) ===\n\n");

    /* --- 1. Criação --- */
    cria_PE(&pilha, 5, sizeof(int));  /* capacidade 5, elementos int */
    printf("1. Pilha criada com capacidade 5.\n");
    printf("   Vazia? %s\n", testaVazia_PE(&pilha) ? "SIM" : "NAO");
    printf("   Elementos: %d\n\n", numeroDeEmpilhados_PE(&pilha));

    /* --- 2. Empilhamento --- */
    printf("2. Empilhando 10, 20, 30, 40, 50...\n");
    for (int i = 1; i <= 5; i++) {
        val = i * 10;
        ret = empilha_PE(&pilha, &val);
        printf("   empilha(%d) → %s\n", val, ret ? "SUCESSO" : "FRACASSO");
    }
    imprime_PE(&pilha);
    printf("   Elementos: %d\n\n", numeroDeEmpilhados_PE(&pilha));

    /* --- 3. Tenta empilhar com pilha cheia --- */
    printf("3. Tentando empilhar 60 (pilha cheia)...\n");
    val = 60;
    ret = empilha_PE(&pilha, &val);
    printf("   empilha(60) → %s (esperado: FRACASSO)\n\n",
           ret ? "SUCESSO" : "FRACASSO");

    /* --- 4. Busca no topo --- */
    printf("4. Busca no topo (sem remover):\n");
    buscaNoTopo_PE(&pilha, &val);
    printf("   Topo = %d (esperado: 50)\n\n", val);

    /* --- 5. Desempilhamento --- */
    printf("5. Desempilhando 3 elementos:\n");
    for (int i = 0; i < 3; i++) {
        desempilha_PE(&pilha, &val);
        printf("   desempilhou %d\n", val);
    }
    imprime_PE(&pilha);
    printf("   Elementos restantes: %d\n\n", numeroDeEmpilhados_PE(&pilha));

    /* --- 6. Empilha mais para testar reuso do espaço --- */
    printf("6. Empilhando 99 e 88 após remoções:\n");
    val = 99; empilha_PE(&pilha, &val);
    val = 88; empilha_PE(&pilha, &val);
    imprime_PE(&pilha);
    printf("\n");

    /* --- 7. Esvazia tudo --- */
    printf("7. Esvaziando a pilha:\n");
    while (!testaVazia_PE(&pilha)) {
        desempilha_PE(&pilha, &val);
        printf("   removeu %d\n", val);
    }
    printf("   Vazia agora? %s\n\n", testaVazia_PE(&pilha) ? "SIM" : "NAO");

    /* --- 8. Desempilha com pilha vazia --- */
    printf("8. Tentando desempilhar pilha vazia:\n");
    ret = desempilha_PE(&pilha, &val);
    printf("   desempilha() → %s (esperado: FRACASSO)\n\n",
           ret ? "SUCESSO" : "FRACASSO");

    /* --- 9. Reinicia --- */
    printf("9. Empilha 1,2,3 depois reinicia:\n");
    for (int i = 1; i <= 3; i++) { val = i; empilha_PE(&pilha, &val); }
    imprime_PE(&pilha);
    reinicia_PE(&pilha);
    printf("   Após reinicia → Vazia? %s\n\n",
           testaVazia_PE(&pilha) ? "SIM" : "NAO");

    /* --- 10. Destruição --- */
    destroi_PE(&pilha);
    printf("10. Pilha destruída.\n");

    return 0;
}
