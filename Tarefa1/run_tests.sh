#!/bin/bash
# ============================================================
# run_tests.sh
# Script de testes automatizados para o projeto PDE/CCL
# ============================================================
# Uso: bash run_tests.sh
# ============================================================

PASS=0
FAIL=0
APP="./app"

RED='\033[0;31m'
GRN='\033[0;32m'
YEL='\033[1;33m'
NC='\033[0m'

separator() { printf "${YEL}%s${NC}\n" "────────────────────────────────────────────"; }

ok()   { printf "${GRN}[PASS]${NC} %s\n" "$1"; PASS=$((PASS+1)); }
fail() { printf "${RED}[FAIL]${NC} %s\n" "$1"; FAIL=$((FAIL+1)); }

separator
echo "  TESTES AUTOMATIZADOS - Pilha PDE + CCL"
separator

# ── Teste 0: compilação ──────────────────────────────────────
echo ""
echo "TESTE 0: Compilação"
gcc -Wall -Wextra -o app aplicacao.c pilha.c -lm 2>err_compile.txt
if [ $? -eq 0 ]; then
    ok "Compilação sem erros"
else
    fail "Erro de compilação:"
    cat err_compile.txt
    echo "Abortando testes."
    exit 1
fi

# ── Teste 1: arquivo de entrada do enunciado ─────────────────
echo ""
echo "TESTE 1: Matriz do enunciado (14x14)"
$APP entrada.txt saida1.txt > out1.txt 2>&1
if [ $? -eq 0 ]; then
    ok "Execução sem erros"
else
    fail "Execução retornou erro"
fi

# Verifica se o arquivo de saída foi gerado
if [ -f saida1.txt ]; then
    ok "Arquivo saida1.txt gerado"
else
    fail "Arquivo saida1.txt não foi gerado"
fi

# Verifica que a saída menciona pelo menos 2 objetos
if grep -q "Número total de objetos encontrados: 2" out1.txt; then
    ok "Detectou 2 objetos na Tabela 1"
else
    fail "Número de objetos incorreto (esperado: 2)"
    grep "objetos" out1.txt
fi

echo ""
echo "  --- Saída do programa (Teste 1) ---"
cat out1.txt
echo ""

# ── Teste 2: 3 objetos de tamanhos diferentes ────────────────
echo ""
echo "TESTE 2: Três objetos isolados (5x5)"
$APP teste2.txt saida2.txt > out2.txt 2>&1
if [ $? -eq 0 ]; then
    ok "Execução sem erros"
else
    fail "Execução retornou erro"
fi

if grep -q "Número total de objetos encontrados: 3" out2.txt; then
    ok "Detectou 3 objetos"
else
    fail "Número de objetos incorreto (esperado: 3)"
fi

# O maior objeto deve ter tamanho 3 (coluna esquerda: (1,1),(2,1),(3,1))
if grep -q "tamanho = 3" out2.txt; then
    ok "Maior objeto tem tamanho 3"
else
    fail "Tamanho do maior objeto incorreto (esperado: 3)"
fi

echo ""
echo "  --- Saída do programa (Teste 2) ---"
cat out2.txt
echo ""

# ── Teste 3: pixel único ─────────────────────────────────────
echo ""
echo "TESTE 3: Pixel único (3x3)"
$APP teste3.txt saida3.txt > out3.txt 2>&1
if [ $? -eq 0 ]; then
    ok "Execução sem erros"
else
    fail "Execução retornou erro"
fi

if grep -q "Número total de objetos encontrados: 1" out3.txt; then
    ok "Detectou 1 objeto"
else
    fail "Número de objetos incorreto (esperado: 1)"
fi

if grep -q "CLin = 1,  CCol = 1" out3.txt; then
    ok "Centro calculado corretamente (1,1)"
else
    fail "Centro incorreto (esperado CLin=1, CCol=1)"
fi

echo ""
echo "  --- Saída do programa (Teste 3) ---"
cat out3.txt
echo ""

# ── Teste 4: 4 objetos de tamanhos variados ──────────────────
echo ""
echo "TESTE 4: 4 objetos — quadrado 2x2, retângulo 3x3, dois pixels isolados"
$APP teste4.txt saida4.txt > out4.txt 2>&1
if [ $? -eq 0 ]; then
    ok "Execução sem erros"
else
    fail "Execução retornou erro"
fi

if grep -q "Número total de objetos encontrados: 4" out4.txt; then
    ok "Detectou 4 objetos"
else
    fail "Número de objetos incorreto (esperado: 4)"
fi

# Maior objeto é o 3x3 = 9 células
if grep -q "tamanho = 9" out4.txt; then
    ok "Maior objeto tem tamanho 9 (retângulo 3x3)"
else
    fail "Tamanho do maior objeto incorreto (esperado: 9)"
fi

echo ""
echo "  --- Saída do programa (Teste 4) ---"
cat out4.txt
echo ""

# ── Teste 5: arquivo inexistente ─────────────────────────────
echo ""
echo "TESTE 5: Arquivo de entrada inexistente (deve reportar erro)"
$APP nao_existe.txt saida_x.txt > out5.txt 2>&1
if [ $? -ne 0 ]; then
    ok "Programa retornou erro corretamente"
else
    fail "Programa deveria ter retornado erro"
fi

# ── Resumo ───────────────────────────────────────────────────
separator
printf "Resultado final: ${GRN}%d PASS${NC}  ${RED}%d FAIL${NC}\n" $PASS $FAIL
separator

if [ $FAIL -eq 0 ]; then
    echo ""
    printf "${GRN}Todos os testes passaram!${NC}\n"
    exit 0
else
    echo ""
    printf "${RED}Alguns testes falharam. Verifique a saída acima.${NC}\n"
    exit 1
fi