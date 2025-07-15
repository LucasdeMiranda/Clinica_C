#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

LacamentosRetiradas *cadastrarlancamentoretirada(LacamentosRetiradas *lacamentosretiradas,
                                                 long int *tamlacamentosretiradas,
                                                 LacamentosRetiradas *novolacamentoretirada, Agendamento *agendamentos,
                                                 long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento,float *saldototal)
{
    long int posicao = -1;

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

    return lacamentosretiradas; // garante retorno mesmo se nenhum if for executado
}
 Receber *cadastrarreceber(Receber *receber, long int *tamreceber, long int *codigoatual,
                           Receber *novoreceber, Agendamento *agendamentos, long int tamagendamento,
                           Procedimento *procedimentos, long int tamprocedimento)
{
    long int posicao = -1;

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



long int efetuarpagamento(long int codigofornecedor, float *saldototal, char *data, Entradaestoque *entradaestoque, long int tamentradaestoque, LacamentosRetiradas **lancamentosentradas, long int *tamlancamentosentradas)
{
    int resultado = -1;
    for (long int i = 0; i < tamentradaestoque; i++)
    {
        if (codigofornecedor == entradaestoque[i].codfornecedor)
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

        // Calcular total dos materiais recebidos
        float totalmateriais = 0;
        for (long int j = 0; j < entradaestoque[resultado].tammedicamentosmateriaisrecebidos; j++)
        {
            totalmateriais += entradaestoque[resultado].codmedicamentosmateriaisrecebidos[j].qnt *
                              entradaestoque[resultado].codmedicamentosmateriaisrecebidos[j].precocustounid;
        }

        // Soma frete + imposto + total dos materiais
        novolancamentoretirada.valor = entradaestoque[resultado].frete +
                                       entradaestoque[resultado].imposto +
                                       totalmateriais;

        // chama a função pra cadastrar
        *lancamentosentradas = cadastrarlancamentoretirada(
            *lancamentosentradas,
            tamlancamentosentradas,
            &novolancamentoretirada,
            NULL, // sem agendamentos nesse caso
            0,
            NULL,
            0,saldototal);

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
                        LacamentosRetiradas **lancamentosentradas, long int *tamlancamentosentradas, float *saldototal)
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

        // Cadastrar o lançamento
        *lancamentosentradas = cadastrarlancamentoretirada(
            *lancamentosentradas,
            tamlancamentosentradas,
            &novolancamentoretirada,
            NULL, 0,
            NULL, 0,
            saldototal
        );
        for (long int j = encontrado; j < (*tamreceber) - 1; j++)
        {
            receber[j] = receber[j + 1];
        }
        (*tamreceber)--;
        if(*tamreceber==0){
            free(receber);
            return NULL;
        }
        Receber *aux = realloc(receber, (*tamreceber) * sizeof(Receber));
        if (aux==NULL) 
        {
              printf("erro ao realocar memoria\n");
              return receber;
        }
        else{
            receber=aux;
        }

        return receber;
    }
}
