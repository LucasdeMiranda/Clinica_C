#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuambientesmedicos()
{
    AmbienteMedico *ambientes = NULL;
    long int tamambiente = 0;
    int op, cpf;

    do
    {
        op = 0, cpf = 0;
        printf("1:Cadastrar ambiente\n:");
        printf("2:Alterar ambiente\n:");
        printf("3: Excluir ambiente");
        printf("4:Listar ambientes");
        printf("5:Sair");
        scanf("%d", &op);

        if (op <= 0 && op > 5)
        {
            printf("opção invalida! tente novamente");
        }
        else
        {
            if (op == 1)
            {
                ambientes = cadastrarambientemedico(ambientes, &tamambiente);
            }
            else if (op == 2)
            {
            }
            else if (op == 3)
            {
            }
            else if (op == 4)
            {
            }
        }

    } while (op != 5);
}
AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambientes)
{
    AmbienteMedico *novo = realloc(ambientes, (*tamambientes + 1) * sizeof(AmbienteMedico));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return ambientes;
    }

    ambientes = novo;

    printf("Digite o código: ");
    scanf("%d", &ambientes[*tamambientes].codigo);

    printf("Digite a descrição do procedimento: ");
    scanf(" %[^\n]", ambientes[*tamambientes].descricaoProcedimento);

    (*tamambientes)++;
    return ambientes;
}
