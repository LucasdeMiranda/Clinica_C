#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

LacamentosRetiradas *cadastrarlancamentoretirada(LacamentosRetiradas *lacamentosretiradas,
                                                 long int *tamlacamentosretiradas,
                                                 LacamentosRetiradas *novolacamentoretirada, Agendamento *agendamentos,
                                                 long int tamagendamento, Procedimento *procedimentos,
                                                 long int tamprocedimento, float *saldototal, Entradaestoque *entradaestoque, long int tamentradaestoque)
{
    long int posicao = -1;
    if (novolacamentoretirada->codigoagendamento == -1)
    { // se agendamento =1 significa que vamos registrar um  pagar e não receber
        for (long int i = 0; i < *tamlacamentosretiradas; i++)
        {
            if (novolacamentoretirada->codigoentradaestoque == lacamentosretiradas[i].codigoentradaestoque)
            {
                return lacamentosretiradas; // ja pagou por essa entrada de materiais portanto ja pagou para o fornecedo
            }
        }
    }
    if (novolacamentoretirada->codigoentradaestoque == -1)
    {
        for (long int i = 0; i < *tamlacamentosretiradas; i++)
        {
            if (novolacamentoretirada->codigoagendamento == lacamentosretiradas[i].codigoagendamento)
            {
                return lacamentosretiradas; // já foi pago por esse agendamento
            }
        }
    }

    if (novolacamentoretirada->tipo == 0)
    {
        // verifica se o que sera pago existe agendamento exixte
        for (long int i = 0; i < tamagendamento; i++)
        {
            if (novolacamentoretirada->codigoagendamento == agendamentos[i].codigo)
            {
                posicao = i;
                break;
            }
        }
        if (posicao == -1)
        {
            // não existia o agendamento
            return lacamentosretiradas;
        }
        else
        {
            for (long int i = 0; i < tamprocedimento; i++)
            {
                if (agendamentos[posicao].codprocedimento == procedimentos[i].codigo)
                {
                    novolacamentoretirada->valor = procedimentos[i].custo;
                }
            }
        }
    }

    if (novolacamentoretirada->tipo == 1 || novolacamentoretirada->tipo == 2 || posicao != -1)
    {
        LacamentosRetiradas *novo = realloc(lacamentosretiradas, (*tamlacamentosretiradas + 1) * sizeof(LacamentosRetiradas));
        if (novo == NULL)
        {
            return lacamentosretiradas;
        }

        lacamentosretiradas = novo;
        lacamentosretiradas[*tamlacamentosretiradas] = *novolacamentoretirada;
        if (novolacamentoretirada->tipo == 2 || posicao != -1)
        {
            *saldototal += novolacamentoretirada->valor;
        }
        (*tamlacamentosretiradas)++;
        return lacamentosretiradas;
    }

    return lacamentosretiradas;
}
Receber *cadastrarreceber(Receber *receber, long int *tamreceber, long int *codigoatual,
                          Receber *novoreceber, Agendamento *agendamentos, long int tamagendamento,
                          Procedimento *procedimentos, long int tamprocedimento)
{
    long int posicao = -1;

    // Verifica se o agendamento já está registrado em receber
    for (long int i = 0; i < *tamreceber; i++)
    {
        if (receber[i].codigoagendamento == novoreceber->codigoagendamento)
        {
            // ja fo cadastrado
            return receber;
        }
    }

    // Verifica se o agendamento existe
    for (long int i = 0; i < tamagendamento; i++)
    {
        if (novoreceber->codigoagendamento == agendamentos[i].codigo)
        {
            posicao = i;
            break;
        }
    }

    if (posicao == -1)
    {

        return receber;
    }
    else
    {
        // Busca o custo do procedimento vinculado ao agendamento
        for (long int i = 0; i < tamprocedimento; i++)
        {
            if (agendamentos[posicao].codprocedimento == procedimentos[i].codigo)
            {
                novoreceber->valor = procedimentos[i].custo;
                break;
            }
        }
    }
    Receber *novo = realloc(receber, (*tamreceber + 1) * sizeof(Receber));
    if (novo == NULL)
    {
        return receber;
    }

    receber = novo;
    novoreceber->codigo = *codigoatual;
    receber[*tamreceber] = *novoreceber;

    (*tamreceber)++;
    (*codigoatual)++;

    return receber;
}

long int efetuarpagamento(long int codigoentradaestoque, float *saldototal, char *data, Entradaestoque *entradaestoque, long int tamentradaestoque, LacamentosRetiradas **lancamentosentradas, long int *tamlancamentosentradas)
{
    int resultado = -1;
    for (long int i = 0; i < tamentradaestoque; i++)
    {
        if (codigoentradaestoque == entradaestoque[i].codigo)
        {
            resultado = i;
            break;
        }
    }
    if (resultado == -1)
    {
        return -1; // não existe essa entrada de estoque com o código do fornecedor informado
    }
    else
    {
        LacamentosRetiradas novolancamentoretirada;
        strcpy(novolancamentoretirada.data, data);
        novolancamentoretirada.tipo = 1;
        novolancamentoretirada.codigoentradaestoque = codigoentradaestoque;
        novolancamentoretirada.codigoagendamento = -1;
        // esse campo total de tudo ja registra o total dos produtos pela quantidade e o preço de custo + frete + imposto
        novolancamentoretirada.valor = entradaestoque[resultado].totaldetudo;

        // chama a função pra cadastrar
        *lancamentosentradas = cadastrarlancamentoretirada(
            *lancamentosentradas,
            tamlancamentosentradas,
            &novolancamentoretirada,
            NULL, // sem agendamentos nesse caso
            0,
            NULL,
            0, saldototal, entradaestoque, tamentradaestoque);

        *saldototal -= novolancamentoretirada.valor;

        return 0; // sucesso
    }
}

void imprimirLancamentosRetiradas(LacamentosRetiradas *lancamentos, long int tamlancamentosretiradas)
{
    if (tamlancamentosretiradas == 0)
    {
        printf("Nenhum lançamento ou retirada foi registrado.\n");
        return;
    }

    printf("\n==== Lançamentos e Retiradas ====\n");
    for (long int i = 0; i < tamlancamentosretiradas; i++)
    {
        if (lancamentos[i].tipo == 0 || lancamentos[i].tipo == 2)
        {
            printf("\nLançamento\n");
        }
        else if (lancamentos[i].tipo == 1)
        {
            printf("\nRetirada\n");
        }

        printf("Data: %s\n", lancamentos[i].data);
        printf("Valor: R$ %.2f\n", lancamentos[i].valor);
    }
    printf("===============================\n");
}
// como receber é um vetor de contas a receber quando da baixa tem que tira ele do vetor
Receber *excluirreceber(Receber *receber, long int *tamreceber, long int codigo,
                        LacamentosRetiradas **lancamentosentradas, long int *tamlancamentosentradas,
                        float *saldototal, Entradaestoque *entradaestoque, long int tamentradaestoque)
{
    long int encontrado = -1;
    for (long int i = 0; i < *tamreceber; i++)
    {
        if (codigo == receber[i].codigo)
        {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1)
    {
        // Não existe
        return receber;
    }
    else
    {
        LacamentosRetiradas novolancamentoretirada;
        strcpy(novolancamentoretirada.data, receber[encontrado].data);
        novolancamentoretirada.tipo = 2;
        novolancamentoretirada.valor = receber[encontrado].valor;
        novolancamentoretirada.codigoagendamento = receber[encontrado].codigoagendamento;
        novolancamentoretirada.codigoentradaestoque = -1; // esse -1 um pra simboloizar que não é uma conta pra pagar a um fornecedor ou seja não é de entrada estoque

        // Cadastrar o lançamento
        *lancamentosentradas = cadastrarlancamentoretirada(
            *lancamentosentradas,
            tamlancamentosentradas,
            &novolancamentoretirada,
            NULL, 0,
            NULL, 0,
            saldototal, entradaestoque, tamentradaestoque);
        for (long int j = encontrado; j < (*tamreceber) - 1; j++)
        {
            receber[j] = receber[j + 1];
        }
        (*tamreceber)--;
        if (*tamreceber == 0)
        {
            free(receber);
            return NULL;
        }
        Receber *aux = realloc(receber, (*tamreceber) * sizeof(Receber));
        if (aux == NULL)
        {
            return receber;
        }
        else
        {
            receber = aux;
        }

        return receber;
    }
}

long int importarrecebertxt(Receber **receber, long int *tamreceber, long int *codigoatual, char *nome,
                            Agendamento *agendamentos, long int tamagendamento,
                            Procedimento *procedimentos, long int tamprocedimento)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1; // erro ao abrir arquivo
    }

    char linha[1024];
    Receber novoreceber;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        char *token = strtok(linha, ";");
        if (token != NULL)
            novoreceber.codigo = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            novoreceber.codigoagendamento = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            novoreceber.valor = strtof(token, NULL);

        token = strtok(NULL, ";\n");
        if (token != NULL)
            strncpy(novoreceber.data, token, sizeof(novoreceber.data));

        *receber = cadastrarreceber(*receber, tamreceber, codigoatual, &novoreceber,
                                    agendamentos, tamagendamento, procedimentos, tamprocedimento);
    }

    fclose(arquivo);
    return 0;
}

void exportarrecebertxt(Receber *receber, char *nome, long int tamreceber)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
    {
        return; // erro ao abrir arquivo
    }

    for (long int i = 0; i < tamreceber; i++)
    {
        fprintf(arquivo, "%ld;%ld;%.2f;%s\n",
                receber[i].codigoagendamento,
                receber[i].codigo,
                receber[i].valor,
                receber[i].data);
    }

    fclose(arquivo);
}

long int importarlancamentosretiradastxt(LacamentosRetiradas **lacamentosretiradas, long int *tamlacamentosretiradas,
                                         Agendamento *agendamentos, long int tamagendamento,
                                         Procedimento *procedimentos, long int tamprocedimento,
                                         float *saldototal,
                                         Entradaestoque *entradaestoque, long int tamentradaestoque,
                                         char *nome)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1; // erro ao abrir arquivo
    }

    char linha[1024];
    LacamentosRetiradas novolancamento;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        char *token = strtok(linha, ";");
        if (token != NULL)
            strncpy(novolancamento.data, token, sizeof(novolancamento.data));
        novolancamento.data[sizeof(novolancamento.data) - 1] = '\0';

        token = strtok(NULL, ";");
        if (token != NULL)
            novolancamento.tipo = atoi(token);

        token = strtok(NULL, ";");
        if (token != NULL)
            novolancamento.valor = strtof(token, NULL);

        token = strtok(NULL, ";");
        if (token != NULL)
            novolancamento.codigoagendamento = strtol(token, NULL, 10);

        token = strtok(NULL, ";\n");
        if (token != NULL)
            novolancamento.codigoentradaestoque = strtol(token, NULL, 10);

        *lacamentosretiradas = cadastrarlancamentoretirada(*lacamentosretiradas, tamlacamentosretiradas,
                                                           &novolancamento, agendamentos, tamagendamento,
                                                           procedimentos, tamprocedimento, saldototal,
                                                           entradaestoque, tamentradaestoque);
    }

    fclose(arquivo);
    return 0;
}

void exportarlancamentosretiradastxt(LacamentosRetiradas *lacamentosretiradas, long int tamlacamentosretiradas, const char *nome)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo para exportar lançamentos e retiradas.\n");
        return;
    }

    for (long int i = 0; i < tamlacamentosretiradas; i++)
    {
        fprintf(arquivo, "%s;%d;%.2f;%ld;%ld\n",
                lacamentosretiradas[i].data,
                lacamentosretiradas[i].tipo,
                lacamentosretiradas[i].valor,
                lacamentosretiradas[i].codigoagendamento,
                lacamentosretiradas[i].codigoentradaestoque);
    }

    fclose(arquivo);
}

long int importarreceberbin(Receber **receber, long int *tamreceber, long int *codigoatual,
                            const char *nomearquivo,
                            Agendamento *agendamentos, long int tamagendamento,
                            Procedimento *procedimentos, long int tamprocedimento)
{
    FILE *arquivo = fopen(nomearquivo, "rb");
    if (!arquivo)
    {
        return -1; // erro ao abrir arquivo
    }

    long int total;
    if (fread(&total, sizeof(long int), 1, arquivo) != 1)
    {
        fclose(arquivo);
        return -2; // erro ao ler total
    }

    for (long int i = 0; i < total; i++)
    {
        Receber temp;
        if (fread(&temp, sizeof(Receber), 1, arquivo) != 1)
        {
            fclose(arquivo);
            return -3; // erro na leitura do registro
        }

        *receber = cadastrarreceber(*receber, tamreceber, codigoatual, &temp,
                                    agendamentos, tamagendamento,
                                    procedimentos, tamprocedimento);
    }

    fclose(arquivo);
    return 0; // sucesso
}

void exportarreceberbin(Receber *receber, long int tamreceber, const char *nomearquivo)
{
    FILE *arquivo = fopen(nomearquivo, "wb");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para escrita binária.\n");
        return;
    }

    // Primeiro grava o tamanho do vetor
    fwrite(&tamreceber, sizeof(long int), 1, arquivo);
    // Depois grava o vetor inteiro de Receber
    fwrite(receber, sizeof(Receber), tamreceber, arquivo);

    fclose(arquivo);
}

long int importarlancamentoretiradabin(
    LacamentosRetiradas **lancamentos, long int *tam,
    Agendamento *agendamentos, long int tamagendamento,
    Procedimento *procedimentos, long int tamprocedimento,
    float *saldototal,
    Entradaestoque *entradaestoque, long int tamentradaestoque,char *nomedoarquivo)
{
    FILE *arquivo = fopen(nomedoarquivo, "rb");
    if (!arquivo)
        return -1;

    long int total = 0;
    if (fread(&total, sizeof(long int), 1, arquivo) != 1)
    {
        fclose(arquivo);
        return -2;
    }

    for (long int i = 0; i < total; i++)
    {
        LacamentosRetiradas temp;

        if (fread(&temp, sizeof(LacamentosRetiradas), 1, arquivo) != 1)
        {
            fclose(arquivo);
            return -3;
        }

        *lancamentos = cadastrarlancamentoretirada(*lancamentos, tam, &temp,
                                                   agendamentos, tamagendamento,
                                                   procedimentos, tamprocedimento,
                                                   saldototal, entradaestoque, tamentradaestoque);
    }

    fclose(arquivo);
    return 0;
}

void exportarlancamentoretiradabin(LacamentosRetiradas *lancamentos, long int tam, const char *nomearquivo)
{
    FILE *arquivo = fopen(nomearquivo, "wb");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para escrita binária\n");
        return;
    }

    fwrite(&tam, sizeof(long int), 1, arquivo);
    fwrite(lancamentos, sizeof(LacamentosRetiradas), tam, arquivo);

    fclose(arquivo);
}

