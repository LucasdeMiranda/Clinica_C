#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuprofisionais()
{
    Profissional *profisionais = NULL;
    long int tamprofisionais = 0, codigoatual = 0, codigo, auxtam = 0, posicao;
    int op;

    do
    {

        op = 0, codigo = 0;
        printf("1:Cadastrar profisional\n:");
        printf("2:Alterar profisional\n:");
        printf("3: Excluir profisional\n");
        printf("4:Listar profisionais\n");
        printf("5:Consultar profissional\n");
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
                Profissional novoprofisional;
                auxtam = tamprofisionais;
                printf("Digite o nome completo: ");
                scanf(" %199[^\n]", novoprofisional.nomeCompleto);

                printf("Digite o CRM: ");
                scanf(" %49[^\n]", novoprofisional.crm);

                printf("Digite a especialidade: ");
                scanf(" %399[^\n]", novoprofisional.especialidade);

                printf("Digite o CPF: ");
                scanf("  %49[^\n]", novoprofisional.cpf);

                printf("Digite o telefone: ");
                scanf(" %20[^\n]", novoprofisional.telefone);

                printf("Digite o email: ");
                scanf(" %299[^\n]", novoprofisional.email);
                profisionais = cadastrarprofissionalsaude(profisionais, &tamprofisionais, &codigoatual, &novoprofisional);
                if (tamprofisionais > auxtam)
                {
                    printf("Profissional cadastrado com sucesso\n");
                }
                else
                {
                    printf("Erro ao cadastrar profisional\n");
                }
            }

            else if (op == 2)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                posicao = alterarprofissional(profisionais, tamprofisionais, codigo);
                if (posicao == -1)
                {
                    printf("Profissional não encontrado ou lista vazia\n");
                }
                else
                {
                    printf("Digite o nome completo: ");
                    scanf(" %199[^\n]", profisionais[posicao].nomeCompleto);

                    printf("Digite o CRM: ");
                    scanf(" %49[^\n]", profisionais[posicao].crm);

                    printf("Digite a especialidade: ");
                    scanf(" %399[^\n]", profisionais[posicao].especialidade);

                    printf("Digite o CPF: ");
                    scanf(" %49[^\n]", profisionais[posicao].cpf);

                    printf("Digite o telefone: ");
                    scanf(" %19[^\n]", profisionais[posicao].telefone);

                    printf("Digite o email: ");
                    scanf(" %299[^\n]", profisionais[posicao].email);
                    printf("Profissional alterado com sucesso\n");
                }
            }
            else if (op == 3)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                auxtam = tamprofisionais;
                profisionais = excluirprofisional(profisionais, &tamprofisionais, codigo);
                if (tamprofisionais < auxtam)
                {
                    printf(" Profissional excluido com sucesso\n");
                }
                else
                {
                    printf("Profissional não encontrado para exclusão\n");
                }
            }
            else if (op == 4)
            {
                listarprofissional(profisionais, tamprofisionais);
            }
            else if (op == 5)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                posicao = consultaprofisional(profisionais, tamprofisionais, codigo);
                if (posicao == -1)
                {
                    printf("Profissional não encontrado\n");
                }
                else
                {
                    printf("Código: %ld\n", profisionais[posicao].codigo);
                    printf("Nome: %s\n", profisionais[posicao].nomeCompleto);
                    printf("CRM: %s\n", profisionais[posicao].crm);
                    printf("Especialidade: %s\n", profisionais[posicao].especialidade);
                    printf("CPF: %s\n", profisionais[posicao].cpf);
                    printf("Telefone: %s\n", profisionais[posicao].telefone);
                    printf("Email: %s\n", profisionais[posicao].email);
                }
            }
        }

    } while (op != 6);
    free(profisionais);
}