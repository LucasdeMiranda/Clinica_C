#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view/biblioteca.h"

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
Profissional *cadastrarprofissionalsaude(Profissional *profissionais, long int *tamprofisionais, long int *codigoatual, Profissional *novoprofisional)
{
    Profissional *novo = realloc(profissionais, (*tamprofisionais + 1) * sizeof(Profissional));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return profissionais;
    }

    profissionais = novo;
    novoprofisional->codigo = *codigoatual;

    profissionais[*tamprofisionais] = *novoprofisional;

    (*tamprofisionais)++;
    (*codigoatual)++;
    return profissionais;
}

long int alterarprofissional(Profissional *profisionais, long int tamprofisional, long int codigo)
{
    if (profisionais == NULL)
    {
        return -1;
    }

    for (int i = 0; i < tamprofisional; i++)
    {
        if (profisionais[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}

void listarprofissional(Profissional *profisionais, long int tamprofisional)
{
    if (profisionais == NULL || tamprofisional == 0)
    {
        printf("Lista de profissionais vazia\n");
    }
    for (int i = 0; i < tamprofisional; i++)
    {
        printf("Código: %ld\n", profisionais[i].codigo);
        printf("Nome: %s\n", profisionais[i].nomeCompleto);
        printf("CRM: %s\n", profisionais[i].crm);
        printf("Especialidade: %s\n", profisionais[i].especialidade);
        printf("CPF: %s\n", profisionais[i].cpf);
        printf("Telefone: %s\n", profisionais[i].telefone);
        printf("Email: %s\n", profisionais[i].email);
    }
    return;
}

Profissional *excluirprofisional(Profissional *profisionais, long int *tamprofisional, long int codigo)
{
    int encontrado = -1;
    if (profisionais == NULL || *tamprofisional == 0)
    {
        return profisionais; // vazio
    }
    for (int i = 0; i < *tamprofisional; i++)
    {
        if (profisionais[i].codigo == codigo)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        return profisionais;
    }
    else
    {
        for (int j = encontrado; j < *tamprofisional - 1; j++)
        {
            profisionais[j] = profisionais[j + 1];
        }
        (*tamprofisional)--;
        if (*tamprofisional == 0)
        {
            free(profisionais);
            return NULL;
        }
        Profissional *aux = realloc(profisionais, (*tamprofisional) * sizeof(Profissional));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return profisionais;
        }
        else
        {
            profisionais = aux;
        }
    }
    return profisionais;
}

long int consultaprofisional(Profissional *profisionais, long int tamprofisional, long int codigo)
{
    if (profisionais == NULL || tamprofisional == 0)
    {
        return -1;
    }

    for (int i = 0; i < tamprofisional; i++)
    {
        if (profisionais[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}
