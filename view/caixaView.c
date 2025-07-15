#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menucaixa(float *saldototal, LacamentosRetiradas **lancamentosretiradas, Receber **receber,
               long int *tamlancamentosretiradas, long int *tamreceber, long int *codigoatualreceber,
               Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos,
               long int tamprocedimento, Entradaestoque *entradaestoque, long int tamentradaestoque)
{
    int op, op2,resultado;
    char data[100];
    long int aux, auxreceber,codigofornecedor,codigo;
    do
    {
        printf("1:Receber pelo procedimento realizado:\n");
        printf("2:Registrar um pagamento a receber:\n");
        printf("3:Pagar conta aos fornecedores:\n");
        printf("4:Consultar lançamentos e retiradas:\n");
        printf("5:Sair:\n");
        scanf("%d", &op);
        if (op < 1 || op > 5)
        {
            printf("opção invalida\n");
        }
        else if (op == 1)
        {
            printf("1:A vista:\n");
            printf("2:Pelo plano:\n");
            scanf("%d", &op2);
            if (op2 < 1 || op > 2)
            {
                printf("opção invalida\n");
            }
            else if (op2 == 1)
            {
                LacamentosRetiradas novolancamentoretirada;
                aux = *tamlancamentosretiradas;
                printf("Digite a data:");
                scanf(" %99[^\n]", novolancamentoretirada.data);
                printf("Digite o codigo do agendamento a ser pago:");
                scanf("%ld", &novolancamentoretirada.codigoagendamento);
                novolancamentoretirada.tipo = 0;
                *lancamentosretiradas = cadastrarlancamentoretirada(*lancamentosretiradas, tamlancamentosretiradas,
                                                                    &novolancamentoretirada, agendamentos, tamagendamento, procedimentos, tamprocedimento,saldototal);
                if (*tamlancamentosretiradas > aux)
                {
                    printf("Lançamento cadastrado com sucesso\n");
                  
                }
                else
                {
                    printf("Erro ao cadastrar lancamento\n");
                }
            }
            else if (op2 == 2)
            {
                auxreceber=*tamreceber;
              printf("digite o codigo:");
              scanf("%ld",&codigo);
            *receber = excluirreceber(*receber, tamreceber, codigo, lancamentosretiradas, tamlancamentosretiradas, saldototal);

              if(*tamreceber<auxreceber){
                printf("conta a receber excluida com sucesso\n");
              }
              else{
                printf("erro ao excluir conta a receber\n");
              }
             
            }
        }
        else if (op == 2)
        {

            Receber novoreceber;
            auxreceber = *tamreceber;
            printf("digite a data:");
            scanf(" %99[^\n]", novoreceber.data);
            printf("digite o código do agendamento:");
            scanf("%ld",&novoreceber.codigoagendamento);
            *receber = cadastrarreceber(*receber, tamreceber,codigoatualreceber,
                &novoreceber,agendamentos,tamagendamento,procedimentos,tamprocedimento);
            if (*tamreceber > auxreceber)
            {
                printf("Sucesso ao cadastrar pagamento a receber\n");
            }
            else
            {
                printf("Erro ao cadastrar pagamento a receber\n");
            }
        }
        else if(op==3){
            printf("Digite o codigo do fornecedor");
            scanf("%ld",&codigofornecedor);
            printf("digite a data");
            scanf(" %99[^\n]", data);
            resultado=efetuarpagamento(codigofornecedor,saldototal,data,entradaestoque,tamentradaestoque,lancamentosretiradas,tamlancamentosretiradas);

            if(resultado==-1){
                printf("erro ao efetuar pagamento aos fornecedores\n");
            }
            else{
                printf("pagamento efetuado com sucesso\n");
                printf("saldo atual:%f",*saldototal);
            }

        }
        else if(op==4){
            imprimirLancamentosRetiradas(*lancamentosretiradas,*tamlancamentosretiradas);
        }

    } while (op != 5);
}