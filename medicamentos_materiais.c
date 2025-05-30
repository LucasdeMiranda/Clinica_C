#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menumedicamentos_materiais()
{
    MedicamentoMaterial *medicamentosmateriais = NULL;
    long int tammedicamentomaterial = 0, codigoatual = 0, codigo, auxtam = 0, posicao;
    int op;

    do
    {
        op = 0, codigo = 0;
        printf("1:Cadastrar medicamento ou materiais\n");
        printf("2:Alterar  medicamentos ou materiais\n");
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
                MedicamentoMaterial novomedicamentomaterial;
                auxtam = tammedicamentomaterial;
                printf("Digite a descrição: ");
                scanf(" %[^\n]", novomedicamentomaterial.descricao);

                printf("Digite o fabricante: ");
                scanf(" %[^\n]", novomedicamentomaterial.fabricante);

                printf("Digite o preço de custo: ");
                scanf("%f", &novomedicamentomaterial.precoCusto);

                printf("Digite o preço de venda: ");
                scanf("%f", &novomedicamentomaterial.precoVenda);

                printf("Digite a quantidade em estoque: ");
                scanf("%ld", &novomedicamentomaterial.quantidadeEstoque);

                printf("Digite o estoque mínimo: ");
                scanf("%ld", &novomedicamentomaterial.estoqueMinimo);
                printf("Digite o código do fornecedor:");
                scanf("%ld", &novomedicamentomaterial.codfornecedor);

                medicamentosmateriais = cadastrarmedicamentomaterial(medicamentosmateriais, &tammedicamentomaterial, &codigoatual, &novomedicamentomaterial);
                if (tammedicamentomaterial > auxtam)
                {
                    printf("Medicamento ou material cadastrado com sucesso\n");
                }
                else
                {
                    printf("Erro ao cadastrar medicamento\n");
                }
            }

            else if (op == 2)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                posicao = alterarmedicamentomaterial(medicamentosmateriais, tammedicamentomaterial, codigo);
                if (posicao == -1)
                {
                    printf("Medicamento não encontrado ou lista vazia\n");
                }
                else
                {
                    printf("Digite a descrição: ");
                    scanf(" %[^\n]", medicamentosmateriais[posicao].descricao);

                    printf("Digite o fabricante: ");
                    scanf(" %[^\n]", medicamentosmateriais[posicao].fabricante);

                    printf("Digite o preço de custo: ");
                    scanf("%f", &medicamentosmateriais[posicao].precoCusto);

                    printf("Digite o preço de venda: ");
                    scanf("%f", &medicamentosmateriais[posicao].precoVenda);

                    printf("Digite a quantidade em estoque: ");
                    scanf("%ld", &medicamentosmateriais[posicao].quantidadeEstoque);

                    printf("Digite o estoque mínimo: ");
                    scanf("%ld", &medicamentosmateriais[posicao].estoqueMinimo);
                    printf("Digite o código do fornecedor:");
                    scanf("%ld", &medicamentosmateriais[posicao].codfornecedor);
                    printf("Medicamento ou material alterado com sucesso\n");
                }
            }
            else if (op == 3)
            {
                printf("digite o código:");
                scanf("%ld", &codigo);
                auxtam = tammedicamentomaterial;
                medicamentosmateriais = excluimedicamentomaterial(medicamentosmateriais, &tammedicamentomaterial, codigo);
                if (tammedicamentomaterial < auxtam)
                {
                    printf("Medicamento excluido com sucesso\n");
                }
                else
                {
                    printf("Medicamento não encontrado para exclusão.\n");
                }
            }
            else if (op == 4)
            {
                listarmedicamentomaterial(medicamentosmateriais, tammedicamentomaterial);
            }
            else if (op == 5)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                posicao = consultamedicamentomaterial(medicamentosmateriais, tammedicamentomaterial, codigo);
                if (posicao == -1)
                {
                    printf("Medicamento não encontrado\n");
                }
                else
                {
                    printf("Código: %ld\n", medicamentosmateriais[posicao].codigo);
                    printf("Descrição: %s\n", medicamentosmateriais[posicao].descricao);
                    printf("Fabricante: %s\n", medicamentosmateriais[posicao].fabricante);
                    printf("Preço de Custo: %.2f\n", medicamentosmateriais[posicao].precoCusto);
                    printf("Preço de Venda: %.2f\n", medicamentosmateriais[posicao].precoVenda);
                    printf("Quantidade em Estoque: %ld\n", medicamentosmateriais[posicao].quantidadeEstoque);
                    printf("Estoque Mínimo: %ld\n", medicamentosmateriais[posicao].estoqueMinimo);
                    printf("Codigo do fornecedor:%ld\n", medicamentosmateriais[posicao].codfornecedor);
                }
            }
        }

    } while (op != 6);
    free(medicamentosmateriais);
}
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
