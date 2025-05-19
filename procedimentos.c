#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuprocedimentos()
{
    Procedimento *procedimentos = NULL;
    long int tamprocedimento = 0, codigoatual = 0, codigo;
    int op;

    do
    {
        op = 0, codigo = 0;
        printf("1:Cadastrar procedimento\n:");
        printf("2:Alterar procedimento\n:");
        printf("3: Excluir procedimento\n");
        printf("4:Listar procedimentos\n");
        printf("5:Consultar procedimento\n");
        printf("6:Sair\n");
        scanf("%d", &op);

        if (op <= 0 || op > 6)
        {
            printf("opção invalida! tente novamente\n");
        }
        else
        {
            if (op == 1)
            {
                procedimentos = cadastrarprocedimento(procedimentos, &tamprocedimento, &codigoatual);
            }
            else if (op == 2)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                alterarprocedimento(procedimentos, tamprocedimento, codigo);
            }
            else if (op == 3)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                procedimentos = excluirprocedimento(procedimentos, &tamprocedimento, codigo);
            }
            else if (op == 4)
            {
                listarprocedimento(procedimentos, tamprocedimento);
            }
            else if (op == 5)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                consultaprocedimento(procedimentos, tamprocedimento, codigo);
            }
        }

    } while (op != 6);
    for (int i = 0; i < tamprocedimento; i++)
    {
        free(procedimentos[i].codmedicamentosemateriais);
    }
    free(procedimentos);
}
Procedimento *cadastrarprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int *codigoatual)
{
    Procedimento *novoprocedimento = realloc(procedimentos, (*tamprocedimento + 1) * sizeof(Procedimento));

    if (novoprocedimento == NULL)
    {
        printf("erro ao alocar memoria");
        return procedimentos;
    }
    procedimentos = novoprocedimento;
    procedimentos[*tamprocedimento].codigo = *codigoatual;

    printf("Digite a descrição do procedimento: ");
    scanf(" %[^\n]", procedimentos[*tamprocedimento].descricao);

    printf("Digite o custo: ");
    scanf("%f", &procedimentos[*tamprocedimento].custo);

    printf("Digite o tempo estimado em minutos: ");
    scanf("%ld", &procedimentos[*tamprocedimento].tempoEstimado);

    printf("digite o código do ambiente médico:");
    scanf("%ld", &procedimentos[*tamprocedimento].codambientemedico);

    printf("digite quantos materiais e medicamentos seram utilizados:");
    scanf("%ld", &procedimentos[*tamprocedimento].tamcodmedicamentosmateriais);

    procedimentos[*tamprocedimento].codmedicamentosemateriais = malloc(procedimentos[*tamprocedimento].tamcodmedicamentosmateriais * sizeof(long int));
    if (procedimentos[*tamprocedimento].codmedicamentosemateriais == NULL)
    {
        printf("Erro ao alocar memória para os códigos de medicamentos/materiais\n");
        return procedimentos;
    }

    else
    {
        for (int i = 0; i < procedimentos[*tamprocedimento].tamcodmedicamentosmateriais; i++)
        {
            printf("Digite o código do material %d: ", i + 1);
            scanf("%ld", &procedimentos[*tamprocedimento].codmedicamentosemateriais[i]);
        }
    }
    printf("Procedimento cadastrado com sucesso\n");
    (*tamprocedimento)++;
    (*codigoatual)++;
    return procedimentos;
}

void alterarprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo)
{
    if (procedimentos == NULL)
    {
        printf("Lista de procedimentos vazia\n");
        return;
    }

    for (int i = 0; i < tamprocedimento; i++)
    {
        if (procedimentos[i].codigo == codigo)
        {
            printf("Digite a descrição do procedimento: ");
            scanf(" %[^\n]", procedimentos[i].descricao);

            printf("Digite o custo: ");
            scanf("%f", &procedimentos[i].custo);

            printf("Digite o tempo estimado em minutos: ");
            scanf("%ld", &procedimentos[i].tempoEstimado);

            printf("digite o código do ambiente médico:");
            scanf("%ld", &procedimentos[i].codambientemedico);

            printf("digite quantos materiais e medicamentos seram utilizados:");
            scanf("%ld", &procedimentos[i].tamcodmedicamentosmateriais);

            long int *novo = realloc(procedimentos[i].codmedicamentosemateriais, procedimentos[i].tamcodmedicamentosmateriais * sizeof(long int));
            if (novo == NULL)
            {
                printf("erro ao realocar meomoria para o vetor de codigos de materiais e medicamentos\n");
                return;
            }
            else
            {
                procedimentos[i].codmedicamentosemateriais = novo;
                for (int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
                {
                    printf("Digite o código do material %d: ", j + 1);
                    scanf("%ld", &procedimentos[i].codmedicamentosemateriais[j]);
                }
                printf("Procedimento alterado com sucesso!\n");
                return;
            }
        }
    }
    printf("Código não encontrado.\n");
    return;
}

void listarprocedimento(Procedimento *procedimentos, long int tamprocedimento)
{
    if (procedimentos == NULL || tamprocedimento == 0)
    {
        printf("Lista de procedimentos vazia\n");
        return;
    }
    for (int i = 0; i < tamprocedimento; i++)
    {
        printf("Código do procedimento: %ld\n", procedimentos[i].codigo);
        printf("Descrição: %s\n", procedimentos[i].descricao);
        printf("Custo: R$ %.2f\n", procedimentos[i].custo);
        printf("Tempo estimado: %ld minutos\n", procedimentos[i].tempoEstimado);
        printf("Código do ambiente médico: %ld\n", procedimentos[i].codambientemedico);
        printf("Quantidade de materiais/medicamentos: %ld\n", procedimentos[i].tamcodmedicamentosmateriais);
        if (procedimentos[i].codmedicamentosemateriais != NULL)
        {
            for (int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
            {
                printf("Codigo do material:%ld\n", procedimentos[i].codmedicamentosemateriais[j]);
            }
        }
    }
    return;
}

Procedimento *excluirprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int codigo)
{
    int encontrado = -1;
    if (procedimentos == NULL || *tamprocedimento == 0)
    {
        printf("Lista de procedimentos vazia.\n");
        return procedimentos;
    }
    for (int i = 0; i < *tamprocedimento; i++)
    {
        if (procedimentos[i].codigo == codigo)
        {
            encontrado = i;
            free(procedimentos[i].codmedicamentosemateriais);
            procedimentos[i].codmedicamentosemateriais = NULL;
            procedimentos[i].tamcodmedicamentosmateriais = 0;
            break;
        }
    }
    if (encontrado == -1)
    {
        printf("procedimento não encontrado\n");
        return procedimentos;
    }
    else
    {
        for (int j = encontrado; j < *tamprocedimento - 1; j++)
        {
            procedimentos[j] = procedimentos[j + 1];
        }
        (*tamprocedimento)--;

        if (*tamprocedimento == 0)
        {
            printf("excluido com sucesso\n");
            free(procedimentos);
            return NULL;
        }
        Procedimento *aux = realloc(procedimentos, (*tamprocedimento) * sizeof(Procedimento));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return procedimentos;
        }
        else
        {
            procedimentos = aux;
            printf("excluido com sucesso\n");
        }
    }
    return procedimentos;
}

void consultaprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo)
{
    if (procedimentos == NULL || tamprocedimento == 0)
    {
        printf("lista de procedimentos vazia\n");
        return;
    }
    for (int i = 0; i < tamprocedimento; i++)
    {
        if (procedimentos[i].codigo == codigo)
        {
            printf("Código do procedimento: %ld\n", procedimentos[i].codigo);
            printf("Descrição: %s\n", procedimentos[i].descricao);
            printf("Custo: R$ %.2f\n", procedimentos[i].custo);
            printf("Tempo estimado: %ld minutos\n", procedimentos[i].tempoEstimado);
            printf("Código do ambiente médico: %ld\n", procedimentos[i].codambientemedico);
            printf("Quantidade de materiais/medicamentos: %ld\n", procedimentos[i].tamcodmedicamentosmateriais);

            if (procedimentos[i].codmedicamentosemateriais != NULL)
            {
                for (int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
                {
                    printf("Codigo do material:%ld\n", procedimentos[i].codmedicamentosemateriais[j]);
                }
                return;
            }
        }
    }

    printf("procedimento não encontrado\n");
    return;
}
