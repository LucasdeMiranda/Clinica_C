#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

Procedimento *cadastrarprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int *codigoatual,
                                    Procedimento *novoprocedimento, AmbienteMedico *ambientes, MedicamentoMaterial *medicamentosmateriais,
                                    long int tamambientes, long int tammedicamentomaterial)
{
    int encontraambiente = -1;
    for (int i = 0; i < tamambientes; i++)
    {
        if (novoprocedimento->codambientemedico == ambientes[i].codigo)
        {
            encontraambiente = 0;
            break;
        }
    }
    if (encontraambiente == -1)
    {
        return procedimentos;
    }

    // Verifica se todos os materiais/medicamentos existem
    for (int i = 0; i < novoprocedimento->tamcodmedicamentosmateriais; i++)
    {
        long int codbuscado = novoprocedimento->codmedicamentosemateriais[i].codigo;
        int encontrado = -1;
        for (int j = 0; j < tammedicamentomaterial; j++)
        {
            if (medicamentosmateriais[j].codigo == codbuscado)
            {
                encontrado = 0;
                break;
            }
        }
        if (encontrado == -1)
        {
            return procedimentos;
        }
    }

    Procedimento *novo = realloc(procedimentos, (*tamprocedimento + 1) * sizeof(Procedimento));
    if (novo == NULL)
    {
        // erro ao alocar memoria
        return procedimentos;
    }

    procedimentos = novo;
    novoprocedimento->codigo = *codigoatual;
    procedimentos[*tamprocedimento] = *novoprocedimento;

    // Aloca novo vetor de structs Codmedicamentosmateriais
    procedimentos[*tamprocedimento].codmedicamentosemateriais = malloc(novoprocedimento->tamcodmedicamentosmateriais * sizeof(Codmedicamentosmateriais));

    if (procedimentos[*tamprocedimento].codmedicamentosemateriais == NULL)
    {
        // Erro ao alocar memória para os medicamentos/materiais
        return procedimentos;
    }
    for (int i = 0; i < novoprocedimento->tamcodmedicamentosmateriais; i++)
    {
        procedimentos[*tamprocedimento].codmedicamentosemateriais[i] = novoprocedimento->codmedicamentosemateriais[i];
    }

    (*tamprocedimento)++;
    (*codigoatual)++;
    return procedimentos;
}

void alterarprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo)
{
    if (procedimentos == NULL)
    {
        printf("Lista de procedimentos vazia\n");
        return;
    }

    for (int i = 0; i < tamprocedimento; i++)
    {
        if (procedimentos[i].codigo == codigo)
        {
            printf("Digite a descrição do procedimento:");
            scanf(" %1999[^\n]", procedimentos[i].descricao);

            printf("Digite o custo: ");
            scanf("%f", &procedimentos[i].custo);

            printf("Digite o tempo estimado em minutos: ");
            scanf("%ld", &procedimentos[i].tempoEstimado);

            printf("digite o código do ambiente médico:");
            scanf("%ld", &procedimentos[i].codambientemedico);

            printf("digite quantos materiais e medicamentos seram utilizados:");
            scanf("%ld", &procedimentos[i].tamcodmedicamentosmateriais);

            Codmedicamentosmateriais *novo = realloc(procedimentos[i].codmedicamentosemateriais, procedimentos[i].tamcodmedicamentosmateriais * sizeof(Codmedicamentosmateriais));
            if (novo == NULL)
            {
                printf("erro ao realocar meomoria para o vetor de codigos de materiais e medicamentos\n");
                return;
            }
            else
            {
                procedimentos[i].codmedicamentosemateriais = novo;
                for (int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
                {
                    printf("Digite o código do material %d: ", j + 1);
                    scanf("%ld", &procedimentos[i].codmedicamentosemateriais[j].codigo);
                    printf("Digite a quantidade do material %d: ", j + 1);
                    scanf("%ld", &procedimentos[i].codmedicamentosemateriais[j].qnt);
                }
                printf("Procedimento alterado com sucesso!\n");
                return;
            }
        }
    }
    printf("Código não encontrado.\n");
    return;
}
void listarprocedimento(Procedimento *procedimentos, long int tamprocedimento)
{
    if (procedimentos == NULL || tamprocedimento == 0)
    {
        printf("Lista de procedimentos vazia\n");
        return;
    }

    for (int i = 0; i < tamprocedimento; i++)
    {
        printf("Código do procedimento: %ld\n", procedimentos[i].codigo);
        printf("Descrição: %s\n", procedimentos[i].descricao);
        printf("Custo: R$ %.2f\n", procedimentos[i].custo);
        printf("Tempo estimado: %ld minutos\n", procedimentos[i].tempoEstimado);
        printf("Código do ambiente médico: %ld\n", procedimentos[i].codambientemedico);
        printf("Quantidade de materiais/medicamentos: %ld\n", procedimentos[i].tamcodmedicamentosmateriais);

        if (procedimentos[i].codmedicamentosemateriais != NULL)
        {
            for (int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
            {
                printf("Código do material: %ld - Quantidade usada: %ld\n",
                       procedimentos[i].codmedicamentosemateriais[j].codigo,
                       procedimentos[i].codmedicamentosemateriais[j].qnt);
            }
        }

        printf("\n");
    }

    return;
}

Procedimento *excluirprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int codigo)
{
    int encontrado = -1;
    if (procedimentos == NULL || *tamprocedimento == 0)
    {
        return procedimentos;
    }
    for (int i = 0; i < *tamprocedimento; i++)
    {
        if (procedimentos[i].codigo == codigo)
        {
            encontrado = i;
            free(procedimentos[i].codmedicamentosemateriais);
            procedimentos[i].codmedicamentosemateriais = NULL;
            procedimentos[i].tamcodmedicamentosmateriais = 0;
            break;
        }
    }
    if (encontrado == -1)
    {
        return procedimentos;
    }
    else
    {
        for (int j = encontrado; j < *tamprocedimento - 1; j++)
        {
            procedimentos[j] = procedimentos[j + 1];
        }
        (*tamprocedimento)--;

        if (*tamprocedimento == 0)
        {
            free(procedimentos);
            return NULL;
        }
        Procedimento *aux = realloc(procedimentos, (*tamprocedimento) * sizeof(Procedimento));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return procedimentos;
        }
        else
        {
            procedimentos = aux;
        }
    }
    return procedimentos;
}

long int consultaprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo)
{
    if (procedimentos == NULL || tamprocedimento == 0)
    {
        return -1; // vazio
    }
    for (int i = 0; i < tamprocedimento; i++)
    {
        if (procedimentos[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}

long int exportarprocedimento(Procedimento *procedimentos, char *nome, long int tamprocedimento)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
        return -1;

    if (procedimentos == NULL)
    {
        fclose(arquivo);
        return -1;
    }

    fprintf(arquivo, "<dados>\n");
    fprintf(arquivo, "<!-- Tabela de Procedimentos -->\n");
    fprintf(arquivo, "<tabela nome=\"procedimento\">\n");

    for (long int i = 0; i < tamprocedimento; i++)
    {
        fprintf(arquivo, "<registro>\n");
        fprintf(arquivo, "<codigo>%ld</codigo>\n", procedimentos[i].codigo);
        fprintf(arquivo, "<descricao>%s</descricao>\n", procedimentos[i].descricao);
        fprintf(arquivo, "<custo>%.2f</custo>\n", procedimentos[i].custo);
        fprintf(arquivo, "<tempo_estimado>%ld</tempo_estimado>\n", procedimentos[i].tempoEstimado);
        fprintf(arquivo, "<ambiente_medico>%ld</ambiente_medico>\n", procedimentos[i].codambientemedico);

        fprintf(arquivo, "<medicamentos>\n");
        fprintf(arquivo, "<quantidade>%ld</quantidade>\n", procedimentos[i].tamcodmedicamentosmateriais);

        for (long int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
        {
            fprintf(arquivo, "<codigo quantidade=\"%ld\">%ld</codigo>\n",
                    procedimentos[i].codmedicamentosemateriais[j].qnt,
                    procedimentos[i].codmedicamentosemateriais[j].codigo);
        }

        fprintf(arquivo, "</medicamentos>\n");
        fprintf(arquivo, "</registro>\n");
    }

    fprintf(arquivo, "</tabela>\n");
    fprintf(arquivo, "</dados>\n");

    fclose(arquivo);
    return 0;
}

long int importarprocedimentotxt(Procedimento **procedimentos, long int *tamprocedimento, long int *codigoatual,
                                  AmbienteMedico *ambientes, MedicamentoMaterial *medicamentosmateriais,
                                  long int tamabientes, long int tammedicamento, char *nome)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1;
    }

    char linha[5000]; // linha maior, já que descrição e lista podem ser grandes
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        Procedimento novoprocedimento;

        // Remove o '\n' do final da linha se existir
        linha[strcspn(linha, "\n")] = '\0';

        char *token = strtok(linha, ";");
        if (token == NULL) continue;
        novoprocedimento.codigo = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(novoprocedimento.descricao, token, sizeof(novoprocedimento.descricao));
        novoprocedimento.descricao[sizeof(novoprocedimento.descricao) - 1] = '\0';

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoprocedimento.custo = strtof(token, NULL);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoprocedimento.tempoEstimado = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoprocedimento.codambientemedico = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoprocedimento.tamcodmedicamentosmateriais = strtol(token, NULL, 10);

        // Alocar memória para os materiais
        novoprocedimento.codmedicamentosemateriais = malloc(novoprocedimento.tamcodmedicamentosmateriais * sizeof(Codmedicamentosmateriais));
        if (novoprocedimento.codmedicamentosemateriais == NULL)
        {
            fclose(arquivo);
            return -1; // erro de alocação
        }

        for (int i = 0; i < novoprocedimento.tamcodmedicamentosmateriais; i++)
        {
            token = strtok(NULL, ";");
            if (token == NULL) break;
            novoprocedimento.codmedicamentosemateriais[i].codigo = strtol(token, NULL, 10);

            token = strtok(NULL, ";");
            if (token == NULL) break;
            novoprocedimento.codmedicamentosemateriais[i].qnt = strtol(token, NULL, 10);
        }

        *procedimentos = cadastrarprocedimento(*procedimentos, tamprocedimento, codigoatual,
                                               &novoprocedimento, ambientes, medicamentosmateriais,
                                               tamabientes, tammedicamento);
    }

    fclose(arquivo);
    return 0;
}

void exportarprocedimentotxt(Procedimento *procedimentos, long int tam, const char *caminho)
{
    FILE *arquivo = fopen(caminho, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para exportar procedimentos.\n");
        return;
    }

    for (long int i = 0; i < tam; i++)
    {
        // Escreve os dados principais do procedimento
        fprintf(arquivo, "%ld;%s;%.2f;%ld;%ld;%ld",
                procedimentos[i].codigo,
                procedimentos[i].descricao,
                procedimentos[i].custo,
                procedimentos[i].tempoEstimado,
                procedimentos[i].codambientemedico,
                procedimentos[i].tamcodmedicamentosmateriais);

        for (long int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
        {
            fprintf(arquivo, ";%ld;%ld",
                    procedimentos[i].codmedicamentosemateriais[j].codigo,
                    procedimentos[i].codmedicamentosemateriais[j].qnt);
        }

        fprintf(arquivo, "\n"); 
    }

    fclose(arquivo);
}

long int importarprocedimentobin(Procedimento **procedimentos, long int *tamprocedimento, long int *codigoatual,
                                const char *nomearquivo,
                                AmbienteMedico *ambientes, long int tamambientes,
                                MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial)
{
    FILE *arquivo = fopen(nomearquivo, "rb");
    if (!arquivo)
    {
        return -1; // erro abrir arquivo
    }

    long int total;
    if (fread(&total, sizeof(long int), 1, arquivo) != 1)
    {
        fclose(arquivo);
        return -2; // erro ler total
    }

    for (long int i = 0; i < total; i++)
    {
        Procedimento temp;

        // Ler a parte fixa (todos os campos exceto o vetor)
        // Para evitar ler lixo no ponteiro, zerar antes
        memset(&temp, 0, sizeof(Procedimento));

        // Ler dados fixos
        if (fread(&temp.codigo, sizeof(long int), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(&temp.descricao, sizeof(char), sizeof(temp.descricao), arquivo) != sizeof(temp.descricao)) { fclose(arquivo); return -3; }
        if (fread(&temp.custo, sizeof(float), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(&temp.tempoEstimado, sizeof(long int), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(&temp.codambientemedico, sizeof(long int), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(&temp.tamcodmedicamentosmateriais, sizeof(long int), 1, arquivo) != 1) { fclose(arquivo); return -3; }

        // Alocar vetor dinâmico
        if (temp.tamcodmedicamentosmateriais > 0)
        {
            temp.codmedicamentosemateriais = malloc(temp.tamcodmedicamentosmateriais * sizeof(Codmedicamentosmateriais));
            if (temp.codmedicamentosemateriais == NULL)
            {
                fclose(arquivo);
                return -4; // erro malloc
            }

            // Ler vetor
            if (fread(temp.codmedicamentosemateriais, sizeof(Codmedicamentosmateriais), temp.tamcodmedicamentosmateriais, arquivo) != temp.tamcodmedicamentosmateriais)
            {
                free(temp.codmedicamentosemateriais);
                fclose(arquivo);
                return -5; // erro ler vetor
            }
        }
        else
        {
            temp.codmedicamentosemateriais = NULL;
        }

        // Agora cadastra no vetor principal
        *procedimentos = cadastrarprocedimento(*procedimentos, tamprocedimento, codigoatual, &temp,
                                               ambientes, medicamentosmateriais, tamambientes, tammedicamentomaterial);

        // Depois de cadastrar, o cadastrarprocedimento deve copiar e armazenar os dados internamente,
        // incluindo alocar e copiar o vetor codmedicamentosemateriais
        // Então aqui pode liberar temp.codmedicamentosemateriais para evitar vazamento:
        if (temp.codmedicamentosemateriais != NULL)
            free(temp.codmedicamentosemateriais);
    }

    fclose(arquivo);
    return 0; // sucesso
}

void exportarprocedimentobin(Procedimento *procedimentos, long int tamprocedimento, const char *nomearquivo)
{
    FILE *arquivo = fopen(nomearquivo, "wb");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para escrita binária.\n");
        return;
    }

    fwrite(&tamprocedimento, sizeof(long int), 1, arquivo);

    for (long int i = 0; i < tamprocedimento; i++)
    {
        // Grava campos fixos
        fwrite(&procedimentos[i].codigo, sizeof(long int), 1, arquivo);
        fwrite(procedimentos[i].descricao, sizeof(char), sizeof(procedimentos[i].descricao), arquivo);
        fwrite(&procedimentos[i].custo, sizeof(float), 1, arquivo);
        fwrite(&procedimentos[i].tempoEstimado, sizeof(long int), 1, arquivo);
        fwrite(&procedimentos[i].codambientemedico, sizeof(long int), 1, arquivo);
        fwrite(&procedimentos[i].tamcodmedicamentosmateriais, sizeof(long int), 1, arquivo);

        // Grava vetor dinâmico
        if (procedimentos[i].tamcodmedicamentosmateriais > 0 && procedimentos[i].codmedicamentosemateriais != NULL)
        {
            fwrite(procedimentos[i].codmedicamentosemateriais, sizeof(Codmedicamentosmateriais),
                   procedimentos[i].tamcodmedicamentosmateriais, arquivo);
        }
    }

    fclose(arquivo);
}

long int importarprocedimento(Procedimento **procedimentos,char *nome,long int *tamprocedimento,long int *codigoatual,AmbienteMedico *ambientes,
    MedicamentoMaterial *medicamentosmateriais,
    long int tamambientes,
    long int tammedicamentomaterial)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
        return -1; // erro ao abrir arquivo

    char linha[2048];
    Procedimento novoprocedimento;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "<tabela nome=\"procedimento\">") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</tabela>") == NULL)
            {
                if (strstr(linha, "<registro>") != NULL)
                {
                    novoprocedimento.tamcodmedicamentosmateriais = 0;
                    novoprocedimento.codmedicamentosemateriais = NULL;

                    while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</registro>") == NULL)
                    {
                        if (strstr(linha, "<codigo>") != NULL)
                            sscanf(linha, "<codigo>%ld</codigo>", &novoprocedimento.codigo);

                        if (strstr(linha, "<descricao>") != NULL)
                            sscanf(linha, "<descricao>%1999[^<]</descricao>", novoprocedimento.descricao);

                        if (strstr(linha, "<custo>") != NULL)
                            sscanf(linha, "<custo>%f</custo>", &novoprocedimento.custo);

                        if (strstr(linha, "<tempo_estimado>") != NULL)
                            sscanf(linha, "<tempo_estimado>%ld</tempo_estimado>", &novoprocedimento.tempoEstimado);

                        if (strstr(linha, "<ambiente_medico>") != NULL)
                            sscanf(linha, "<ambiente_medico>%ld</ambiente_medico>", &novoprocedimento.codambientemedico);

                        if (strstr(linha, "<medicamentos>") != NULL)
                        {
                            while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</medicamentos>") == NULL)
                            {
                                if (strstr(linha, "<quantidade>") != NULL)
                                {
                                    sscanf(linha, "<quantidade>%ld</quantidade>", &novoprocedimento.tamcodmedicamentosmateriais);
                                    novoprocedimento.codmedicamentosemateriais = malloc(novoprocedimento.tamcodmedicamentosmateriais * sizeof(Codmedicamentosmateriais));
                                    if (novoprocedimento.codmedicamentosemateriais == NULL)
                                    {
                                        fclose(arquivo);
                                        return -2; // erro de alocação
                                    }
                                }
                                else if (strstr(linha, "<codigo_material") != NULL)
                                {
                                    Codmedicamentosmateriais cm;
                                    sscanf(linha, "<codigo_material quantidade=\"%ld\">%ld</codigo_material>", &cm.qnt, &cm.codigo);

                                    novoprocedimento.codmedicamentosemateriais[
                                        novoprocedimento.tamcodmedicamentosmateriais++] = cm;
                                }
                            }

                            novoprocedimento.tamcodmedicamentosmateriais--;
                        }
                    }

                   
                    *procedimentos = cadastrarprocedimento(*procedimentos, tamprocedimento, codigoatual,
                                                            &novoprocedimento, ambientes, medicamentosmateriais,
                                                            tamambientes, tammedicamentomaterial);

                    // Libera a memória alocada para os medicamentos
                    if (novoprocedimento.codmedicamentosemateriais != NULL)
                    {
                        free(novoprocedimento.codmedicamentosemateriais);
                        novoprocedimento.codmedicamentosemateriais = NULL;
                    }
                }
            }
        }
    }

    fclose(arquivo);
    return 0;
}

