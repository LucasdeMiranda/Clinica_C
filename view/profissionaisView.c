#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuprofisionais(Profissional **profissionais, long int *tamprofissionais, long int *codigoatual)
{
    long int codigo, auxtam = 0, posicao;
    int op;

    do
    {
        op = 0, codigo = 0;
        printf("1: Cadastrar profissional\n");
        printf("2: Alterar profissional\n");
        printf("3: Excluir profissional\n");
        printf("4: Listar profissionais\n");
        printf("5: Consultar profissional\n");
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
                Profissional novoprofissional;
                auxtam = *tamprofissionais;

                printf("Digite o nome completo: ");
                scanf(" %199[^\n]", novoprofissional.nomeCompleto);

                printf("Digite o CRM: ");
                scanf(" %49[^\n]", novoprofissional.crm);

                printf("Digite a especialidade: ");
                scanf(" %399[^\n]", novoprofissional.especialidade);

                printf("Digite o CPF: ");
                scanf(" %49[^\n]", novoprofissional.cpf);

                printf("Digite o telefone: ");
                scanf(" %19[^\n]", novoprofissional.telefone);

                printf("Digite o email: ");
                scanf(" %299[^\n]", novoprofissional.email);

                *profissionais = cadastrarprofissionalsaude(*profissionais, tamprofissionais, codigoatual, &novoprofissional);

                if (*tamprofissionais > auxtam)
                {
                    printf("Profissional cadastrado com sucesso\n");
                }
                else
                {
                    printf("Erro ao cadastrar profissional\n");
                }
            }
            else if (op == 2)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                posicao = alterarprofissional(*profissionais, *tamprofissionais, codigo);

                if (posicao == -1)
                {
                    printf("Profissional não encontrado ou lista vazia\n");
                }
                else
                {
                    printf("Digite o nome completo: ");
                    scanf(" %199[^\n]", (*profissionais)[posicao].nomeCompleto);

                    printf("Digite o CRM: ");
                    scanf(" %49[^\n]", (*profissionais)[posicao].crm);

                    printf("Digite a especialidade: ");
                    scanf(" %399[^\n]", (*profissionais)[posicao].especialidade);

                    printf("Digite o CPF: ");
                    scanf(" %49[^\n]", (*profissionais)[posicao].cpf);

                    printf("Digite o telefone: ");
                    scanf(" %19[^\n]", (*profissionais)[posicao].telefone);

                    printf("Digite o email: ");
                    scanf(" %299[^\n]", (*profissionais)[posicao].email);

                    printf("Profissional alterado com sucesso\n");
                }
            }
            else if (op == 3)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                auxtam = *tamprofissionais;

                *profissionais = excluirprofissional(*profissionais, tamprofissionais, codigo);

                if (*tamprofissionais < auxtam)
                {
                    printf("Profissional excluído com sucesso\n");
                }
                else
                {
                    printf("Profissional não encontrado para exclusão\n");
                }
            }
            else if (op == 4)
            {
                listarprofissional(*profissionais, *tamprofissionais);
            }
            else if (op == 5)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                posicao = consultaprofissional(*profissionais, *tamprofissionais, codigo);

                if (posicao == -1)
                {
                    printf("Profissional não encontrado\n");
                }
                else
                {
                    printf("Código: %ld\n", (*profissionais)[posicao].codigo);
                    printf("Nome: %s\n", (*profissionais)[posicao].nomeCompleto);
                    printf("CRM: %s\n", (*profissionais)[posicao].crm);
                    printf("Especialidade: %s\n", (*profissionais)[posicao].especialidade);
                    printf("CPF: %s\n", (*profissionais)[posicao].cpf);
                    printf("Telefone: %s\n", (*profissionais)[posicao].telefone);
                    printf("Email: %s\n", (*profissionais)[posicao].email);
                }
            }
        }

    } while (op != 6);
}
