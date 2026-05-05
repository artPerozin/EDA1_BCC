/*
 * aplicacao.c
 * -----------
 * Aplicação principal: lê uma matriz binária (0s e 1s) de um arquivo texto,
 * identifica os "objetos" (componentes conexos formados por 1s), exibe a
 * distribuição de tamanhos, salva em arquivo a matriz com apenas o maior
 * objeto, e calcula o centro geométrico desse objeto.
 *
 * A busca em largura (BFS) é realizada de forma ITERATIVA usando a PDE
 * (Pilha Duplamente Encadeada) implementada em pilha.c como estrutura
 * auxiliar — sem nenhuma chamada recursiva.
 *
 * Algoritmo utilizado: Rotulação de componentes conexos (Connected Component
 * Labeling) com vizinhança de 4 (cima, baixo, esquerda, direita).
 *
 *   Passos:
 *   1. Ler a matriz do arquivo de entrada.
 *   2. Percorrer cada célula. Se for 1 e ainda não rotulada:
 *      a. Atribuir um novo rótulo (label) ao componente.
 *      b. Usar a pilha para expandir o componente célula a célula
 *         (BFS iterativa), marcando cada célula visitada com o rótulo.
 *      c. Contar o tamanho do componente.
 *   3. Determinar o maior componente.
 *   4. Gerar a matriz de saída (apenas o maior componente).
 *   5. Calcular e exibir o centro geométrico do maior objeto.
 *
 * Compilação (exemplo):
 *   gcc -Wall -o app aplicacao.c pilha.c -lm
 *
 * Uso:
 *   ./app entrada.txt saida.txt
 *
 * Disciplina: EDA - Estruturas de Dados e Algoritmos
 */

/* ══════════════════════════════════════════════════════════════════════════
 *  Inclusões
 * ══════════════════════════════════════════════════════════════════════════ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> /* round() – compile com -lm */

#include "arq.h"   /* Matriz, Coord, MAX_DIM    */
#include "pilha.h" /* PDE: Pilha, push, pop … */

/* ══════════════════════════════════════════════════════════════════════════
 *  Constantes e tipos auxiliares
 * ══════════════════════════════════════════════════════════════════════════ */

/* Número máximo de componentes distintos que podemos rotular */
#define MAX_LABELS (MAX_DIM * MAX_DIM)

/* Matriz de rótulos: cada célula recebe 0 (não visitada) ou um rótulo ≥ 1 */
static int rotulos[MAX_DIM][MAX_DIM];

/* Tamanho de cada componente indexado pelo rótulo */
static int tamComponente[MAX_LABELS];

/* Vizinhança de 4 (delta linha, delta coluna) */
static const int dLin[] = {-1, 1, 0, 0};
static const int dCol[] = {0, 0, -1, 1};
#define NUM_VIZ 4

/* ══════════════════════════════════════════════════════════════════════════
 *  lerMatriz
 *  Lê o arquivo texto e preenche a estrutura Matriz.
 *  Formato: cada linha do arquivo é uma linha da matriz; valores separados
 *  por espaço (0 ou 1).  Linhas em branco são tratadas como linha de zeros.
 *  Retorna 1 em sucesso, 0 em falha.
 * ══════════════════════════════════════════════════════════════════════════ */
int lerMatriz(const char *nomeArq, Matriz *mat)
{
    FILE *f = fopen(nomeArq, "r");
    if (!f)
    {
        fprintf(stderr, "[ERRO] lerMatriz: não foi possível abrir '%s'.\n", nomeArq);
        return 0;
    }

    /* Inicializa a matriz com zeros */
    memset(mat->dados, 0, sizeof(mat->dados));
    mat->M = 0;
    mat->N = 0;

    char linha[MAX_DIM * 3 + 8]; /* espaço para "0 " repetido MAX_DIM vezes */
    int maxCols = 0;

    while (fgets(linha, sizeof(linha), f))
    {
        if (mat->M >= MAX_DIM)
        {
            fprintf(stderr, "[AVISO] lerMatriz: matriz excede MAX_DIM=%d linhas. Truncando.\n", MAX_DIM);
            break;
        }

        int col = 0;
        char *tok = strtok(linha, " \t\r\n");
        while (tok && col < MAX_DIM)
        {
            mat->dados[mat->M][col] = atoi(tok);
            col++;
            tok = strtok(NULL, " \t\r\n");
        }
        if (col > maxCols)
            maxCols = col;
        mat->M++;
    }

    mat->N = maxCols;
    fclose(f);

    if (mat->M == 0 || mat->N == 0)
    {
        fprintf(stderr, "[ERRO] lerMatriz: arquivo vazio ou mal formatado.\n");
        return 0;
    }

    printf("[INFO] Matriz lida: %d linhas x %d colunas.\n", mat->M, mat->N);
    return 1;
}

/* ══════════════════════════════════════════════════════════════════════════
 *  salvarMatriz
 *  Grava a matriz no arquivo texto de saída.
 *  Formato: valores separados por espaço, uma linha por row.
 * ══════════════════════════════════════════════════════════════════════════ */
void salvarMatriz(const char *nomeArq, const Matriz *mat)
{
    FILE *f = fopen(nomeArq, "w");
    if (!f)
    {
        fprintf(stderr, "[ERRO] salvarMatriz: não foi possível criar '%s'.\n", nomeArq);
        return;
    }

    for (int i = 0; i < mat->M; i++)
    {
        for (int j = 0; j < mat->N; j++)
        {
            fprintf(f, "%d", mat->dados[i][j]);
            if (j < mat->N - 1)
                fprintf(f, " ");
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("[INFO] Matriz de saída gravada em '%s'.\n", nomeArq);
}

/* ══════════════════════════════════════════════════════════════════════════
 *  imprimirMatriz
 *  Exibe a matriz no terminal de forma legível.
 * ══════════════════════════════════════════════════════════════════════════ */
void imprimirMatriz(const Matriz *mat)
{
    /* Cabeçalho de colunas */
    printf("     ");
    for (int j = 0; j < mat->N; j++)
        printf("%2d", j);
    printf("\n     ");
    for (int j = 0; j < mat->N; j++)
        printf("--");
    printf("\n");

    for (int i = 0; i < mat->M; i++)
    {
        printf("%3d |", i);
        for (int j = 0; j < mat->N; j++)
        {
            printf("%2s", mat->dados[i][j] ? "1" : ".");
        }
        printf("\n");
    }
}

/* ══════════════════════════════════════════════════════════════════════════
 *  rotularComponentes
 *  Percorre toda a matriz e usa a PDE para rotular cada componente conexo.
 *  Retorna o número total de componentes encontrados.
 *
 *  Para cada célula (i,j) com valor 1 ainda não rotulada:
 *    - Atribui um rótulo novo.
 *    - Empilha a coordenada (i,j).
 *    - Enquanto a pilha não estiver vazia:
 *        * Desempilha uma coordenada.
 *        * Para cada vizinho válido com valor 1 e ainda sem rótulo:
 *            - Rotula o vizinho com o rótulo atual.
 *            - Empilha o vizinho.
 *    - Conta quantas células receberam este rótulo.
 *
 *  Isso é equivalente a um BFS iterativo.
 * ══════════════════════════════════════════════════════════════════════════ */
static int rotularComponentes(const Matriz *mat)
{
    int numLabels = 0;

    /* Inicializa a matriz de rótulos com zero (não visitado) */
    memset(rotulos, 0, sizeof(rotulos));
    memset(tamComponente, 0, sizeof(tamComponente));

    /* Cria a pilha que armazenará coordenadas do tipo Coord */
    Pilha *pilha = criarPilha(sizeof(Coord));
    if (!pilha)
    {
        fprintf(stderr, "[ERRO] rotularComponentes: falha ao criar pilha.\n");
        return -1;
    }

    for (int i = 0; i < mat->M; i++)
    {
        for (int j = 0; j < mat->N; j++)
        {

            /* Ignora zeros e células já rotuladas */
            if (mat->dados[i][j] == 0 || rotulos[i][j] != 0)
                continue;

            /* Nova célula "semente": inicia um novo componente */
            numLabels++;
            int label = numLabels; /* rótulo deste componente */
            int tamanho = 0;

            /* Empilha a semente */
            Coord semente = {i, j};
            rotulos[i][j] = label;
            push(pilha, &semente);

            /* Expande o componente iterativamente via pilha */
            while (!pilhaVazia(pilha))
            {
                Coord atual;
                pop(pilha, &atual); /* retira o topo */
                tamanho++;          /* conta a célula retirada */

                /* Visita cada um dos 4 vizinhos */
                for (int v = 0; v < NUM_VIZ; v++)
                {
                    int ni = atual.lin + dLin[v];
                    int nj = atual.col + dCol[v];

                    /* Verifica limites da matriz */
                    if (ni < 0 || ni >= mat->M)
                        continue;
                    if (nj < 0 || nj >= mat->N)
                        continue;

                    /* Apenas propaga para 1s ainda não rotulados */
                    if (mat->dados[ni][nj] == 1 && rotulos[ni][nj] == 0)
                    {
                        rotulos[ni][nj] = label; /* rotula antes de empilhar */
                        Coord viz = {ni, nj};    /* para evitar re-empilhamento */
                        push(pilha, &viz);
                    }
                }
            }

            /* Guarda o tamanho deste componente */
            tamComponente[label] = tamanho;
        }
    }

    destruirPilha(pilha);
    return numLabels;
}

/* ══════════════════════════════════════════════════════════════════════════
 *  calcularCentro
 *  Calcula o centro geométrico (centroide) do maior objeto.
 *  Fórmulas conforme o enunciado:
 *    CLin = round( (Σ i) / tamanho )
 *    CCol = round( (Σ j) / tamanho )
 *  onde i e j percorrem todas as células com rótulo == maiorLabel.
 * ══════════════════════════════════════════════════════════════════════════ */
static void calcularCentro(const Matriz *mat, int maiorLabel,
                           int *cLin, int *cCol)
{
    long long somaI = 0, somaJ = 0;
    int tam = tamComponente[maiorLabel];

    for (int i = 0; i < mat->M; i++)
    {
        for (int j = 0; j < mat->N; j++)
        {
            if (rotulos[i][j] == maiorLabel)
            {
                somaI += i;
                somaJ += j;
            }
        }
    }

    *cLin = (int)round((double)somaI / tam);
    *cCol = (int)round((double)somaJ / tam);
}

/* ══════════════════════════════════════════════════════════════════════════
 *  main
 * ══════════════════════════════════════════════════════════════════════════ */
int main(int argc, char *argv[])
{
    /* ------------------------------------------------------------------ */
    /* 0. Argumentos de linha de comando                                   */
    /* ------------------------------------------------------------------ */
    if (argc < 3)
    {
        fprintf(stderr,
                "Uso: %s <arquivo_entrada> <arquivo_saida>\n"
                "Exemplo: ./app entrada.txt saida.txt\n",
                argv[0]);
        return 1;
    }
    const char *arqEntrada = argv[1];
    const char *arqSaida = argv[2];

    /* ------------------------------------------------------------------ */
    /* 1. Leitura da matriz de entrada                                     */
    /* ------------------------------------------------------------------ */
    Matriz matEntrada;
    if (!lerMatriz(arqEntrada, &matEntrada))
        return 1;

    printf("\n=== MATRIZ DE ENTRADA ===\n");
    imprimirMatriz(&matEntrada);

    /* ------------------------------------------------------------------ */
    /* 2. Rotulação de componentes conexos (BFS iterativa com PDE)        */
    /* ------------------------------------------------------------------ */
    int numObjetos = rotularComponentes(&matEntrada);
    if (numObjetos < 0)
        return 1; /* erro interno */

    /* ------------------------------------------------------------------ */
    /* A) Distribuição dos objetos                                         */
    /* ------------------------------------------------------------------ */
    printf("\n=== A) DISTRIBUIÇÃO DOS OBJETOS ===\n");
    printf("Número total de objetos encontrados: %d\n\n", numObjetos);

    int maiorLabel = 0;
    int maiorTam = 0;

    for (int label = 1; label <= numObjetos; label++)
    {
        printf("  Objeto %2d: tamanho = %d célula(s)\n",
               label, tamComponente[label]);
        if (tamComponente[label] > maiorTam)
        {
            maiorTam = tamComponente[label];
            maiorLabel = label;
        }
    }

    printf("\nMaior objeto: Objeto %d com %d célula(s).\n",
           maiorLabel, maiorTam);

    /* ------------------------------------------------------------------ */
    /* B) Geração da matriz de saída (apenas o maior objeto)              */
    /* ------------------------------------------------------------------ */
    Matriz matSaida;
    matSaida.M = matEntrada.M;
    matSaida.N = matEntrada.N;
    memset(matSaida.dados, 0, sizeof(matSaida.dados));

    for (int i = 0; i < matEntrada.M; i++)
    {
        for (int j = 0; j < matEntrada.N; j++)
        {
            if (rotulos[i][j] == maiorLabel)
            {
                matSaida.dados[i][j] = 1;
            }
        }
    }

    printf("\n=== B) MATRIZ DE SAÍDA (maior objeto) ===\n");
    imprimirMatriz(&matSaida);
    salvarMatriz(arqSaida, &matSaida);

    /* ------------------------------------------------------------------ */
    /* C) Centro geométrico do maior objeto                               */
    /* ------------------------------------------------------------------ */
    int cLin, cCol;
    calcularCentro(&matEntrada, maiorLabel, &cLin, &cCol);

    printf("\n=== C) CENTRO DO MAIOR OBJETO ===\n");
    printf("CLin = %d,  CCol = %d\n", cLin, cCol);

    printf("\n[CONCLUÍDO] Processamento finalizado com sucesso.\n");
    return 0;
}