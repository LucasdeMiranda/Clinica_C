#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menumedicamentos_materiais()
{
    MedicamentoMaterial *medicamentosmateriais = NULL;
    long int tammedicamentomaterial = 0;
    int op, cpf;

    do
    {
        op = 0, cpf = 0;
        printf("1:Cadastrar medicamento ou materiai\n:");
        printf("2:Alterar  medicamentos ou materiais\n:");
        printf("3: Excluir medicamento ou material");
        printf("4:Listar medicamentos e materiais");
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
                medicamentosmateriais = cadastrarmedicamentomaterial(medicamentosmateriais, &tammedicamentomaterial);
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
MedicamentoMaterial *cadastrarmedicamentomaterial(MedicamentoMaterial *itens, long int *tammedicamentomaterial)
{
    MedicamentoMaterial *novo = realloc(itens, (*tammedicamentomaterial + 1) * sizeof(MedicamentoMaterial));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return itens;
    }

    itens = novo;

    printf("Digite o código: ");
    scanf("%d", &itens[*tammedicamentomaterial].codigo);

    printf("Digite a descrição: ");
    scanf(" %[^\n]", itens[*tammedicamentomaterial].descricao);

    printf("Digite o fabricante: ");
    scanf(" %[^\n]", itens[*tammedicamentomaterial].fabricante);

    printf("Digite o preço de custo: ");
    scanf("%f", &itens[*tammedicamentomaterial].precoCusto);

    printf("Digite o preço de venda: ");
    scanf("%f", &itens[*tammedicamentomaterial].precoVenda);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &itens[*tammedicamentomaterial].quantidadeEstoque);

    printf("Digite o estoque mínimo: ");
    scanf("%d", &itens[*tammedicamentomaterial].estoqueMinimo);

    (*tammedicamentomaterial)++;
    return itens;
}
