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
long int importarprofissional(Profissional **profissionais, char *nome, long int *tamprofissionais, long int *codigoatual)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1;
    }

    char linha[1000];
    Profissional novoprofissional;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "<tabela nome=\"profissional\">") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</tabela>") == NULL)
            {
                if (strstr(linha, "<codigo>") != NULL)
                    sscanf(linha, "<codigo>%ld</codigo>", &novoprofissional.codigo);

                if (strstr(linha, "<nome>") != NULL)
                    sscanf(linha, "<nome>%199[^<]</nome>", novoprofissional.nomeCompleto);

                if (strstr(linha, "<crm>") != NULL)
                    sscanf(linha, "<crm>%49[^<]</crm>", novoprofissional.crm);

                if (strstr(linha, "<especialidade>") != NULL)
                    sscanf(linha, "<especialidade>%399[^<]</especialidade>", novoprofissional.especialidade);

                if (strstr(linha, "<telefone>") != NULL)
                    sscanf(linha, "<telefone>%19[^<]</telefone>", novoprofissional.telefone);

                if (strstr(linha, "<email>") != NULL)
                    sscanf(linha, "<email>%299[^<]</email>", novoprofissional.email);

                if (strstr(linha, "</registro>") != NULL)
                {
                    strcpy(novoprofissional.cpf, ""); // Não vem do XML
                    *profissionais = cadastrarprofissionalsaude(*profissionais, tamprofissionais, codigoatual, &novoprofissional);
                }
            }
            break;
        }
    }

    fclose(arquivo);
    return 0;
}

long int exportarprofissional(Profissional *profissionais, char *nome, long int tamprofissionais)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL || profissionais == NULL)
        return -1;

    fprintf(arquivo, "<dados>\n");
    fprintf(arquivo, "<!-- Tabela de Profissionais de Saúde -->\n");
    fprintf(arquivo, "<tabela nome=\"profissional\">\n");

    for (long int i = 0; i < tamprofissionais; i++)
    {
        fprintf(arquivo, "<registro>\n");
        fprintf(arquivo, "<codigo>%ld</codigo>\n", profissionais[i].codigo);
        fprintf(arquivo, "<nome>%s</nome>\n", profissionais[i].nomeCompleto);
        fprintf(arquivo, "<crm>%s</crm>\n", profissionais[i].crm);
        fprintf(arquivo, "<especialidade>%s</especialidade>\n", profissionais[i].especialidade);
        fprintf(arquivo, "<telefone>%s</telefone>\n", profissionais[i].telefone);
        fprintf(arquivo, "<email>%s</email>\n", profissionais[i].email);
        fprintf(arquivo, "</registro>\n");
    }

    fprintf(arquivo, "</tabela>\n");
    fprintf(arquivo, "</dados>\n");

    fclose(arquivo);
    return 0;
}

long int importarprofissionaltxt(Profissional **profissionais, long int *tamprofissionais, long int *codigoatual, char *nome)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1;
    }

    char linha[1024];
    Profissional novo;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        char *token = strtok(linha, ";");
        if (token != NULL)
            novo.codigo = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novo.nomeCompleto, token, sizeof(novo.nomeCompleto));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novo.crm, token, sizeof(novo.crm));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novo.especialidade, token, sizeof(novo.especialidade));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novo.cpf, token, sizeof(novo.cpf));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novo.telefone, token, sizeof(novo.telefone));

        token = strtok(NULL, ";\n");
        if (token != NULL)
            strncpy(novo.email, token, sizeof(novo.email));

        *profissionais = cadastrarprofissionalsaude(*profissionais, tamprofissionais, codigoatual, &novo);
    }

    fclose(arquivo);
    return 0;
}

void exportarprofissionaltxt(Profissional *profissionais, char *nome, long int tamprofissionais)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
    {
        return; // erro ao abrir o arquivo
    }

    for (long int i = 0; i < tamprofissionais; i++)
    {
        fprintf(arquivo, "%ld;%s;%s;%s;%s;%s;%s\n",
                profissionais[i].codigo,
                profissionais[i].nomeCompleto,
                profissionais[i].crm,
                profissionais[i].especialidade,
                profissionais[i].cpf,
                profissionais[i].telefone,
                profissionais[i].email);
    }

    fclose(arquivo);
}
