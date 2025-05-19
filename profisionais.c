#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuprofisionais()
{
    Profissional *profisionais = NULL;
    long int tamprofisionais = 0, codigoatual = 0, codigo;
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
                profisionais = cadastrarprofissionalsaude(profisionais, &tamprofisionais, &codigoatual);
            }
            else if (op == 2)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                alterarprofissional(profisionais, tamprofisionais, codigo);
            }
            else if (op == 3)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                profisionais = excluirprofisional(profisionais, &tamprofisionais, codigo);
            }
            else if (op == 4)
            {
                listarprofissional(profisionais, tamprofisionais);
            }
            else if (op == 5)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                consultaprofisional(profisionais, tamprofisionais, codigo);
            }
        }

    } while (op != 6);
    free(profisionais);
}
Profissional *cadastrarprofissionalsaude(Profissional *profissionais, long int *tamprofisionais, long int *codigoatual)
{
    Profissional *novo = realloc(profissionais, (*tamprofisionais + 1) * sizeof(Profissional));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return profissionais;
    }

    profissionais = novo;

    profissionais[*tamprofisionais].codigo = *codigoatual;

    printf("Digite o nome completo: ");
    scanf(" %[^\n]", profissionais[*tamprofisionais].nomeCompleto);

    printf("Digite o CRM: ");
    scanf(" %[^\n]", profissionais[*tamprofisionais].crm);

    printf("Digite a especialidade: ");
    scanf(" %[^\n]", profissionais[*tamprofisionais].especialidade);

    printf("Digite o CPF: ");
    scanf("  %[^\n]", profissionais[*tamprofisionais].cpf);

    printf("Digite o telefone: ");
    scanf(" %[^\n]", profissionais[*tamprofisionais].telefone);

    printf("Digite o email: ");
    scanf(" %[^\n]", profissionais[*tamprofisionais].email);
    printf("Profissional cadastrado com sucesso\n");

    (*tamprofisionais)++;
    (*codigoatual)++;
    return profissionais;
}

void alterarprofissional(Profissional *profisionais, long int tamprofisional, long int codigo)
{
    if (profisionais == NULL)
    {
        printf("Lista de profissionais vazia");
        return;
    }

    for (int i = 0; i < tamprofisional; i++)
    {
        if (profisionais[i].codigo == codigo)
        {
            printf("Digite o nome completo: ");
            scanf(" %[^\n]", profisionais[i].nomeCompleto);

            printf("Digite o CRM: ");
            scanf(" %[^\n]", profisionais[i].crm);

            printf("Digite a especialidade: ");
            scanf(" %[^\n]", profisionais[i].especialidade);

            printf("Digite o CPF: ");
            scanf(" %[^\n]", profisionais[i].cpf);

            printf("Digite o telefone: ");
            scanf(" %[^\n]", profisionais[i].telefone);

            printf("Digite o email: ");
            scanf(" %[^\n]", profisionais[i].email);
            printf("Profissional alterado com sucesso\n");
        }
    }
    return;
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
        printf("lista de profissionais vazia\n");
        return profisionais;
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
        printf("profissional não encontrado\n");
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
            printf("excluido com sucesso\n");
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
            printf("excluido com sucesso\n");
        }
    }
    return profisionais;
}

void consultaprofisional(Profissional *profisionais, long int tamprofisional, long int codigo)
{
    if (profisionais == NULL || tamprofisional == 0)
    {
        printf("Lista de profissionais vazia.\n");
        return;
    }

    for (int i = 0; i < tamprofisional; i++)
    {
        if (profisionais[i].codigo == codigo)
        {
            printf("Código: %ld\n", profisionais[i].codigo);
            printf("Nome: %s\n", profisionais[i].nomeCompleto);
            printf("CRM: %s\n", profisionais[i].crm);
            printf("Especialidade: %s\n", profisionais[i].especialidade);
            printf("CPF: %s\n", profisionais[i].cpf);
            printf("Telefone: %s\n", profisionais[i].telefone);
            printf("Email: %s\n", profisionais[i].email);
            return;
        }
    }
    printf("profissional não encontrado\n");
    return;
}
