#ifndef LISTA_H
#define LISTA_H

struct nodo{
    int x;
    struct nodo *link;
};

struct descritor{
    unsigned int posicao;
    struct nodo *primeiro;
    struct nodo *ultimo;
    struct descritor *link;
};

int contaNodo(struct nodo *p);
int contaNodoDescritor(struct descritor *p);

#endif