 # Variáveis
CC = gcc
CFLAGS = -Wall -std=c99
OBJ = main.o biblioteca.o ambientes_medicos.o fornecedores.o medicamentos_materiais.o pacientes.o procedimentos.o profisionais.o
EXEC = programa

# Regra para compilar o programa
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regras para compilar os arquivos .c em .o
main.o: main.c biblioteca.h
	$(CC) $(CFLAGS) -c main.c

biblioteca.o: biblioteca.c biblioteca.h
	$(CC) $(CFLAGS) -c biblioteca.c

ambientes_medicos.o: ambientes_medicos.c
	$(CC) $(CFLAGS) -c ambientes_medicos.c

fornecedores.o: fornecedores.c
	$(CC) $(CFLAGS) -c fornecedores.c

medicamentos_materiais.o: medicamentos_materiais.c
	$(CC) $(CFLAGS) -c medicamentos_materiais.c

pacientes.o: pacientes.c
	$(CC) $(CFLAGS) -c pacientes.c

procedimentos.o: procedimentos.c
	$(CC) $(CFLAGS) -c procedimentos.c

profisionais.o: profisionais.c
	$(CC) $(CFLAGS) -c profisionais.c

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)
