#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int contaNodo(struct nodo *p){

    struct nodo *slow = p;
    struct nodo *fast = p;

    while(fast && fast->link){
        slow = slow->link;
        fast = fast->link->link;

        if(slow == fast)
            break;
    }

    if(fast == NULL || fast->link == NULL){

        int count = 0;

        while(p){
            count++;
            p = p->link;
        }

        return count;
    }

    slow = p;

    while(slow != fast){
        slow = slow->link;
        fast = fast->link;
    }

    struct nodo *inicio = slow;

    int count = 0;
    struct nodo *temp = p;

    while(temp != inicio){
        count++;
        temp = temp->link;
    }

    int ciclo = 1;
    temp = inicio->link;

    while(temp != inicio){
        ciclo++;
        temp = temp->link;
    }

    return count + ciclo;
}

int main(){

    struct nodo *n1 = malloc(sizeof(struct nodo));
    struct nodo *n2 = malloc(sizeof(struct nodo));
    struct nodo *n3 = malloc(sizeof(struct nodo));
    struct nodo *n4 = malloc(sizeof(struct nodo));

    n1->link = n2;
    n2->link = n3;
    n3->link = n4;
    n4->link = n2;

    printf("C: %d\n", contaNodo(n1));

    return 0;
}