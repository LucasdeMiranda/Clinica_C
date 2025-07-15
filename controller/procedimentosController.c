#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

 Procedimento *cadastrarprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int *codigoatual,
                                    Procedimento *novoprocedimento, AmbienteMedico *ambientes, MedicamentoMaterial *medicamentosmateriais,
                                    long int tamambientes, long int tammedicamentomaterial)
{
    int encontraambiente = -1;
    for (int i = 0; i < tamambientes; i++)
    {
        if (novoprocedimento->codambientemedico == ambientes[i].codigo)
        {
             encontraambiente = 0;
            break;
        }
    }
    if (encontraambiente == -1)
    {
        return procedimentos;
    }

    // Verifica se todos os materiais/medicamentos existem
    for (int i = 0; i < novoprocedimento->tamcodmedicamentosmateriais; i++)
    {
        long int codbuscado = novoprocedimento->codmedicamentosemateriais[i].codigo;
        int encontrado = -1;
        for (int j = 0; j < tammedicamentomaterial; j++)
        {
            if (medicamentosmateriais[j].codigo == codbuscado)
            {
                encontrado = 0;
                break;
            }
        }
        if (encontrado == -1)
        {
            return procedimentos;
        }
    }

    Procedimento *novo = realloc(procedimentos, (*tamprocedimento + 1) * sizeof(Procedimento));
    if (novo == NULL)
    {
        //erro ao alocar memoria
        return procedimentos;
    }

    procedimentos = novo;
    novoprocedimento->codigo = *codigoatual;
    procedimentos[*tamprocedimento] = *novoprocedimento;

    // Aloca novo vetor de structs Codmedicamentosmateriais
    procedimentos[*tamprocedimento].codmedicamentosemateriais = malloc(novoprocedimento->tamcodmedicamentosmateriais * sizeof(Codmedicamentosmateriais));
    
    if (procedimentos[*tamprocedimento].codmedicamentosemateriais == NULL)
    {
        //Erro ao alocar memória para os medicamentos/materiais
        return procedimentos;
    }
    for (int i = 0; i < novoprocedimento->tamcodmedicamentosmateriais; i++)
    {
        procedimentos[*tamprocedimento].codmedicamentosemateriais[i] = novoprocedimento->codmedicamentosemateriais[i];
    }

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
            printf("Digite a descrição do procedimento:");
            scanf(" %1999[^\n]", procedimentos[i].descricao);

            printf("Digite o custo: ");
            scanf("%f", &procedimentos[i].custo);

            printf("Digite o tempo estimado em minutos: ");
            scanf("%ld", &procedimentos[i].tempoEstimado);

            printf("digite o código do ambiente médico:");
            scanf("%ld", &procedimentos[i].codambientemedico);

            printf("digite quantos materiais e medicamentos seram utilizados:");
            scanf("%ld", &procedimentos[i].tamcodmedicamentosmateriais);

            Codmedicamentosmateriais *novo = realloc(procedimentos[i].codmedicamentosemateriais, procedimentos[i].tamcodmedicamentosmateriais * sizeof(Codmedicamentosmateriais));
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
                    scanf("%ld", &procedimentos[i].codmedicamentosemateriais[j].codigo);
                    printf("Digite a quantidade do material %d: ", j + 1);
                    scanf("%ld", &procedimentos[i].codmedicamentosemateriais[j].qnt);
                    
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
                printf("Código do material: %ld - Quantidade usada: %ld\n",
                    procedimentos[i].codmedicamentosemateriais[j].codigo,
                    procedimentos[i].codmedicamentosemateriais[j].qnt);
            }
        }

        printf("\n");
    }

    return;
}


Procedimento *excluirprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int codigo)
{
    int encontrado = -1;
    if (procedimentos == NULL || *tamprocedimento == 0)
    {
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
        }
    }
    return procedimentos;
}

long int consultaprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo)
{
    if (procedimentos == NULL || tamprocedimento == 0)
    {
        return -1; // vazio
    }
    for (int i = 0; i < tamprocedimento; i++)
    {
        if (procedimentos[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}
