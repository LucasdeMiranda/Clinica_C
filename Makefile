 # Compilador e flags
CC = gcc
CFLAGS = -Wall -std=c99 -Iview -Icontroller

# Arquivos objeto (sem biblioteca.o)
OBJ = main.o ambientes_medicosView.o ambientes_medicosController.o fornecedores.o medicamentos_materiais.o pacientes.o procedimentos.o profissionais.o

# Executável
EXEC = CLINICA

# Regra para compilar o programa
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

# Regras para compilar os arquivos .c em .o
main.o: main.c view/biblioteca.h
	$(CC) $(CFLAGS) -c main.c

ambientes_medicosView.o: view/ambientes_medicosView.c view/biblioteca.h
	$(CC) $(CFLAGS) -c view/ambientes_medicosView.c -o ambientes_medicosView.o

ambientes_medicosController.o: controller/ambientes_medicosController.c controller/ambientes_medicosController.h
	$(CC) $(CFLAGS) -c controller/ambientes_medicosController.c -o ambientes_medicosController.o

fornecedores.o: fornecedores.c
	$(CC) $(CFLAGS) -c fornecedores.c

medicamentos_materiais.o: medicamentos_materiais.c
	$(CC) $(CFLAGS) -c medicamentos_materiais.c

pacientes.o: pacientes.c view/biblioteca.h
	$(CC) $(CFLAGS) -c pacientes.c

procedimentos.o: procedimentos.c
	$(CC) $(CFLAGS) -c procedimentos.c

profissionais.o: profissionais.c
	$(CC) $(CFLAGS) -c profissionais.c

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC) chat
