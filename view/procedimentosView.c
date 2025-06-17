#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuprocedimentos(Procedimento **procedimentos, long int *tamprocedimento, long int *codigoatual)
{
    long int codigo, auxtam = 0, posicao;
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
                Procedimento novoprocedimento;
                auxtam = *tamprocedimento;
                printf("Digite a descrição do procedimento: ");
                scanf(" %1999[^\n]", novoprocedimento.descricao);

                printf("Digite o custo: ");
                scanf("%f", &novoprocedimento.custo);

                printf("Digite o tempo estimado em minutos: ");
                scanf("%ld", &novoprocedimento.tempoEstimado);

                printf("digite o código do ambiente médico:");
                scanf("%ld", &novoprocedimento.codambientemedico);

                printf("digite quantos materiais e medicamentos seram utilizados:");
                scanf("%ld", &novoprocedimento.tamcodmedicamentosmateriais);
                novoprocedimento.codmedicamentosemateriais = malloc(novoprocedimento.tamcodmedicamentosmateriais * sizeof(long int));

                if (novoprocedimento.codmedicamentosemateriais == NULL)
                {
                    printf("Erro ao alocar memória para os códigos de medicamentos/materiais\n");
                }
                for (int i = 0; i < novoprocedimento.tamcodmedicamentosmateriais; i++)
                {
                    printf("Digite o código do material %d: ", i + 1);
                    scanf("%ld", &novoprocedimento.codmedicamentosemateriais[i]);
                }

                *procedimentos = cadastrarprocedimento(*procedimentos, tamprocedimento, codigoatual, &novoprocedimento);
                if (*tamprocedimento > auxtam)
                {
                    printf("Procedimento cadastrado com sucesso\n");
                    free(novoprocedimento.codmedicamentosemateriais);
                }
                else
                {
                    printf("Erro ao cadastrar procedimento\n");
                }
            }

            else if (op == 2)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                alterarprocedimento(*procedimentos, *tamprocedimento, codigo);
            }
            else if (op == 3)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                auxtam = *tamprocedimento;
                *procedimentos = excluirprocedimento(*procedimentos, tamprocedimento, codigo);
                if (*tamprocedimento < auxtam)
                {
                    printf("excluido com sucesso\n");
                }
                else
                {
                    printf("Procedimento não encontrado para exclusão\n");
                }
            }
            else if (op == 4)
            {
                listarprocedimento(*procedimentos, *tamprocedimento);
            }
            else if (op == 5)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                posicao = consultaprocedimento(*procedimentos, *tamprocedimento, codigo);

                if (posicao == -1)
                {
                    printf("Procedimento não encontrado\n");
                }
                else
                {
                    printf("Código do procedimento: %ld\n", (*procedimentos)[posicao].codigo);
                    printf("Descrição: %s\n", (*procedimentos)[posicao].descricao);
                    printf("Custo: R$ %.2f\n", (*procedimentos)[posicao].custo);
                    printf("Tempo estimado: %ld minutos\n", (*procedimentos)[posicao].tempoEstimado);
                    printf("Código do ambiente médico: %ld\n", (*procedimentos)[posicao].codambientemedico);
                    printf("Quantidade de materiais/medicamentos: %ld\n", (*procedimentos)[posicao].tamcodmedicamentosmateriais);

                    if ((*procedimentos)[posicao].codmedicamentosemateriais != NULL)
                    {
                        for (int j = 0; j < (*procedimentos)[posicao].tamcodmedicamentosmateriais; j++)
                        {
                            printf("Codigo do material:%ld\n", (*procedimentos)[posicao].codmedicamentosemateriais[j]);
                        }
                    }
                }
            }
        }

    } while (op != 6);
}
