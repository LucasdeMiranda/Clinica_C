#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view/biblioteca.h"

AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambiente, long int *codigoatual, AmbienteMedico *novoambiente)
{
    AmbienteMedico *novo = realloc(ambientes, (*tamambiente + 1) * sizeof(AmbienteMedico));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return ambientes;
    }

    ambientes = novo;
    novoambiente->codigo = *codigoatual;

    // Copia os dados preenchidos no main para a nova posição do vetor
    ambientes[*tamambiente] = *novoambiente;

    (*tamambiente)++;
    (*codigoatual)++;

    return ambientes;
}

long int alterarambientemedico(AmbienteMedico *ambientes, long int tamambiente, long int codigo)
{
    if (ambientes == NULL || tamambiente == 0)
    {
        return -1; // lista vazia
    }
    for (int i = 0; i < tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {
            return i; // retorna a posição
        }
    }
    return -1;
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
        }
    }
    return ambientes;
}

long int consultaambiente(AmbienteMedico *ambientes, long int tamambiente, long int codigo)
{
    if (ambientes == NULL || tamambiente == 0)
    {

        return -1;
    }
    for (int i = 0; i < tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {

            return i;
        }
    }
     
    return -1;
}