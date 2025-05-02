#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuprocedimentos()
{
    Procedimento *procedimentos = NULL;
    long int tamprocedimento = 0;
    int op, cpf;

    do
    {
        op = 0, cpf = 0;
        printf("1:Cadastrar procedimento\n:");
        printf("2:Alterar procedimento\n:");
        printf("3: Excluir procedimento");
        printf("4:Listar procedimentos");
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
                procedimentos = cadastrarprocedimento(procedimentos, &tamprocedimento);
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
Procedimento *cadastrarprocedimento(Procedimento *procedimentos, long int *tamprocedimento)
{
    Procedimento *novo = realloc(procedimentos, (*tamprocedimento + 1) * sizeof(Procedimento));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return procedimentos;
    }

    procedimentos = novo;

    printf("Digite o código: ");
    scanf("%d", &procedimentos[*tamprocedimento].codigo);

    printf("Digite a descrição: ");
    scanf(" %[^\n]", procedimentos[*tamprocedimento].descricao);

    printf("Digite o custo: ");
    scanf("%f", &procedimentos[*tamprocedimento].custo);

    printf("Digite o tempo estimado (em minutos): ");
    scanf("%d", &procedimentos[*tamprocedimento].tempoEstimado);

    printf("Digite a quantidade de itens: ");
    scanf("%d", &procedimentos[*tamprocedimento].quantidadeItens);

    printf("Digite o código do ambiente médico: ");
    scanf("%d", &procedimentos[*tamprocedimento].ambientemedico.codigo);

    printf("Digite a descrição do ambiente médico: ");
    scanf(" %[^\n]", procedimentos[*tamprocedimento].ambientemedico.descricaoProcedimento);

    (*tamprocedimento)++;
    return procedimentos;
}
