#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuprocedimentos(Procedimento **procedimentos, long int *tamprocedimento, long int *codigoatual, AmbienteMedico *ambientes, MedicamentoMaterial *medicamentosmateriais,
                       long int tamambientes, long int tammedicamentomaterial)
{
    long int codigo, auxtam = 0, posicao;
    int op;

    do
    {
        op = 0;
        codigo = 0;
        printf("1:Cadastrar procedimento\n");
        printf("2:Alterar procedimento\n");
        printf("3:Excluir procedimento\n");
        printf("4:Listar procedimentos\n");
        printf("5:Consultar procedimento\n");
        printf("6:Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        if (op <= 0 || op > 6)
        {
            printf("Opção inválida! Tente novamente\n");
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

                printf("Digite o código do ambiente médico: ");
                scanf("%ld", &novoprocedimento.codambientemedico);

                printf("Digite quantos materiais e medicamentos serão utilizados: ");
                scanf("%ld", &novoprocedimento.tamcodmedicamentosmateriais);

                novoprocedimento.codmedicamentosemateriais = malloc(novoprocedimento.tamcodmedicamentosmateriais * sizeof(Codmedicamentosmateriais));
                if (novoprocedimento.codmedicamentosemateriais == NULL)
                {
                    printf("Erro ao alocar memória para os medicamentos/materiais\n");
                }

                for (int i = 0; i < novoprocedimento.tamcodmedicamentosmateriais; i++)
                {
                    printf("Digite o código do material %d: ", i + 1);
                    scanf("%ld", &novoprocedimento.codmedicamentosemateriais[i].codigo);

                    printf("Digite a quantidade usada do material %ld: ", novoprocedimento.codmedicamentosemateriais[i].codigo);
                    scanf("%ld", &novoprocedimento.codmedicamentosemateriais[i].qnt);
                }

                *procedimentos = cadastrarprocedimento(*procedimentos, tamprocedimento, codigoatual, &novoprocedimento, ambientes, medicamentosmateriais, tamambientes, tammedicamentomaterial);
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
                printf("Digite o código: ");
                scanf("%ld", &codigo);
                alterarprocedimento(*procedimentos, *tamprocedimento, codigo);
            }
            else if (op == 3)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);
                auxtam = *tamprocedimento;
                *procedimentos = excluirprocedimento(*procedimentos, tamprocedimento, codigo);
                if (*tamprocedimento < auxtam)
                {
                    printf("Excluído com sucesso\n");
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
                printf("Digite o código: ");
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
                            printf("Código do material: %ld - Quantidade usada: %ld\n",
                                   (*procedimentos)[posicao].codmedicamentosemateriais[j].codigo,
                                   (*procedimentos)[posicao].codmedicamentosemateriais[j].qnt);
                        }
                    }
                }
            }
        }

    } while (op != 6);
}
