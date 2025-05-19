#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuambientesmedicos()
{
    AmbienteMedico *ambientes = NULL;
    long int tamambiente = 0, codigoatual = 0, codigo;
    int op;

    do
    {
        op = 0, codigo = 0;
        printf("1:Cadastrar ambiente\n:");
        printf("2:Alterar ambiente\n:");
        printf("3: Excluir ambiente\n");
        printf("4:Listar ambientes\n");
        printf("5:Consultar ambientes médicos\n");
        printf("6:Sair\n");
        scanf("%d", &op);

        if (op <= 0 || op > 6)
        {
            printf("opção invalida! tente novamente");
        }
        else
        {
            if (op == 1)
            {
                ambientes = cadastrarambientemedico(ambientes, &tamambiente, &codigoatual);
            }
            else if (op == 2)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                alterarambientemedico(ambientes, tamambiente, codigo);
            }
            else if (op == 3)
            {
                printf("digite o código:");
                scanf("%ld", &codigo);
                ambientes = excluirambientemedico(ambientes, &tamambiente, codigo);
            }
            else if (op == 4)
            {
                listarambiente(ambientes, tamambiente);
            }
            else if (op == 5)
            {
                printf("digite o código:");
                scanf("%ld", &codigo);
                consultaambiente(ambientes, tamambiente, codigo);
            }
            
        }

    } while (op != 6);
    free(ambientes);
}
AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambiente, long int *codigoatual)
{
    AmbienteMedico *novo = realloc(ambientes, (*tamambiente + 1) * sizeof(AmbienteMedico));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return ambientes;
    }

    ambientes = novo;

    ambientes[*tamambiente].codigo = *codigoatual;

    printf("Digite a descrição do procedimento: ");
    scanf(" %[^\n]", ambientes[*tamambiente].descricaoProcedimento);

    (*tamambiente)++;
    (*codigoatual)++;
    printf("Ambiente médico cadastrado com sucesso\n");
    return ambientes;
}

void alterarambientemedico(AmbienteMedico *ambientes, long int tamambiente, long int codigo)
{
    if (ambientes == NULL)
    {
        printf("Lista de ambientes vazia");
        return;
    }

    for (int i = 0; i < tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {
            printf("Digite a nova descrição do procedimento: ");
            scanf(" %[^\n]", ambientes[i].descricaoProcedimento);
             printf("alteração feita com sucesso\n");
        }
    }
    return;
}

void listarambiente(AmbienteMedico *ambientes, long int tamambiente)
{
    if (ambientes == NULL || tamambiente == 0)
    {
        printf("lista de ambientes vazia\n");
        return;
    }
    for (int i = 0; i < tamambiente; i++)
    {
        printf("Código: %ld\n", ambientes[i].codigo);
        printf("Descrição do procedimento: %s\n", ambientes[i].descricaoProcedimento);
    }
    return;
}

AmbienteMedico *excluirambientemedico(AmbienteMedico *ambientes, long int *tamambiente, int codigo)
{
    int encontrado = -1;
    if (ambientes == NULL || *tamambiente == 0)
    {
        printf("Lista de  ambientes vazia.\n");
        return ambientes;
    }

    for (int i = 0; i < *tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        printf("ambiente medico não encontrado\n");
        return ambientes;
    }
    else
    {
        for (int j = encontrado; j < *tamambiente - 1; j++)
        {
            ambientes[j] = ambientes[j + 1];
        }
        (*tamambiente)--;

        if (*tamambiente == 0)
        {
            printf("excluido com sucesso\n");
            free(ambientes);
            return NULL;
        }
        AmbienteMedico *aux = realloc(ambientes, (*tamambiente) * sizeof(AmbienteMedico));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return ambientes;
        }
        else
        {
            ambientes = aux;
            printf("excluido com sucesso\n");
        }
    }
    return ambientes;
}

void consultaambiente(AmbienteMedico *ambientes, long int tamambiente, long int codigo)
{
    if (ambientes == NULL || tamambiente == 0)
    {
        printf("Lista de ambientes vazia.\n");
        return;
    }
    for (int i = 0; i < tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {
            printf("Código: %ld\n", ambientes[i].codigo);
            printf("Descrição do procedimento: %s\n", ambientes[i].descricaoProcedimento);
            return;
        }
    }

    printf("ambiente não encontrado\n");
}