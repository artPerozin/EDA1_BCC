# Ponteiros em C — Estudo de Memória

## Código Analisado

```c
int *p = NULL, **pp = NULL, x = 321, y = 101;
p  = &x;   // p aponta para x
pp = &p;   // pp aponta para p
*p = -3;   // altera o valor de x via ponteiro (x agora vale -3)
y  = **pp; // y recebe o valor apontado por pp (y = x = -3)
```

---

## Estado Final da Memória

| Campo           | Endereço             | Conteúdo             | Tipo       |
|-----------------|----------------------|----------------------|------------|
| `x`             | `00007FFC127C92C0`   | `-3` *(era 321)*     | `int`      |
| `y`             | `00007FFC127C92C4`   | `-3` *(era 101)*     | `int`      |
| `p`             | `00007FFC127C92C8`   | `00007FFC127C92C0`   | `int *`    |
| `pp`            | `00007FFC127C92D0`   | `00007FFC127C92C8`   | `int **`   |

> ⚠️ O conteúdo de `p` é o **endereço de `x`**, não o valor `-3`. O valor `-3` está em `x`.

---

## Cadeia de Indireção

```
pp  →  p  →  x
│      │      │
│      │      └─ valor: -3
│      └─ endereço de x: 00007FFC127C92C0
└─ endereço de p: 00007FFC127C92C8
```

| Expressão       | Equivale a | Valor / Endereço     |
|-----------------|------------|----------------------|
| `pp`            | —          | `00007FFC127C92C8` (endereço de `p`) |
| `*pp`           | `p`        | `00007FFC127C92C0` (endereço de `x`) |
| `**pp`          | `*p` == `x`| `-3`                 |

---

## Passo a Passo das Atribuições

### 1. Declarações iniciais
```c
int *p = NULL, **pp = NULL, x = 321, y = 101;
```
| Variável | Valor inicial |
|----------|---------------|
| `x`      | `321`         |
| `y`      | `101`         |
| `p`      | `NULL`        |
| `pp`     | `NULL`        |

### 2. `p = &x`
`p` passa a armazenar o **endereço de `x`**.  
Agora `*p` acessa diretamente o valor de `x`.

### 3. `pp = &p`
`pp` passa a armazenar o **endereço de `p`**.  
Agora `*pp` equivale a `p`, e `**pp` equivale a `*p` (ou seja, `x`).

### 4. `*p = -3`
Atribui `-3` à variável apontada por `p` — que é `x`.  
`x` agora vale `-3`. O endereço de `x` não muda.

### 5. `y = **pp`
Desreferencia `pp` duas vezes:
- `*pp` → `p` → endereço de `x`
- `**pp` → `*p` → valor de `x` → `-3`

`y` recebe `-3`.

---

## Conceitos-Chave

| Conceito | Descrição |
|----------|-----------|
| `&var` | Operador de endereço — retorna o endereço de memória de `var` |
| `*p` | Operador de desreferência — acessa o valor no endereço armazenado em `p` |
| `int *p` | Ponteiro para `int` — armazena endereço de um `int` |
| `int **pp` | Ponteiro para ponteiro para `int` — armazena endereço de um `int *` |
| `NULL` | Valor nulo para ponteiros — indica que não aponta para nada |

---

*Material de estudo — Ponteiros e memória em C*