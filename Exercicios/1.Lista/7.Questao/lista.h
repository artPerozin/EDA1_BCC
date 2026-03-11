#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>

typedef struct nodo{
    int dt;
    struct nodo *link;
} Nodo;

typedef struct descritor{
    int tamanho;
    Nodo *inicio;
} Descritor;

int reinicia(Descritor *p);
int insere(Descritor *p, Nodo *novo, int pos);

#endif