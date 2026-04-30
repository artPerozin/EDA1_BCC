/* =========================================================
   teste_aplicacoes.c — Aplicações práticas (questão 13)
   Usa PE para: verificar parênteses e converter decimal→binário
   Compile: gcc teste_aplicacoes.c -o teste_aplicacoes
   Execute: ./teste_aplicacoes
   ========================================================= */
#include <stdio.h>
#include <string.h>
#include "PE.h"

/* =========================================================
   APLICAÇÃO 1 — Verificação de parênteses/colchetes/chaves
   Questão 13b: ex: ([x^{z+y}-t]*[z+w]/x)
   Algoritmo:
     - Abre '(' '[' '{' → empilha
     - Fecha ')' ']' '}' → desempilha e verifica se o par bate
     - No final: pilha deve estar vazia
   ========================================================= */
int parBate(char abre, char fecha) {
    return (abre=='(' && fecha==')') ||
           (abre=='[' && fecha==']') ||
           (abre=='{' && fecha=='}');
}

int verificaAninhamento(const char *expr) {
    PE pilha;
    char ch, topo;
    cria_PE(&pilha, (int)strlen(expr), sizeof(char));

    for (int i = 0; expr[i] != '\0'; i++) {
        ch = expr[i];
        if (ch=='(' || ch=='[' || ch=='{') {
            empilha_PE(&pilha, &ch);   /* abre: empilha             */
        } else if (ch==')' || ch==']' || ch=='}') {
            if (testaVazia_PE(&pilha)) {
                destroi_PE(&pilha);
                return 0;              /* fechou sem abrir          */
            }
            buscaNoTopo_PE(&pilha, &topo);
            desempilha_PE(&pilha, &topo);
            if (!parBate(topo, ch)) {  /* par errado                */
                destroi_PE(&pilha);
                return 0;
            }
        }
    }
    int resultado = testaVazia_PE(&pilha); /* vazia = tudo fechado   */
    destroi_PE(&pilha);
    return resultado;
}

/* =========================================================
   APLICAÇÃO 2 — Conversão decimal → binário (questão 13e)
   Algoritmo: divide por 2 repetidamente, empilha os restos.
   Ao desempilhar, os bits saem na ordem correta (MSB primeiro).
   ========================================================= */
void decimalParaBinario(int n) {
    PE pilha;
    cria_PE(&pilha, 32, sizeof(int)); /* int tem no máx 32 bits     */

    int original = n;
    if (n == 0) { printf("0"); destroi_PE(&pilha); return; }

    /* divide por 2 e empilha os restos */
    while (n > 0) {
        int resto = n % 2;    /* resto é 0 ou 1                     */
        empilha_PE(&pilha, &resto);
        n = n / 2;            /* próxima divisão                    */
    }

    /* desempilha: o último resto empilhado é o bit mais significativo */
    printf("%d em binário = ", original);
    int bit;
    while (!testaVazia_PE(&pilha)) {
        desempilha_PE(&pilha, &bit);
        printf("%d", bit);
    }
    printf("\n");
    destroi_PE(&pilha);
}

/* =========================================================
   APLICAÇÃO 3 — Avaliação de expressão pós-fixa (questão 13a)
   Exemplo: "3 4 + 2 *"  equivale a (3+4)*2 = 14
   Algoritmo:
     - Número → empilha
     - Operador → desempilha dois, opera, empilha resultado
   ========================================================= */
int avaliaPosFixa(const char *expr) {
    PE pilha;
    cria_PE(&pilha, 50, sizeof(int));
    int a, b, res;

    /* percorre token por token (separados por espaço) */
    char buf[256];
    strncpy(buf, expr, sizeof(buf)-1);
    char *tok = strtok(buf, " ");

    while (tok != NULL) {
        if (tok[0] >= '0' && tok[0] <= '9') {
            /* é um número: converte e empilha */
            int num = atoi(tok);
            empilha_PE(&pilha, &num);
        } else {
            /* é um operador: desempilha dois operandos */
            desempilha_PE(&pilha, &b);  /* b foi empilhado por último */
            desempilha_PE(&pilha, &a);
            switch (tok[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = b != 0 ? a / b : 0; break;
                default:  res = 0;
            }
            empilha_PE(&pilha, &res);  /* empilha o resultado        */
        }
        tok = strtok(NULL, " ");
    }

    desempilha_PE(&pilha, &res);   /* resultado final               */
    destroi_PE(&pilha);
    return res;
}

/* =========================================================
   MAIN
   ========================================================= */
int main(void) {

    /* --- Aplicação 1: Verificação de aninhamento --- */
    printf("=== APLICAÇÃO 1: Verificação de parênteses ===\n\n");

    const char *exprs[] = {
        "([x^{z+y}-t]*[z+w]/x)",   /* correto                      */
        "((a+b)*c)",                 /* correto                      */
        "([)]",                      /* errado: par incompatível     */
        "((a+b)",                    /* errado: falta fechar         */
        "(a+b))",                    /* errado: fecha demais         */
        "{[()]}"                     /* correto                      */
    };
    int n = sizeof(exprs)/sizeof(exprs[0]);
    for (int i = 0; i < n; i++) {
        printf("  \"%s\"  →  %s\n",
               exprs[i],
               verificaAninhamento(exprs[i]) ? "CORRETO" : "ERRADO");
    }

    /* --- Aplicação 2: Decimal → binário --- */
    printf("\n=== APLICAÇÃO 2: Decimal → Binário ===\n\n");
    int nums[] = {0, 1, 5, 10, 42, 255, 1024};
    for (int i = 0; i < 7; i++)
        decimalParaBinario(nums[i]);

    /* --- Aplicação 3: Expressão pós-fixa --- */
    printf("\n=== APLICAÇÃO 3: Expressão pós-fixa ===\n\n");

    /* "3 4 +" = 3+4 = 7 */
    printf("  \"3 4 +\"         = %d  (esperado: 7)\n",
           avaliaPosFixa("3 4 +"));

    /* "3 4 + 2 *" = (3+4)*2 = 14 */
    printf("  \"3 4 + 2 *\"     = %d  (esperado: 14)\n",
           avaliaPosFixa("3 4 + 2 *"));

    /* "5 1 2 + 4 * + 3 -" = 5+(1+2)*4-3 = 5+12-3 = 14 */
    printf("  \"5 1 2 + 4 * + 3 -\" = %d  (esperado: 14)\n",
           avaliaPosFixa("5 1 2 + 4 * + 3 -"));

    /* "10 2 /" = 10/2 = 5 */
    printf("  \"10 2 /\"        = %d  (esperado: 5)\n",
           avaliaPosFixa("10 2 /"));

    return 0;
}
