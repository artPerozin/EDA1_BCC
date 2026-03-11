#ifndef LISTA_H
#define LISTA_H

typedef struct nodo{
    int x;
    struct nodo *link;
} Nodo;

typedef struct descritor{
    int TAMvet;
    Nodo **vet;
} Descritor;

int contaNodo(Descritor *p);

#endif