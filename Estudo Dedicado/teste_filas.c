/* =========================================================
   teste_filas.c — Testa FES, FEM e FEC comparativamente
   Compile: gcc teste_filas.c -o teste_filas
   Execute: ./teste_filas
   ========================================================= */
#include <stdio.h>
#include "FES.h"
#include "FEM.h"
#include "FEC.h"

/* --- Helpers de impressão --- */

void imprime_FES(FES *f) {
    if (testaVazia_FES(f)) { printf("  [vazia]\n"); return; }
    printf("  frente → ");
    for (int i = f->inicio; i < f->fim; i++) {
        int v; memcpy(&v, (char*)f->vet + i * f->tamInfo, f->tamInfo);
        printf("[%d] ", v);
    }
    printf("← fim\n");
}

void imprime_FEM(FEM *f) {
    if (testaVazia_FEM(f)) { printf("  [vazia]\n"); return; }
    printf("  frente → ");
    for (int i = 0; i < f->fim; i++) {
        int v; memcpy(&v, (char*)f->vet + i * f->tamInfo, f->tamInfo);
        printf("[%d] ", v);
    }
    printf("← fim\n");
}

void imprime_FEC(FEC *f) {
    if (testaVazia_FEC(f)) { printf("  [vazia]\n"); return; }
    printf("  frente → ");
    for (int i = 0; i < f->numElem; i++) {
        int idx = (f->inicio + i) % f->tamVetor;
        int v; memcpy(&v, (char*)f->vet + idx * f->tamInfo, f->tamInfo);
        printf("[%d] ", v);
    }
    printf("← fim\n");
}

int main(void) {
    FES fes; FEM fem; FEC fec;
    int val, ret;

    /* =====================================================
       BLOCO 1: FES — Fila Estática Simples
       ===================================================== */
    printf("=== 1. FES — Fila Estática Simples ===\n\n");

    cria_FES(&fes, 5, sizeof(int));
    printf("Criada com capacidade 5.\n");

    printf("Enfileirando 10, 20, 30:\n");
    for (int i = 1; i <= 3; i++) { val = i*10; enfileira_FES(&fes, &val); }
    imprime_FES(&fes);
    printf("Elementos: %d\n\n", numElementos_FES(&fes));

    printf("Desenfileirando 2 elementos:\n");
    for (int i = 0; i < 2; i++) {
        desenfileira_FES(&fes, &val);
        printf("  saiu: %d\n", val);
    }
    imprime_FES(&fes);
    printf("inicio=%d fim=%d (espaços [0] e [1] desperdiçados!)\n\n",
           fes.inicio, fes.fim);

    printf("Enfileirando 40, 50, 60, 70 (só 2 cabem — vetor 'cheio'):\n");
    for (int i = 4; i <= 7; i++) {
        val = i*10;
        ret = enfileira_FES(&fes, &val);
        printf("  enfileira(%d) → %s\n", val, ret?"SUCESSO":"FRACASSO");
    }
    imprime_FES(&fes);
    printf("\n");

    destroi_FES(&fes);

    /* =====================================================
       BLOCO 2: FEM — Fila com Movimentação
       ===================================================== */
    printf("=== 2. FEM — Fila com Movimentação ===\n\n");

    cria_FEM(&fem, 5, sizeof(int));
    printf("Enfileirando 10, 20, 30, 40, 50:\n");
    for (int i = 1; i <= 5; i++) { val = i*10; enfileira_FEM(&fem, &val); }
    imprime_FEM(&fem);

    printf("\nDesenfileirando 3 (note que os demais se movem para [0]):\n");
    for (int i = 0; i < 3; i++) {
        desenfileira_FEM(&fem, &val);
        printf("  saiu: %d | fila: ", val); imprime_FEM(&fem);
    }

    printf("\nEnfileirando mais 3 (espaço foi recuperado):\n");
    for (int i = 8; i <= 10; i++) {
        val = i*10; enfileira_FEM(&fem, &val);
        printf("  enfileirou %d | fila: ", val); imprime_FEM(&fem);
    }
    printf("\n");

    destroi_FEM(&fem);

    /* =====================================================
       BLOCO 3: FEC — Fila Estática Circular
       ===================================================== */
    printf("=== 3. FEC — Fila Estática Circular ===\n\n");

    cria_FEC(&fec, 5, sizeof(int));

    printf("Enfileirando 10, 20, 30, 40, 50 (enche o vetor):\n");
    for (int i = 1; i <= 5; i++) { val = i*10; enfileira_FEC(&fec, &val); }
    imprime_FEC(&fec);
    printf("Cheia? %s\n\n", testaCheia_FEC(&fec) ? "SIM" : "NAO");

    printf("Desenfileirando 3:\n");
    for (int i = 0; i < 3; i++) {
        desenfileira_FEC(&fec, &val);
        printf("  saiu: %d\n", val);
    }
    printf("inicio=%d fim=%d numElem=%d\n\n",
           fec.inicio, fec.fim, fec.numElem);

    printf("Enfileirando 60, 70, 80 (%% faz a volta no vetor):\n");
    for (int i = 6; i <= 8; i++) {
        val = i*10;
        ret = enfileira_FEC(&fec, &val);
        printf("  enfileira(%d) → %s | inicio=%d fim=%d\n",
               val, ret?"SUCESSO":"FRACASSO", fec.inicio, fec.fim);
    }
    imprime_FEC(&fec);
    printf("Elementos: %d\n\n", numElementos_FEC(&fec));

    printf("Tentando enfileirar com fila cheia:\n");
    val = 999;
    ret = enfileira_FEC(&fec, &val);
    printf("  enfileira(999) → %s (esperado: FRACASSO)\n\n",
           ret ? "SUCESSO" : "FRACASSO");

    printf("Esvaziando tudo:\n");
    while (!testaVazia_FEC(&fec)) {
        desenfileira_FEC(&fec, &val);
        printf("  saiu: %d\n", val);
    }
    printf("Vazia? %s\n\n", testaVazia_FEC(&fec) ? "SIM" : "NAO");

    printf("Desenfileira com vazia:\n");
    ret = desenfileira_FEC(&fec, &val);
    printf("  resultado: %s (esperado: FRACASSO)\n\n",
           ret ? "SUCESSO" : "FRACASSO");

    destroi_FEC(&fec);

    /* =====================================================
       BLOCO 4: Comparativo — problema do desperdício
       ===================================================== */
    printf("=== 4. Comparativo: por que FEC é melhor que FES ===\n\n");
    printf("FES com 4 posições: enfileira 4, remove 3, tenta enfileirar:\n");
    FES fes2;
    cria_FES(&fes2, 4, sizeof(int));
    for (int i=1;i<=4;i++){val=i*10; enfileira_FES(&fes2,&val);}
    for (int i=0;i<3;i++) desenfileira_FES(&fes2,&val);
    val=99;
    ret = enfileira_FES(&fes2, &val);
    printf("  Enfileira(99) → %s (FRACASSO mesmo com 3 vagas livres!)\n\n",
           ret?"SUCESSO":"FRACASSO");

    printf("FEC com 4 posições: mesma sequência:\n");
    FEC fec2;
    cria_FEC(&fec2, 4, sizeof(int));
    for (int i=1;i<=4;i++){val=i*10; enfileira_FEC(&fec2,&val);}
    for (int i=0;i<3;i++) desenfileira_FEC(&fec2,&val);
    val=99;
    ret = enfileira_FEC(&fec2, &val);
    printf("  Enfileira(99) → %s (SUCESSO! reutilizou o espaço via %%)\n",
           ret?"SUCESSO":"FRACASSO");

    destroi_FES(&fes2);
    destroi_FEC(&fec2);

    return 0;
}
