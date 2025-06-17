#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menumedicamentos_materiais(MedicamentoMaterial **medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual)
{
    long int codigo, auxtam = 0, posicao;
    int op;

    do
    {
        op = 0, codigo = 0;
        printf("1: Cadastrar medicamento ou materiais\n");
        printf("2: Alterar medicamentos ou materiais\n");
        printf("3: Excluir medicamento ou material\n");
        printf("4: Listar medicamentos e materiais\n");
        printf("5: Consultar medicamento ou material\n");
        printf("6: Sair\n");
        scanf("%d", &op);

        if (op <= 0 || op > 6)
        {
            printf("Opção inválida! Tente novamente\n");
        }
        else
        {
            if (op == 1)
            {
                MedicamentoMaterial novomedicamentomaterial;
                auxtam = *tammedicamentomaterial;

                printf("Digite a descrição: ");
                scanf(" %999[^\n]", novomedicamentomaterial.descricao);

                printf("Digite o fabricante: ");
                scanf(" %299[^\n]", novomedicamentomaterial.fabricante);

                printf("Digite o preço de custo: ");
                scanf("%f", &novomedicamentomaterial.precoCusto);

                printf("Digite o preço de venda: ");
                scanf("%f", &novomedicamentomaterial.precoVenda);

                printf("Digite a quantidade em estoque: ");
                scanf("%ld", &novomedicamentomaterial.quantidadeEstoque);

                printf("Digite o estoque mínimo: ");
                scanf("%ld", &novomedicamentomaterial.estoqueMinimo);

                printf("Digite o código do fornecedor: ");
                scanf("%ld", &novomedicamentomaterial.codfornecedor);

                *medicamentosmateriais = cadastrarmedicamentomaterial(*medicamentosmateriais, tammedicamentomaterial, codigoatual, &novomedicamentomaterial);

                if (*tammedicamentomaterial > auxtam)
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
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                posicao = alterarmedicamentomaterial(*medicamentosmateriais, *tammedicamentomaterial, codigo);

                if (posicao == -1)
                {
                    printf("Medicamento não encontrado ou lista vazia\n");
                }
                else
                {
                    printf("Digite a descrição: ");
                    scanf(" %999[^\n]", (*medicamentosmateriais)[posicao].descricao);

                    printf("Digite o fabricante: ");
                    scanf(" %299[^\n]", (*medicamentosmateriais)[posicao].fabricante);

                    printf("Digite o preço de custo: ");
                    scanf("%f", &(*medicamentosmateriais)[posicao].precoCusto);

                    printf("Digite o preço de venda: ");
                    scanf("%f", &(*medicamentosmateriais)[posicao].precoVenda);

                    printf("Digite a quantidade em estoque: ");
                    scanf("%ld", &(*medicamentosmateriais)[posicao].quantidadeEstoque);

                    printf("Digite o estoque mínimo: ");
                    scanf("%ld", &(*medicamentosmateriais)[posicao].estoqueMinimo);

                    printf("Digite o código do fornecedor: ");
                    scanf("%ld", &(*medicamentosmateriais)[posicao].codfornecedor);

                    printf("Medicamento ou material alterado com sucesso\n");
                }
            }
            else if (op == 3)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                auxtam = *tammedicamentomaterial;

                *medicamentosmateriais = excluimedicamentomaterial(*medicamentosmateriais, tammedicamentomaterial, codigo);

                if (*tammedicamentomaterial < auxtam)
                {
                    printf("Medicamento excluído com sucesso\n");
                }
                else
                {
                    printf("Medicamento não encontrado para exclusão.\n");
                }
            }
            else if (op == 4)
            {
                listarmedicamentomaterial(*medicamentosmateriais, *tammedicamentomaterial);
            }
            else if (op == 5)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                posicao = consultamedicamentomaterial(*medicamentosmateriais, *tammedicamentomaterial, codigo);

                if (posicao == -1)
                {
                    printf("Medicamento não encontrado\n");
                }
                else
                {
                    printf("Código: %ld\n", (*medicamentosmateriais)[posicao].codigo);
                    printf("Descrição: %s\n", (*medicamentosmateriais)[posicao].descricao);
                    printf("Fabricante: %s\n", (*medicamentosmateriais)[posicao].fabricante);
                    printf("Preço de Custo: %.2f\n", (*medicamentosmateriais)[posicao].precoCusto);
                    printf("Preço de Venda: %.2f\n", (*medicamentosmateriais)[posicao].precoVenda);
                    printf("Quantidade em Estoque: %ld\n", (*medicamentosmateriais)[posicao].quantidadeEstoque);
                    printf("Estoque Mínimo: %ld\n", (*medicamentosmateriais)[posicao].estoqueMinimo);
                    printf("Código do fornecedor: %ld\n", (*medicamentosmateriais)[posicao].codfornecedor);
                }
            }
        }

    } while (op != 6);
}
