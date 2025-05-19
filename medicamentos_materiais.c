#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menumedicamentos_materiais()
{
    MedicamentoMaterial *medicamentosmateriais = NULL;
    long int tammedicamentomaterial = 0, codigoatual = 0, codigo;
    int op;

    do
    {
        op = 0, codigo = 0;
        printf("1:Cadastrar medicamento ou materiais\n:");
        printf("2:Alterar  medicamentos ou materiais\n:");
        printf("3: Excluir medicamento ou material\n");
        printf("4:Listar medicamentos e materiais\n");
        printf("5:Consultar medicamento ou material\n");
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
                medicamentosmateriais = cadastrarmedicamentomaterial(medicamentosmateriais, &tammedicamentomaterial, &codigoatual);
            }
            else if (op == 2)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                alterarmedicamentomaterial(medicamentosmateriais, tammedicamentomaterial, codigo);
            }
            else if (op == 3)
            {
                printf("digite o código:");
                scanf("%ld", &codigo);
                medicamentosmateriais = excluimedicamentomaterial(medicamentosmateriais, &tammedicamentomaterial, codigo);
            }
            else if (op == 4)
            {
                listarmedicamentomaterial(medicamentosmateriais, tammedicamentomaterial);
            }
            else if (op == 5)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                consultamedicamentomaterial(medicamentosmateriais, tammedicamentomaterial, codigo);
            }
        }

    } while (op != 6);
     free(medicamentosmateriais);
}
MedicamentoMaterial *cadastrarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual)
{
    MedicamentoMaterial *novo = realloc(medicamentosmateriais, (*tammedicamentomaterial + 1) * sizeof(MedicamentoMaterial));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return medicamentosmateriais;
    }

    medicamentosmateriais = novo;

    medicamentosmateriais[*tammedicamentomaterial].codigo = *codigoatual;

    printf("Digite a descrição: ");
    scanf(" %[^\n]", medicamentosmateriais[*tammedicamentomaterial].descricao);

    printf("Digite o fabricante: ");
    scanf(" %[^\n]", medicamentosmateriais[*tammedicamentomaterial].fabricante);

    printf("Digite o preço de custo: ");
    scanf("%f", &medicamentosmateriais[*tammedicamentomaterial].precoCusto);

    printf("Digite o preço de venda: ");
    scanf("%f", &medicamentosmateriais[*tammedicamentomaterial].precoVenda);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &medicamentosmateriais[*tammedicamentomaterial].quantidadeEstoque);

    printf("Digite o estoque mínimo: ");
    scanf("%d", &medicamentosmateriais[*tammedicamentomaterial].estoqueMinimo);
    printf("Digite o código do fornecedor:");
    scanf("%ld", &medicamentosmateriais[*tammedicamentomaterial].codfornecedor);
    printf("Medicamento ou material cadastrado com sucesso\n");

    (*tammedicamentomaterial)++;
    (*codigoatual)++;
    return medicamentosmateriais;
}

void alterarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo)
{
    if (medicamentosmateriais == NULL)
    {
        printf("Lista de medicamentos/materiais vazia\n");
        return;
    }

    for (int i = 0; i < tammedicamentomaterial; i++)
    {
        if (medicamentosmateriais[i].codigo == codigo)
        {
            printf("Digite a descrição: ");
            scanf(" %[^\n]", medicamentosmateriais[i].descricao);

            printf("Digite o fabricante: ");
            scanf(" %[^\n]", medicamentosmateriais[i].fabricante);

            printf("Digite o preço de custo: ");
            scanf("%f", &medicamentosmateriais[i].precoCusto);

            printf("Digite o preço de venda: ");
            scanf("%f", &medicamentosmateriais[i].precoVenda);

            printf("Digite a quantidade em estoque: ");
            scanf("%ld", &medicamentosmateriais[i].quantidadeEstoque);

            printf("Digite o estoque mínimo: ");
            scanf("%ld", &medicamentosmateriais[i].estoqueMinimo);
            printf("Digite o código do fornecedor:");
            scanf("%ld", &medicamentosmateriais[i].codfornecedor);
            printf("Medicamento ou material alterado com sucesso\n");
        }
    }
    return;
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
        printf("Lista de  medicamentos e materiais vazia.\n");
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
        printf("  medicamento ou material não encontrado\n");
        return medicamentosmateriais;
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
            printf("excluido com sucesso\n");
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
            printf("excluido com sucesso\n");
        }
    }
    return medicamentosmateriais;
}

void consultamedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo)
{
    if (medicamentosmateriais == NULL || tammedicamentomaterial == 0)
    {
        printf("Lista de medicamentos e materiais vazia.\n");
        return;
    }
    for (int i = 0; i < tammedicamentomaterial; i++)
    {
        if (medicamentosmateriais[i].codigo == codigo)
        {
            printf("Código: %ld\n", medicamentosmateriais[i].codigo);
            printf("Descrição: %s\n", medicamentosmateriais[i].descricao);
            printf("Fabricante: %s\n", medicamentosmateriais[i].fabricante);
            printf("Preço de Custo: %.2f\n", medicamentosmateriais[i].precoCusto);
            printf("Preço de Venda: %.2f\n", medicamentosmateriais[i].precoVenda);
            printf("Quantidade em Estoque: %ld\n", medicamentosmateriais[i].quantidadeEstoque);
            printf("Estoque Mínimo: %ld\n", medicamentosmateriais[i].estoqueMinimo);
            printf("Codigo do fornecedor:%ld\n", medicamentosmateriais[i].codfornecedor);
            return;
        }
    }
    printf("medicamento ou material não encontrado\n");
    return;
}
