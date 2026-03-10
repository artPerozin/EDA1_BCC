# Diretivas de Pré-processamento em C

> As diretivas de compilação (ou diretivas de pré-processamento) são instruções processadas **antes** da compilação propriamente dita. Elas começam sempre com o símbolo `#` e não terminam com `;`.

---

## `#include` — Inclusão de Arquivos

Insere o conteúdo de outro arquivo no ponto onde a diretiva aparece.

### Sintaxe

```c
#include <arquivo.h>   // Busca nos diretórios padrão do sistema
#include "arquivo.h"   // Busca primeiro no diretório do projeto
```

### Exemplo

```c
#include <stdio.h>      // Biblioteca padrão de I/O
#include <stdlib.h>     // Funções utilitárias (malloc, exit, etc.)
#include "meu_modulo.h" // Cabeçalho do próprio projeto
```

> **Dica:** Use `< >` para bibliotecas do sistema e `" "` para arquivos do seu projeto.

---

## `#define` — Definição de Macros e Constantes

Define uma macro: substitui textualmente um identificador por um valor ou expressão em todo o código.

### Sintaxe

```c
#define NOME valor
#define NOME(params) expressão
```

### Exemplos

```c
// Constante simbólica
#define PI 3.14159
#define MAX_BUFFER 1024

// Macro com parâmetro
#define QUADRADO(x) ((x) * (x))
#define MAX(a, b)   ((a) > (b) ? (a) : (b))

int main() {
    double area = PI * QUADRADO(5.0); // Expandido em tempo de compilação
    int maior = MAX(10, 20);
    return 0;
}
```

> ⚠️ **Atenção:** Sempre use parênteses ao redor dos parâmetros de macros para evitar erros de precedência. `QUADRADO(2+3)` sem parênteses viraria `2+3 * 2+3 = 11`, não `25`.

---

## `#undef` — Remoção de uma Macro

Cancela a definição de uma macro previamente criada com `#define`.

### Sintaxe

```c
#undef NOME
```

### Exemplo

```c
#define TAMANHO 100

// ... usa TAMANHO = 100 aqui ...

#undef TAMANHO
#define TAMANHO 200

// ... agora TAMANHO = 200 ...
```

> **Uso comum:** Redefinir uma macro com valor diferente em partes distintas do código, ou garantir que uma macro não exista antes de redefini-la.

---

## `#ifdef` — Compilação Condicional: "Se Definido"

Compila o bloco de código **somente se** a macro especificada estiver definida.

### Sintaxe

```c
#ifdef NOME
    // código compilado se NOME estiver definido
#endif
```

### Exemplo

```c
#define DEBUG

#ifdef DEBUG
    printf("Valor de x: %d\n", x); // Só compila se DEBUG estiver definido
#endif
```

> **Uso comum:** Ativar logs e mensagens de depuração apenas em builds de desenvolvimento.

---

## `#ifndef` — Compilação Condicional: "Se NÃO Definido"

Compila o bloco de código **somente se** a macro **não** estiver definida.

### Sintaxe

```c
#ifndef NOME
    // código compilado se NOME NÃO estiver definido
#endif
```

### Exemplo clássico — Guard de Cabeçalho (Header Guard)

```c
// arquivo: meu_modulo.h
#ifndef MEU_MODULO_H
#define MEU_MODULO_H

// conteúdo do cabeçalho...
void minhaFuncao(int x);

#endif // MEU_MODULO_H
```

> **Por quê?** Evita que o mesmo cabeçalho seja incluído mais de uma vez no mesmo arquivo, prevenindo erros de redefinição.

---

## `#if` — Compilação Condicional com Expressão

Avalia uma **expressão constante** e compila o bloco se o resultado for verdadeiro (diferente de zero).

### Sintaxe

```c
#if expressão_constante
    // código
#endif
```

### Exemplo

```c
#define VERSAO 2

#if VERSAO >= 2
    printf("Funcionalidade disponível na versão 2+\n");
#endif

#if defined(WINDOWS) && !defined(DEBUG)
    // código específico para Windows em modo release
#endif
```

> **Operadores disponíveis:** `==`, `!=`, `<`, `>`, `<=`, `>=`, `&&`, `||`, `!`, `defined()`

---

## `#else` — Alternativa na Compilação Condicional

Define um bloco alternativo quando a condição do `#if`, `#ifdef` ou `#ifndef` for falsa.

### Sintaxe

```c
#ifdef NOME
    // compilado se NOME estiver definido
#else
    // compilado se NOME NÃO estiver definido
#endif
```

### Exemplo

```c
#ifdef PLATAFORMA_LINUX
    #define LIMPAR_TELA "clear"
#else
    #define LIMPAR_TELA "cls"
#endif
```

---

## `#elif` — "Else If" na Compilação Condicional

Encadeia múltiplas condições, funcionando como `else if`.

### Sintaxe

```c
#if condição1
    // ...
#elif condição2
    // ...
#elif condição3
    // ...
#else
    // ...
#endif
```

### Exemplo

```c
#define SISTEMA 2  // 1 = Linux, 2 = Windows, 3 = macOS

#if SISTEMA == 1
    printf("Linux\n");
#elif SISTEMA == 2
    printf("Windows\n");
#elif SISTEMA == 3
    printf("macOS\n");
#else
    printf("Sistema desconhecido\n");
#endif
```

---

## `#endif` — Encerramento de Bloco Condicional

Obrigatório para fechar qualquer bloco aberto por `#if`, `#ifdef` ou `#ifndef`.

### Sintaxe

```c
#if / #ifdef / #ifndef
    // ...
#endif
```

> Todo `#if`, `#ifdef` ou `#ifndef` **deve** ter um `#endif` correspondente. Esquecer o `#endif` causa erro de compilação.

---

## Resumo Geral

| Diretiva   | Função                                              |
|------------|-----------------------------------------------------|
| `#include` | Inclui o conteúdo de outro arquivo                  |
| `#define`  | Define uma amacro ou constante simbólica             |
| `#undef`   | Remove a definição de uma macro                     |
| `#ifdef`   | Compila se a macro **estiver** definida             |
| `#ifndef`  | Compila se a macro **não estiver** definida         |
| `#if`      | Compila se a expressão constante for verdadeira     |
| `#else`    | Bloco alternativo ao `#if` / `#ifdef` / `#ifndef`  |
| `#elif`    | Condição alternativa encadeada (else if)            |
| `#endif`   | Encerra um bloco condicional                        |

---

## Exemplo Completo: Tudo Junto

```c
#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>

#define VERSAO 3
#define DEBUG

// Configuração baseada na versão
#if VERSAO == 1
    #define MAX_USUARIOS 10
#elif VERSAO == 2
    #define MAX_USUARIOS 100
#else
    #define MAX_USUARIOS 1000
#endif

// Log de debug (removido em produção)
#ifdef DEBUG
    #define LOG(msg) printf("[DEBUG] %s\n", msg)
#else
    #define LOG(msg)  // Macro vazia — não gera código
#endif

#undef DEBUG  // A partir daqui, DEBUG não existe mais

#endif // CONFIG_H
```

---

*Material de estudo — Diretivas de Pré-processamento em C*