#include <stdio.h>

int main (){
    int *p = NULL, **pp = NULL, x = 321, y = 101;
    p = &x; // Conteúdo de p = &x = Endereço de Memória da variável x
    pp = &p; // Conteúdo de pp = &p = Endereço de Memória da variável p
    *p = -3; // Conteúdo do enderço de memória de P = -3 
    y = **pp; // **pp aponta para *p que aponta para o valor de x
}