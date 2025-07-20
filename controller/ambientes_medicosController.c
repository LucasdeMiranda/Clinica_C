#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambiente, long int *codigoatual, AmbienteMedico *novoambiente)
{
    AmbienteMedico *novo = realloc(ambientes, (*tamambiente + 1) * sizeof(AmbienteMedico));
    if (novo == NULL)
    { // erro ao alocar memoria
        return ambientes;
    }

    ambientes = novo;
    novoambiente->codigo = *codigoatual;

    // Copia os dados preenchidos no main para a nova posição do vetor
    ambientes[*tamambiente] = *novoambiente;

    (*tamambiente)++;
    (*codigoatual)++;

    return ambientes;
}

long int alterarambientemedico(AmbienteMedico *ambientes, long int tamambiente, long int codigo)
{
    if (ambientes == NULL || tamambiente == 0)
    {
        return -1; // lista vazia
    }
    for (int i = 0; i < tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {
            return i; // retorna a posição
        }
    }
    return -1;
}

void listarambiente(AmbienteMedico *ambientes, long int tamambiente)
{
    if (ambientes == NULL || tamambiente == 0)
    {
        printf("lista de ambientes vazia\n");
        return;
    }
    for (int i = 0; i < tamambiente; i++)
    {
        printf("Código: %ld\n", ambientes[i].codigo);
        printf("Descrição do procedimento: %s\n", ambientes[i].descricaoProcedimento);
    }
    return;
}

AmbienteMedico *excluirambientemedico(AmbienteMedico *ambientes, long int *tamambiente, int codigo)
{
    int encontrado = -1;
    if (ambientes == NULL || *tamambiente == 0)
    {
        return ambientes;
    }

    for (int i = 0; i < *tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        return ambientes;
    }
    else
    {
        for (int j = encontrado; j < *tamambiente - 1; j++)
        {
            ambientes[j] = ambientes[j + 1];
        }
        (*tamambiente)--;

        if (*tamambiente == 0)
        {
            free(ambientes);
            return NULL;
        }
        AmbienteMedico *aux = realloc(ambientes, (*tamambiente) * sizeof(AmbienteMedico));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return ambientes;
        }
        else
        {
            ambientes = aux;
        }
    }
    return ambientes;
}

long int consultaambiente(AmbienteMedico *ambientes, long int tamambiente, long int codigo)
{
    if (ambientes == NULL || tamambiente == 0)
    {

        return -1;
    }
    for (int i = 0; i < tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {

            return i;
        }
    }

    return -1;
}

long int importarambiente(AmbienteMedico **ambientes, char *nome, long int *tamambientes, long int *codigoatual)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1;
    }

    char linha[1000];
    AmbienteMedico novo;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "<tabela nome=\"ambiente\">") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</tabela>") == NULL)
            {
                if (strstr(linha, "<codigo>") != NULL)
                {
                    sscanf(linha, "<codigo>%ld</codigo>", &novo.codigo);
                }

                if (strstr(linha, "<descricao>") != NULL)
                {
                    sscanf(linha, "<descricao>%999[^<]</descricao>", novo.descricaoProcedimento);
                }

                if (strstr(linha, "</registro>") != NULL)
                {
                    *ambientes = cadastrarambientemedico(*ambientes, tamambientes, codigoatual, &novo);
                }
            }
            break;
        }
    }

    fclose(arquivo);
    return 0;
}

long int exportarambiente(AmbienteMedico *ambientes, char *nome, long int tamambientes)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
    {
        return -1;
    }

    if (ambientes == NULL)
    {
        fclose(arquivo);
        return -1;
    }

    fprintf(arquivo, "<dados>\n");
    fprintf(arquivo, "<!-- Tabela de Ambientes Médicos -->\n");
    fprintf(arquivo, "<tabela nome=\"ambiente\">\n");

    for (long int i = 0; i < tamambientes; i++)
    {
        fprintf(arquivo, "<registro>\n");
        fprintf(arquivo, "<codigo>%ld</codigo>\n", ambientes[i].codigo);
        fprintf(arquivo, "<descricao>%s</descricao>\n", ambientes[i].descricaoProcedimento);
        fprintf(arquivo, "</registro>\n");
    }

    fprintf(arquivo, "</tabela>\n");
    fprintf(arquivo, "</dados>\n");

    fclose(arquivo);
    return 0;
}

long int importarambientemedicotxt(AmbienteMedico **ambientes, long int *tamambiente, long int *codigoatual, char *nome) {
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL) {
        return -1;
    }

    char linha[1100];
    AmbienteMedico novoambiente;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, ";");
        if (token != NULL)
            novoambiente.codigo = strtol(token, NULL, 10);

        token = strtok(NULL, ";\n");
        if (token != NULL)
            strncpy(novoambiente.descricaoProcedimento, token, sizeof(novoambiente.descricaoProcedimento));

        *ambientes = cadastrarambientemedico(*ambientes, tamambiente, codigoatual, &novoambiente);
    }

    fclose(arquivo);
    return 0;
}

void exportarambientemedicotxt(AmbienteMedico *ambientes, char *nome, long int tamambiente) {
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL) {
        return; // erro
    }

    for (long int i = 0; i < tamambiente; i++) {
        fprintf(arquivo, "%ld;%s\n", ambientes[i].codigo, ambientes[i].descricaoProcedimento);
    }

    fclose(arquivo);
}
