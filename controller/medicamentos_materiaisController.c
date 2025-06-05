#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
MedicamentoMaterial *cadastrarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual, MedicamentoMaterial *novomedicamentomaterial)
{
    MedicamentoMaterial *novo = realloc(medicamentosmateriais, (*tammedicamentomaterial + 1) * sizeof(MedicamentoMaterial));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return medicamentosmateriais;
    }

    medicamentosmateriais = novo;
    novomedicamentomaterial->codigo = *codigoatual;
    medicamentosmateriais[*tammedicamentomaterial] = *novomedicamentomaterial;

    (*tammedicamentomaterial)++;
    (*codigoatual)++;
    return medicamentosmateriais;
}

long int alterarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo)
{
    if (medicamentosmateriais == NULL)
    {
        return -1; // vazio
    }

    for (int i = 0; i < tammedicamentomaterial; i++)
    {
        if (medicamentosmateriais[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1; // não encontrado
}

void listarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial)
{
    if (medicamentosmateriais == NULL || tammedicamentomaterial == 0)
    {
        printf("Lista de medicamentos e materiais vazia\n");
        return;
    }
    for (int i = 0; i < tammedicamentomaterial; i++)
    {
        printf("Código: %ld\n", medicamentosmateriais[i].codigo);
        printf("Descrição: %s\n", medicamentosmateriais[i].descricao);
        printf("Fabricante: %s\n", medicamentosmateriais[i].fabricante);
        printf("Preço de Custo: %.2f\n", medicamentosmateriais[i].precoCusto);
        printf("Preço de Venda: %.2f\n", medicamentosmateriais[i].precoVenda);
        printf("Quantidade em Estoque: %ld\n", medicamentosmateriais[i].quantidadeEstoque);
        printf("Estoque Mínimo: %ld\n", medicamentosmateriais[i].estoqueMinimo);
        printf("Codigo do fornecedor:%ld\n", medicamentosmateriais[i].codfornecedor);
    }
    return;
}

MedicamentoMaterial *excluimedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int codigo)
{
    int encontrado = -1;
    if (medicamentosmateriais == NULL || *tammedicamentomaterial == 0)
    {
        return medicamentosmateriais;
    }
    for (int i = 0; i < *tammedicamentomaterial; i++)
    {
        if (medicamentosmateriais[i].codigo == codigo)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        return medicamentosmateriais; // no encontrado
    }
    else
    {
        for (int j = encontrado; j < *tammedicamentomaterial - 1; j++)
        {
            medicamentosmateriais[j] = medicamentosmateriais[j + 1];
        }
        (*tammedicamentomaterial)--;

        if (*tammedicamentomaterial == 0)
        {
            free(medicamentosmateriais);
            return NULL;
        }

        MedicamentoMaterial *aux = realloc(medicamentosmateriais, (*tammedicamentomaterial) * sizeof(MedicamentoMaterial));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return medicamentosmateriais;
        }
        else
        {
            medicamentosmateriais = aux;
        }
    }
    return medicamentosmateriais;
}

long int consultamedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo)
{
    if (medicamentosmateriais == NULL || tammedicamentomaterial == 0)
    {
        return -1; // vazio
    }
    for (int i = 0; i < tammedicamentomaterial; i++)
    {
        if (medicamentosmateriais[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}