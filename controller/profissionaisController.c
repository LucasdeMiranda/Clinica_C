#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
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

Profissional *excluirprofissional(Profissional *profisionais, long int *tamprofisional, long int codigo)
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

long int consultaprofissional(Profissional *profisionais, long int tamprofisional, long int codigo)
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
