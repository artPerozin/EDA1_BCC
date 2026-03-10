#include <stdio.h>
#include <string.h>

struct teste {
    int inteiro;
    float real;
    char nome[30];
    char rua[30];
    int *apont;
};

int main(void) {
    struct teste *p = NULL;
    struct teste x = {321, 2.39, "Silva", "Timbo", NULL};
    int y = 101;

    p = &x;
    p->apont = &y;

    printf("==== ENDERECOS ====\n");
    printf("&x:            %p\n", (void*)&x);
    printf("&y:            %p\n", (void*)&y);
    printf("p:             %p\n", (void*)p);
    printf("&(p->real):    %p\n", (void*)&(p->real));
    printf("&(p->apont):   %p\n", (void*)&(p->apont));

    printf("\n==== VALORES ====\n");
    printf("p:             %p\n", (void*)p);
    printf("p->real:       %.2f\n", p->real);
    printf("p->apont:      %p\n", (void*)p->apont);
    printf("*(p->apont):   %d\n", *(p->apont));

    return 0;
}