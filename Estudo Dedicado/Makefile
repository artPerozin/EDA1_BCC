# Makefile — compila todos os programas de teste
# Uso:
#   make          → compila tudo
#   make run      → compila e executa todos
#   make clean    → remove os executáveis

CC     = gcc
FLAGS  = -Wall -Wextra -g

all: teste_PE teste_PSE teste_PDE teste_filas teste_MPE teste_aplicacoes

teste_PE: teste_PE.c PE.h
	$(CC) $(FLAGS) teste_PE.c -o teste_PE

teste_PSE: teste_PSE.c PSE.h
	$(CC) $(FLAGS) teste_PSE.c -o teste_PSE

teste_PDE: teste_PDE.c PDE.h
	$(CC) $(FLAGS) teste_PDE.c -o teste_PDE

teste_filas: teste_filas.c FES.h FEM.h FEC.h
	$(CC) $(FLAGS) teste_filas.c -o teste_filas

teste_MPE: teste_MPE.c MPE.h
	$(CC) $(FLAGS) teste_MPE.c -o teste_MPE

teste_aplicacoes: teste_aplicacoes.c PE.h
	$(CC) $(FLAGS) teste_aplicacoes.c -o teste_aplicacoes

run: all
	@echo "\n========== teste_PE ==========" && ./teste_PE
	@echo "\n========== teste_PSE ==========" && ./teste_PSE
	@echo "\n========== teste_PDE ==========" && ./teste_PDE
	@echo "\n========== teste_filas ==========" && ./teste_filas
	@echo "\n========== teste_MPE ==========" && ./teste_MPE
	@echo "\n========== teste_aplicacoes ==========" && ./teste_aplicacoes

clean:
	rm -f teste_PE teste_PSE teste_PDE teste_filas teste_MPE teste_aplicacoes
