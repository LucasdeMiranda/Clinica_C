#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuestoque(Entradaestoque **entradaestoque, MedicamentoMaterial **medicamentosmateriais, long int tammedicamentomaterial, long int *tamentradaestoque)
{
    long int aux;
    int op;
    do
    {
        printf("1:Ver situação do estoque\n");
        printf("2:Receber estoque\n");
        printf("3:Sair\n");
        scanf("%d", &op);
        if (op < 1 || op > 3)
        {
            printf("opção invalida tente novamente\n");
        }
        else if (op == 1)
        {
            estoqueminimo(*medicamentosmateriais, tammedicamentomaterial);
        }
        else if (op == 2)
        {
            Entradaestoque novoentradaestoque;
            aux = *tamentradaestoque;
            printf("digite o fornecedor:");
            scanf(" %999[^\n]", novoentradaestoque.fornecedor);
             printf("digite o codigo do fornecedor:");
            scanf("%ld",&novoentradaestoque.codfornecedor);
            printf("digite o cnpj:");
            scanf(" %999[^\n]", novoentradaestoque.cnpj);
            printf("digite o frete:");
            scanf("%f", &novoentradaestoque.frete);
            printf("digite o imposto:");
            scanf("%f", &novoentradaestoque.imposto);
            printf("digite quantos produtos será dada a entrada:");
            scanf("%ld", &novoentradaestoque.tammedicamentosmateriaisrecebidos);
            novoentradaestoque.codmedicamentosmateriaisrecebidos = malloc(novoentradaestoque.tammedicamentosmateriaisrecebidos * sizeof(Codmateriaisrecebidos));
            if (novoentradaestoque.codmedicamentosmateriaisrecebidos == NULL)
            {
                printf("erro ao alocar memoria para o vetor de materiais recebidos\n");
            }
            else
            {
                for (int i = 0; i < novoentradaestoque.tammedicamentosmateriaisrecebidos; i++)
                {
                    printf("Digite o codigo do material:%d",i+1);
                    scanf("%ld",& novoentradaestoque.codmedicamentosmateriaisrecebidos[i].codigo);
                    printf("Digite o preço de custo da unidade do material %d:",i+1);
                    scanf("%f",&novoentradaestoque.codmedicamentosmateriaisrecebidos[i].precocustounid);
                    printf("Digite a quantidade recebida do material %d:",i+1);
                    scanf("%ld",&novoentradaestoque.codmedicamentosmateriaisrecebidos[i].qnt);
                }
                *entradaestoque=cadastrarentradaestoque(*entradaestoque,tamentradaestoque,*medicamentosmateriais,
                    tammedicamentomaterial,&novoentradaestoque);
                    if(*tamentradaestoque>aux){
                        printf("Sucesso ao cadastrar estoque\n");
                        alterarpreco(&novoentradaestoque, *medicamentosmateriais, tammedicamentomaterial);
                        free(novoentradaestoque.codmedicamentosmateriaisrecebidos);
                    }

                    else{
                        printf("Erro ao cadastrar estoque\n");
                    }
                    
            }
        }
    } while (op != 3);
}