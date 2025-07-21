#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
MedicamentoMaterial *cadastrarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual, MedicamentoMaterial *novomedicamentomaterial)
{
    MedicamentoMaterial *novo = realloc(medicamentosmateriais, (*tammedicamentomaterial + 1) * sizeof(MedicamentoMaterial));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return medicamentosmateriais;
    }

    medicamentosmateriais = novo;
    novomedicamentomaterial->codigo = *codigoatual;
    medicamentosmateriais[*tammedicamentomaterial] = *novomedicamentomaterial;

    (*tammedicamentomaterial)++;
    (*codigoatual)++;
    return medicamentosmateriais;
}

long int alterarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo)
{
    if (medicamentosmateriais == NULL)
    {
        return -1; // vazio
    }

    for (int i = 0; i < tammedicamentomaterial; i++)
    {
        if (medicamentosmateriais[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1; // não encontrado
}

void listarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial)
{
    if (medicamentosmateriais == NULL || tammedicamentomaterial == 0)
    {
        printf("Lista de medicamentos e materiais vazia\n");
        return;
    }
    for (int i = 0; i < tammedicamentomaterial; i++)
    {
        printf("Código: %ld\n", medicamentosmateriais[i].codigo);
        printf("Descrição: %s\n", medicamentosmateriais[i].descricao);
        printf("Fabricante: %s\n", medicamentosmateriais[i].fabricante);
        printf("Preço de Custo: %.2f\n", medicamentosmateriais[i].precoCusto);
        printf("Preço de Venda: %.2f\n", medicamentosmateriais[i].precoVenda);
        printf("Quantidade em Estoque: %ld\n", medicamentosmateriais[i].quantidadeEstoque);
        printf("Estoque Mínimo: %ld\n", medicamentosmateriais[i].estoqueMinimo);
        printf("Codigo do fornecedor:%ld\n", medicamentosmateriais[i].codfornecedor);
    }
    return;
}

MedicamentoMaterial *excluimedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int codigo)
{
    int encontrado = -1;
    if (medicamentosmateriais == NULL || *tammedicamentomaterial == 0)
    {
        return medicamentosmateriais;
    }
    for (int i = 0; i < *tammedicamentomaterial; i++)
    {
        if (medicamentosmateriais[i].codigo == codigo)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        return medicamentosmateriais; // no encontrado
    }
    else
    {
        for (int j = encontrado; j < *tammedicamentomaterial - 1; j++)
        {
            medicamentosmateriais[j] = medicamentosmateriais[j + 1];
        }
        (*tammedicamentomaterial)--;

        if (*tammedicamentomaterial == 0)
        {
            free(medicamentosmateriais);
            return NULL;
        }

        MedicamentoMaterial *aux = realloc(medicamentosmateriais, (*tammedicamentomaterial) * sizeof(MedicamentoMaterial));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return medicamentosmateriais;
        }
        else
        {
            medicamentosmateriais = aux;
        }
    }
    return medicamentosmateriais;
}

long int consultamedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo)
{
    if (medicamentosmateriais == NULL || tammedicamentomaterial == 0)
    {
        return -1; // vazio
    }
    for (int i = 0; i < tammedicamentomaterial; i++)
    {
        if (medicamentosmateriais[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}
long int importarmedicamento(MedicamentoMaterial **medicamentosmateriais, char *nome, long int *tammedicamentomaterial, long int *codigoatualmedicamentomaterial)
{
    char linha[1000];
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
        return -1;

    MedicamentoMaterial novo;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "<tabela nome=\"medicamento\">") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</tabela>") == NULL)
            {
                if (strstr(linha, "<codigo>") != NULL)
                    sscanf(linha, "<codigo>%ld</codigo>", &novo.codigo);

                if (strstr(linha, "<descricao>") != NULL)
                    sscanf(linha, "<descricao>%999[^<]</descricao>", novo.descricao);

                if (strstr(linha, "<fabricante>") != NULL)
                    sscanf(linha, "<fabricante>%299[^<]</fabricante>", novo.fabricante);

                if (strstr(linha, "<codfornecedor>") != NULL)
                    sscanf(linha, "<codfornecedor>%ld</codfornecedor>", &novo.codfornecedor);

                if (strstr(linha, "<preco_custo>") != NULL)
                    sscanf(linha, "<preco_custo>%f</preco_custo>", &novo.precoCusto);

                if (strstr(linha, "<preco_venda>") != NULL)
                    sscanf(linha, "<preco_venda>%f</preco_venda>", &novo.precoVenda);

                if (strstr(linha, "<quantidade_estoque>") != NULL)
                    sscanf(linha, "<quantidade_estoque>%ld</quantidade_estoque>", &novo.quantidadeEstoque);

                if (strstr(linha, "<estoque_minimo>") != NULL)
                    sscanf(linha, "<estoque_minimo>%ld</estoque_minimo>", &novo.estoqueMinimo);

                if (strstr(linha, "</registro>") != NULL)
                {
                    *medicamentosmateriais = cadastrarmedicamentomaterial(
                        *medicamentosmateriais,
                        tammedicamentomaterial,
                        codigoatualmedicamentomaterial,
                        &novo);
                }
            }
            break;
        }
    }

    fclose(arquivo);
    return 0;
}

long int exportarmedicamento(MedicamentoMaterial *medicamentosmateriais, char *nome, long int tammedicamentomaterial)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL || medicamentosmateriais == NULL)
        return -1;

    fprintf(arquivo, "<dados>\n");
    fprintf(arquivo, "<!-- Tabela de Medicamentos -->\n");
    fprintf(arquivo, "<tabela nome=\"medicamento\">\n");

    for (long int i = 0; i < tammedicamentomaterial; i++)
    {
        fprintf(arquivo, "<registro>\n");
        fprintf(arquivo, "<codigo>%ld</codigo>\n", medicamentosmateriais[i].codigo);
        fprintf(arquivo, "<descricao>%s</descricao>\n", medicamentosmateriais[i].descricao);
        fprintf(arquivo, "<fabricante>%s</fabricante>\n", medicamentosmateriais[i].fabricante);
        fprintf(arquivo, "<preco_custo>%.2f</preco_custo>\n", medicamentosmateriais[i].precoCusto);
        fprintf(arquivo, "<preco_venda>%.2f</preco_venda>\n", medicamentosmateriais[i].precoVenda);
        fprintf(arquivo, "<quantidade_estoque>%ld</quantidade_estoque>\n", medicamentosmateriais[i].quantidadeEstoque);
        fprintf(arquivo, "<estoque_minimo>%ld</estoque_minimo>\n", medicamentosmateriais[i].estoqueMinimo);
        fprintf(arquivo, "</registro>\n");
    }

    fprintf(arquivo, "</tabela>\n");
    fprintf(arquivo, "</dados>\n");
    fclose(arquivo);

    return 0;
}

long int importarmedicamentotxt(MedicamentoMaterial **medicamentos, long int *tammedicamentos, long int *codigoatual, char *nome)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1;
    }

    char linha[2048];
    MedicamentoMaterial novo;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        char *token = strtok(linha, ";");
        if (token != NULL)
            novo.codigo = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novo.descricao, token, sizeof(novo.descricao));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novo.fabricante, token, sizeof(novo.fabricante));

        token = strtok(NULL, ";");
        if (token != NULL)
            novo.codfornecedor = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            novo.precoCusto = strtof(token, NULL);

        token = strtok(NULL, ";");
        if (token != NULL)
            novo.precoVenda = strtof(token, NULL);

        token = strtok(NULL, ";");
        if (token != NULL)
            novo.quantidadeEstoque = strtol(token, NULL, 10);

        token = strtok(NULL, ";\n");
        if (token != NULL)
            novo.estoqueMinimo = strtol(token, NULL, 10);

        *medicamentos = cadastrarmedicamentomaterial(*medicamentos, tammedicamentos, codigoatual, &novo);
    }

    fclose(arquivo);
    return 0;
}

void exportarmedicamentotxt(MedicamentoMaterial *medicamentos, char *nome, long int tammedicamentos) {
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL) {
        return; // erro ao abrir arquivo
    }

    for (long int i = 0; i < tammedicamentos; i++) {
        fprintf(arquivo, "%ld;%s;%s;%ld;%.2f;%.2f;%ld;%ld\n",
                medicamentos[i].codigo,
                medicamentos[i].descricao,
                medicamentos[i].fabricante,
                medicamentos[i].codfornecedor,
                medicamentos[i].precoCusto,
                medicamentos[i].precoVenda,
                medicamentos[i].quantidadeEstoque,
                medicamentos[i].estoqueMinimo);
    }

    fclose(arquivo);
}

long int importarmedicamentomaterialbin(MedicamentoMaterial **medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual, const char *nomearquivo)
{
    FILE *arquivo = fopen(nomearquivo, "rb");
    if (!arquivo)
    {
        return -1; // erro ao abrir o arquivo
    }

    long int total;
    if (fread(&total, sizeof(long int), 1, arquivo) != 1)
    {
        fclose(arquivo);
        return -2; // erro ao ler o total
    }

    for (long int i = 0; i < total; i++)
    {
        MedicamentoMaterial temp;
        if (fread(&temp, sizeof(MedicamentoMaterial), 1, arquivo) != 1)
        {
            fclose(arquivo);
            return -3; // erro ao ler um registro
        }

        *medicamentosmateriais = cadastrarmedicamentomaterial(*medicamentosmateriais, tammedicamentomaterial, codigoatual, &temp);
    }

    fclose(arquivo);
    return 0; // sucesso
}

void exportarmedicamentomaterialbin(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, const char *nomearquivo)
{
    FILE *arquivo = fopen(nomearquivo, "wb");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo para escrita binária.\n");
        return;
    }

    fwrite(&tammedicamentomaterial, sizeof(long int), 1, arquivo);
    fwrite(medicamentosmateriais, sizeof(MedicamentoMaterial), tammedicamentomaterial, arquivo);

    fclose(arquivo);
}



