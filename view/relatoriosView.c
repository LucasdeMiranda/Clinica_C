#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menurelatorios(Agendamento *agendamentos, long int tamagendamento, AmbienteMedico *ambientes, long int tamambientes,
                    LacamentosRetiradas *lancamentosretiradas, long int tamlacamentosretiradas, Entradaestoque *entradaestoque, long int tamentradaestoque,
                    Fornecedor *fornecedores, long int tamfornecedores, MedicamentoMaterial *medicamentosmariais, long int tammedicamentomaterial,
                    Paciente *pacientes, long int tampaciente, Procedimento *procedimentos, long int tamprocedimento,
                    Profissional *profissionais, long int tamprofissional, Receber *receber, long int tamreceber)
{
    int op, opcsv, opfiltro, op1;
    char data1[100], data2[100],cidade[200],estado[10];
    long int codpaciente, codfornecedor, resultado,codprocedimento,codprofissional;

    printf("1:Imprimir na tela\n 2:Csv\n3:Sair\n");
    scanf("%d", &opcsv);

    do
    {
        op = 0;
        printf("1:Relatorio de contas a pagar:\n");
        printf("2:Relatorio de contas a receber:\n");
        printf("3:Relatorio de estoque:\n");
        printf("4:Relatorio de pacientes\n");
        printf("5:Relatorio de ambientes\n");
        printf("6:Relatorio de fornecedores\n");
        printf("7:Relatorio de Medicamentos e materiais\n");
        printf("8: Relatorio de  \n");
        printf("9:Relatorio de profissionais\n");
        printf("10:Relatorio de procedimentos realizados\n");
        printf("11:Sair\n");
        scanf("%d", &op);
        if (op < 1 || op > 11)
        {
            printf("opção invalida\n");
        }
        else if (op == 1)
        {
            printf("1:Forncedor\n");
            printf("2:Intervalo de datas\n");
            printf("3:Nenhum\n");
            scanf("%d", &opfiltro);
            if (opfiltro < 1 || opfiltro > 3)
            {
                printf("opção invalida\n");
            }
            else if (opfiltro == 1)
            {
                printf("Digite o codigo do fornecedor:");
                scanf("%ld", &codfornecedor);
                relatoriopagarfornecedor(lancamentosretiradas, tamlacamentosretiradas,
                                         opcsv, codfornecedor, entradaestoque, tamentradaestoque);
            }
            else if (opfiltro == 2)
            {

                printf("digite a data de incio:");
                scanf(" %99[^\n]", data1);
                printf("digite a data de fim:");
                scanf(" %99[^\n]", data2);

                relatoriopagardata(lancamentosretiradas, tamlacamentosretiradas,
                                   entradaestoque, tamentradaestoque, data1, data2, opcsv);
            }
            else if (opfiltro == 3)
            {
                relatoriopagarsemfiltro(lancamentosretiradas, tamlacamentosretiradas,
                                        entradaestoque, tamentradaestoque, opcsv);
            }
        }
        else if (op == 2)
        {

            printf("1:Paciente\n");
            printf("2:Intervalo de datas:\n");
            printf("3:Nenhum\n");
            scanf("%d", &opfiltro);
            if (opfiltro < 1 || opfiltro > 3)
            {
                printf("opção invalida\n");
            }
            else if (opfiltro == 1)
            {
                printf("digite o codigo:");
                scanf("%ld", &codpaciente);
                relatoriopacientecaixa(receber, tamreceber, pacientes, tampaciente, agendamentos, tamagendamento, codpaciente, opcsv);
            }
            else if (opfiltro == 2)
            {
                printf("digite a data de incio:");
                scanf(" %99[^\n]", data1);
                printf("digite a data de fim:");
                scanf(" %99[^\n]", data2);

                relatorioreceberdata(receber, tamreceber, data1, data2, opcsv);
            }
            else if (opfiltro == 3)
            {
                relatoriocaixasemfiltro(receber, tamreceber, opcsv);
            }
        }
        else if (op == 3)
        {
            printf("1:Procedimento\n");
            printf("2:Paciente\n");
            printf("3:Intervalo de datas\n");
            printf("4:Profissional\n");
            printf("5:Materiais em estoque minimo\n");
            printf("6:Nenhum\n");
            scanf("%d", &opfiltro);
            if (opfiltro < 1 || opfiltro > 6)
            {
                printf("opção invalida\n");
            }
            else if(opfiltro==1){
               printf("Digite o codigo do procedimento:");
               scanf("%ld",&codprocedimento);
               relatorioestoqueprocedimento(medicamentosmariais,tammedicamentomaterial,procedimentos,tamprocedimento,codprocedimento,opcsv);
            }
            else if(opfiltro==2){
                printf("Digite o codigo do paciente:");
                scanf("%ld",&codpaciente);
                relatorioestoquepaciente(medicamentosmariais,tammedicamentomaterial,agendamentos,
                    tamagendamento,procedimentos,tamprocedimento,codpaciente,opcsv);
            }
            else if(opfiltro==3){

                printf("digite a data de incio:");
                scanf(" %99[^\n]", data1);
                printf("digite a data de fim:");
                scanf(" %99[^\n]", data2);
                relatoriosestoquedata(entradaestoque,tamentradaestoque,medicamentosmariais,tammedicamentomaterial,data1,data2,opcsv);

            }
            else if(opfiltro==4){
                printf("digite o codigo do profissional:");
                scanf("%ld",&codprofissional);
                relatorioestoqueprofissional(medicamentosmariais,tammedicamentomaterial,agendamentos,
                    tamagendamento,procedimentos,tamprocedimento,codprofissional,opcsv);
            }
            else if(opfiltro==5){
                relatorioestoqueminimo(medicamentosmariais,tammedicamentomaterial,opcsv);
            }
            else if(opfiltro==6){
                relatorioestoquesemfiltro(medicamentosmariais,tammedicamentomaterial,opcsv);
            }
        }
        else if(op==4){
            //filtro usado de cidade pacientes que moram na mesma cidade
            printf("1:Cidade\n");
            printf("2:Nenhum\n");
            scanf("%d", &opfiltro);
            if (opfiltro < 1 || opfiltro > 2)
            {
                printf("opção invalida\n");
            } 
            else if(opfiltro==1){
                 printf("digite a cidade:");
                scanf(" %199[^\n]", cidade);

                relatoriobasicopacientecidade(pacientes,tampaciente,cidade,opcsv);
            }
            else if(opfiltro==2){
            relatoriobasicopacientesemfiltro(pacientes,tampaciente,opcsv);
            }
        }
        else if(op==5){

        }
        else if(op==6){
            //filtro de estado
            printf("1:Estado\n");
            printf("2:Nenhum\n");
            scanf("%d",opfiltro);
              if (opfiltro < 1 || opfiltro > 2)
            {
                printf("opção invalida\n");
            } 
            else if(opfiltro==1){
                printf("digite o estado:");
                scanf(" %9[^\n]",estado);
            }
        }
        else if(op==10){
            printf("1:Procedimento\n");
            printf("2:Paciente\n");
            printf("3:Intervalo de datas\n");
            printf("4:Profissional\n");
            printf("5:Nenhum\n");
            scanf("%d",&opfiltro);
             if (opfiltro < 1 || opfiltro > 5)
            {
                printf("opção invalida\n");
            } 
            else if(opfiltro==1){
                printf("Digite o codigo do procedimento:");
                scanf("%ld",&codprocedimento);
                relatorioprocedimentoprocedimento(agendamentos,tamagendamento,procedimentos,tamprocedimento,codprocedimento,opcsv);
            }
            else if(opfiltro==2){
                printf("digite o codigo do paciente:");
                scanf("%ld",&codpaciente);
                relatorioprocedimentopaciente(agendamentos,tamagendamento,procedimentos,tamprocedimento,pacientes,tampaciente,codpaciente,opcsv);
            }
            else if(opfiltro==3){
                printf("digite a data de incio:");
                scanf(" %99[^\n]", data1);
                printf("digite a data de fim:");
                scanf(" %99[^\n]", data2);
                relatorioprocedimentodata(agendamentos,tamagendamento,procedimentos,tamprocedimento,data1,data2,opcsv);

            }
            else if(opfiltro==4){
                printf("digite o codigo do profissional:");
                scanf("%ld",&codprofissional);
                relatorioprocedimentoprofissional(agendamentos,tamagendamento,procedimentos,tamprocedimento,profissionais,tamprofissional,codprofissional,opcsv);
            }
            else if(opfiltro==5){
                relatorioprocedimentosemfiltro(agendamentos,tamagendamento,procedimentos,tamprocedimento,opcsv);
            }
        }
         

    } while (op != 11);
}
