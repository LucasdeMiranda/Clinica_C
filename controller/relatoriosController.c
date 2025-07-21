#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "biblioteca.h"

#include <stdio.h>

void relatoriopacientecaixa(Receber *receber, long int tamreceber, Paciente *pacientes, long int tampacientes, Agendamento *agendamentos,
                            long int tamagendamentos, long int paciente, int opcsv)
{

    if (receber == NULL || pacientes == NULL || agendamentos == NULL)
    {
        printf("ERRO\n");
        return;
    }
    else
    {
        if (opcsv == 1)
        {
            for (long int i = 0; i < tamreceber; i++)
            {
                for (long int j = 0; j < tamagendamentos; j++)
                {
                    if (receber[i].codigoagendamento == agendamentos[j].codigo)
                    {
                        if (paciente == agendamentos[j].codpaciente)
                        {
                            printf("Paciente codigo: %ld\n", agendamentos[j].codpaciente);
                            printf("Valor a receber: %.2f\n", receber[i].valor);
                        }
                    }
                }
            }
        }
        if (opcsv == 2)
        {
            FILE *arquivo = fopen("relatorio.csv", "w");
            if (arquivo == NULL)
            {
                printf("Erro ao abrir o arquivo relatorio.csv\n");
                return;
            }

            fprintf(arquivo, "CodigoPaciente,ValorReceber\n");

            for (long int i = 0; i < tamreceber; i++)
            {
                for (long int j = 0; j < tamagendamentos; j++)
                {
                    if (receber[i].codigoagendamento == agendamentos[j].codigo)
                    {
                        if (paciente == agendamentos[j].codpaciente)
                        {
                            fprintf(arquivo, "%ld,%.2f\n", agendamentos[j].codpaciente, receber[i].valor);
                        }
                    }
                }
            }

            fclose(arquivo);
            printf("Relatório gerado com sucesso em relatorio.csv\n");
        }
    }
}

void relatoriocaixasemfiltro(Receber *receber, long int tamreceber, int opcsv)
{
    if (receber == NULL)
    {
        printf("ERRO\n");
    }
    else
    {
        if (opcsv == 1)
        {
            for (long int i = 0; i < tamreceber; i++)
            {
                printf("Data:%s\n", receber[i].data);
                printf("Valor:%2.f\n", receber[i].valor);
            }
        }
        else if (opcsv == 2)
        {
            FILE *arquivo = fopen("relatorio.csv", "w");
            if (arquivo == NULL)
            {
                printf("Erro ao abrir o arquivo relatorio.csv\n");
                return;
            }

            fprintf(arquivo, "Data,ValorReceber\n");

            for (long int i = 0; i < tamreceber; i++)
            {
                fprintf(arquivo, "%s,%.2f\n", receber[i].data, receber[i].valor);
            }

            fclose(arquivo);
            printf("Relatório gerado com sucesso em relatorio.csv\n");
        }
    }
}

int converterdata(char *data)
{
    int d, m, a;
    sscanf(data, "%2d/%2d/%4d", &d, &m, &a);
    return a * 10000 + m * 100 + d; // formato: aaaammdd
}

void relatorioreceberdata(Receber *receber, long int tamreceber, char *data1, char *data2, int opcsv)
{
    if (receber == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    int inicio = converterdata(data1);
    int fim = converterdata(data2);

    if (opcsv == 1)
    {
        printf("Relatório de contas a receber entre %s e %s:\n", data1, data2);
        for (long int i = 0; i < tamreceber; i++)
        {
            int atual = converterdata(receber[i].data);

            if (atual >= inicio && atual <= fim)
            {
                printf("Data: %s\n", receber[i].data);
                printf("Valor: %.2f\n", receber[i].valor);
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Data,Valor\n");

        for (long int i = 0; i < tamreceber; i++)
        {
            int atual = converterdata(receber[i].data);

            if (atual >= inicio && atual <= fim)
            {
                fprintf(arquivo, "%s,%.2f\n", receber[i].data, receber[i].valor);
            }
        }

        fclose(arquivo);
        printf("Relatório salvo com sucesso em relatorio.csv\n");
    }
}

void relatoriopagarfornecedor(LacamentosRetiradas *lancamentosretiradas, long int tamlacamentoretirada, int opcsv, long int codfornecedor,
                              Entradaestoque *entradaestoque, long int tamentradaestoque)
{
    if (entradaestoque == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int j = 0; j < tamentradaestoque; j++)
        {
            if (entradaestoque[j].codfornecedor == codfornecedor)
            {
                bool pago = false;
                for (long int i = 0; i < tamlacamentoretirada; i++)
                {
                    if (lancamentosretiradas[i].codigoentradaestoque == entradaestoque[j].codigo)
                    {
                        pago = true;
                        break;
                    }
                }
                if (!pago)
                {
                    printf("Nome: %s\n", entradaestoque[j].fornecedor);
                    printf("Valor a pagar: %.2f\n", entradaestoque[j].totaldetudo);
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Fornecedor,Valor Pagar\n");
        for (long int j = 0; j < tamentradaestoque; j++)
        {
            if (entradaestoque[j].codfornecedor == codfornecedor)
            {
                bool pago = false;
                for (long int i = 0; i < tamlacamentoretirada; i++)
                {
                    if (lancamentosretiradas[i].codigoentradaestoque == entradaestoque[j].codigo)
                    {
                        pago = true;
                        break;
                    }
                }
                if (!pago)
                {
                    fprintf(arquivo, "%s,%.2f\n", entradaestoque[j].fornecedor, entradaestoque[j].totaldetudo);
                }
            }
        }
        fclose(arquivo);
        printf("Relatório salvo com sucesso em relatorio.csv\n");
    }
}

void relatoriopagardata(LacamentosRetiradas *lancamentosretiradas, long int tamlancamentoretirada, Entradaestoque *entradaestoque,
                        long int tamentradaestoque, char *data1, char *data2, int opcsv)
{
    if (entradaestoque == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    int inicio = converterdata(data1);
    int fim = converterdata(data2);

    if (opcsv == 1)
    {

        for (long int i = 0; i < tamentradaestoque; i++)
        {
            int atual = converterdata(entradaestoque[i].data);
            int pago = 0;

            for (long int j = 0; j < tamlancamentoretirada; j++)
            {
                if (lancamentosretiradas[j].codigoentradaestoque == entradaestoque[i].codigo)
                {
                    pago = 1;
                    break;
                }
            }

            if (atual >= inicio && atual <= fim && !pago)
            {
                printf("Data: %s\n", entradaestoque[i].data);
                printf("Fornecedor: %s\n", entradaestoque[i].fornecedor);
                printf("Valor: %.2f\n\n", entradaestoque[i].totaldetudo);
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Data,Fornecedor,Valor\n");

        for (long int i = 0; i < tamentradaestoque; i++)
        {
            int atual = converterdata(entradaestoque[i].data);
            int pago = 0;

            for (long int j = 0; j < tamlancamentoretirada; j++)
            {
                if (lancamentosretiradas[j].codigoentradaestoque == entradaestoque[i].codigo)
                {
                    pago = 1;
                    break;
                }
            }

            if (atual >= inicio && atual <= fim && !pago)
            {
                fprintf(arquivo, "%s,%s,%.2f\n", entradaestoque[i].data, entradaestoque[i].fornecedor, entradaestoque[i].totaldetudo);
            }
        }

        fclose(arquivo);
        printf("Relatório salvo em relatorio_contas_pagar.csv\n");
    }
}

void relatoriopagarsemfiltro(LacamentosRetiradas *lancamentosretiradas, long int tamlancamentoretirada, Entradaestoque *entradaestoque,
                             long int tamentradaestoque, int opcsv)
{
    if (entradaestoque == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamentradaestoque; i++)
        {
            int pago = 0;

            for (long int j = 0; j < tamlancamentoretirada; j++)
            {
                if (lancamentosretiradas[j].codigoentradaestoque == entradaestoque[i].codigo)
                {
                    pago = 1;
                    break;
                }
            }

            if (!pago)
            {
                printf("Data: %s\n", entradaestoque[i].data);
                printf("Fornecedor: %s\n", entradaestoque[i].fornecedor);
                printf("Valor: %.2f\n\n", entradaestoque[i].totaldetudo);
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio_contas_pagar.csv\n");
            return;
        }

        fprintf(arquivo, "Data,Fornecedor,Valor\n");

        for (long int i = 0; i < tamentradaestoque; i++)
        {
            int pago = 0;

            for (long int j = 0; j < tamlancamentoretirada; j++)
            {
                if (lancamentosretiradas[j].codigoentradaestoque == entradaestoque[i].codigo)
                {
                    pago = 1;
                    break;
                }
            }

            if (!pago)
            {
                fprintf(arquivo, "%s,%s,%.2f\n", entradaestoque[i].data, entradaestoque[i].fornecedor, entradaestoque[i].totaldetudo);
            }
        }

        fclose(arquivo);
        printf("Relatório salvo em relatorio.csv\n");
    }
}

void relatorioestoqueprocedimento(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, Procedimento *procedimentos,
                                  long int tamprocedimento, long int codprocedimento, int opcsv)
{
    long int posicao = -1;
    if (procedimentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return; // não preciso verificar medicamentos e materiais porque quando eu fiz a função de
        // cadastrar procedimento fiz a logica pra não deixar cadastrar um procedimento
        // sem um codigo de medicamento que existam em medicamentos e materiais logo se procedimentos não for null medicamentosmateriais não sera
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamprocedimento; i++)
        {
            if (codprocedimento == procedimentos[i].codigo)
            {
                posicao = i;
            }
        }
        if (posicao == -1)
        {
            printf("ERRO: lista vazia\n");
            return;
        }
        for (long int i = 0; i < procedimentos[posicao].tamcodmedicamentosmateriais; i++)
        {
            for (long int j = 0; j < tammedicamentomaterial; j++)
            {
                if (procedimentos[posicao].codmedicamentosemateriais[i].codigo == medicamentosmateriais[j].codigo)
                {
                    printf("Codigo do medicamento:%ld\n", medicamentosmateriais[j].codigo);
                    printf("Quantidade em estoque:%ld\n", medicamentosmateriais[j].quantidadeEstoque);
                    printf("Quantidade usada no procedimento:%ld\n", procedimentos[posicao].codmedicamentosemateriais[i].qnt);
                    printf("Preço de custo:%f\n", medicamentosmateriais[j].precoCusto);
                    printf("Preço de venda:%f\n", medicamentosmateriais[j].precoVenda);
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Codigo medicamento,Quantidade em estoque,Quantidade usada no procedimento,Preço de custo,Preço de Venda\n");

        for (long int i = 0; i < tamprocedimento; i++)
        {
            if (codprocedimento == procedimentos[i].codigo)
            {
                posicao = i;
            }
        }
        if (posicao == -1)
        {
            fprintf(arquivo, "ERRO: lista vazia\n");
            fclose(arquivo);
            return;
        }

        for (long int i = 0; i < procedimentos[posicao].tamcodmedicamentosmateriais; i++)
        {
            for (long int j = 0; j < tammedicamentomaterial; j++)
            {
                if (procedimentos[posicao].codmedicamentosemateriais[i].codigo == medicamentosmateriais[j].codigo)
                {
                    fprintf(arquivo, "%ld,%ld,%ld,%.2f,%.2f\n",
                            medicamentosmateriais[j].codigo,
                            medicamentosmateriais[j].quantidadeEstoque,
                            procedimentos[posicao].codmedicamentosemateriais[i].qnt,
                            medicamentosmateriais[j].precoCusto,
                            medicamentosmateriais[j].precoVenda);
                }
            }
        }

        fclose(arquivo);
        printf("Relatório salvo em relatorios.csv\n");
    }
}

void relatorioestoquepaciente(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial,
                              Agendamento *agendamentos, long int tamagendamentos,
                              Procedimento *procedimentos, long int tamprocedimento,
                              long int codpaciente, int opcsv)
{
    if (agendamentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamagendamentos; i++)
        {
            if (agendamentos[i].codpaciente == codpaciente)
            {
                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        for (long int k = 0; k < procedimentos[j].tamcodmedicamentosmateriais; k++)
                        {
                            long int codMedicamento = procedimentos[j].codmedicamentosemateriais[k].codigo;
                            for (long int l = 0; l < tammedicamentomaterial; l++)
                            {
                                if (medicamentosmateriais[l].codigo == codMedicamento)
                                {
                                    printf("Código do medicamento: %ld\n", medicamentosmateriais[l].codigo);
                                    printf("Quantidade em estoque: %ld\n", medicamentosmateriais[l].quantidadeEstoque);
                                    printf("Preço de custo: %.2f\n", medicamentosmateriais[l].precoCusto);
                                    printf("Preço de venda: %.2f\n", medicamentosmateriais[l].precoVenda);
                                    printf("\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Codigo Medicamento,Quantidade Estoque,Preco Custo,Preco Venda\n");

        for (long int i = 0; i < tamagendamentos; i++)
        {
            if (agendamentos[i].codpaciente == codpaciente)
            {
                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        for (long int k = 0; k < procedimentos[j].tamcodmedicamentosmateriais; k++)
                        {
                            long int codMedicamento = procedimentos[j].codmedicamentosemateriais[k].codigo;
                            for (long int l = 0; l < tammedicamentomaterial; l++)
                            {
                                if (medicamentosmateriais[l].codigo == codMedicamento)
                                {
                                    fprintf(arquivo, "%ld,%ld,%.2f,%.2f\n",
                                            medicamentosmateriais[l].codigo,
                                            medicamentosmateriais[l].quantidadeEstoque,
                                            medicamentosmateriais[l].precoCusto,
                                            medicamentosmateriais[l].precoVenda);
                                }
                            }
                        }
                    }
                }
            }
        }

        fclose(arquivo);
        printf("Relatório gerado com sucesso no arquivo relatorio.csv\n");
    }
}
void relatoriosestoquedata(Entradaestoque *entradaestoque, long int tamentradaestoque,
                           MedicamentoMaterial *medicamentosmateriais, long int tammedicamamentomaterial,
                           char *data1, char *data2, int opcsv)
{
    if (entradaestoque == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    int inicio = converterdata(data1);
    int fim = converterdata(data2);

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamentradaestoque; i++)
        {
            int atual = converterdata(entradaestoque[i].data);
            if (atual >= inicio && atual <= fim)
            {
                for (long int k = 0; k < entradaestoque[i].tammedicamentosmateriaisrecebidos; k++)
                {
                    for (long int j = 0; j < tammedicamamentomaterial; j++)
                    {
                        if (entradaestoque[i].codmedicamentosmateriaisrecebidos[k].codigo == medicamentosmateriais[j].codigo)
                        {
                            printf("Codigo do medicamento: %ld\n", medicamentosmateriais[j].codigo);
                            printf("Quantidade em estoque: %ld\n", medicamentosmateriais[j].quantidadeEstoque);
                            printf("Quantidade recebida: %ld\n", entradaestoque[i].codmedicamentosmateriaisrecebidos[k].qnt);
                            printf("Preço de custo: %.2f\n", medicamentosmateriais[j].precoCusto);
                            printf("Preço de venda: %.2f\n", medicamentosmateriais[j].precoVenda);
                        }
                    }
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Cod Medicamento,Qnt estoque,Qnt Recebida,Preço custo,Preço Venda\n");

        for (long int i = 0; i < tamentradaestoque; i++)
        {
            int atual = converterdata(entradaestoque[i].data);
            if (atual >= inicio && atual <= fim)
            {
                for (long int k = 0; k < entradaestoque[i].tammedicamentosmateriaisrecebidos; k++)
                {
                    for (long int j = 0; j < tammedicamamentomaterial; j++)
                    {
                        if (entradaestoque[i].codmedicamentosmateriaisrecebidos[k].codigo == medicamentosmateriais[j].codigo)
                        {
                            fprintf(arquivo, "%ld,%ld,%ld,%.2f,%.2f\n",
                                    medicamentosmateriais[j].codigo,
                                    medicamentosmateriais[j].quantidadeEstoque,
                                    entradaestoque[i].codmedicamentosmateriaisrecebidos[k].qnt,
                                    medicamentosmateriais[j].precoCusto,
                                    medicamentosmateriais[j].precoVenda);
                        }
                    }
                }
            }
        }

        fclose(arquivo);
        printf("Relatório salvo em relatorio_contas_pagar.csv\n");
    }
}

void relatorioestoqueprofissional(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, Agendamento *agendamentos, long int tamagendamentos, Procedimento *procedimentos, long int tamprocedimento, long int codprofissional, int opcsv)

{

    if (agendamentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamagendamentos; i++)
        {
            if (agendamentos[i].codprofissional == codprofissional)
            {
                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        for (long int k = 0; k < procedimentos[j].tamcodmedicamentosmateriais; k++)
                        {
                            long int codMedicamento = procedimentos[j].codmedicamentosemateriais[k].codigo;
                            for (long int l = 0; l < tammedicamentomaterial; l++)
                            {
                                if (medicamentosmateriais[l].codigo == codMedicamento)
                                {
                                    printf("Código do medicamento: %ld\n", medicamentosmateriais[l].codigo);
                                    printf("Quantidade em estoque: %ld\n", medicamentosmateriais[l].quantidadeEstoque);
                                    printf("Preço de custo: %.2f\n", medicamentosmateriais[l].precoCusto);
                                    printf("Preço de venda: %.2f\n", medicamentosmateriais[l].precoVenda);
                                    printf("\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Codigo Medicamento,Quantidade Estoque,Preco Custo,Preco Venda\n");

        for (long int i = 0; i < tamagendamentos; i++)
        {
            if (agendamentos[i].codprofissional == codprofissional)
            {
                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        for (long int k = 0; k < procedimentos[j].tamcodmedicamentosmateriais; k++)
                        {
                            long int codMedicamento = procedimentos[j].codmedicamentosemateriais[k].codigo;
                            for (long int l = 0; l < tammedicamentomaterial; l++)
                            {
                                if (medicamentosmateriais[l].codigo == codMedicamento)
                                {
                                    fprintf(arquivo, "%ld,%ld,%.2f,%.2f\n",
                                            medicamentosmateriais[l].codigo,
                                            medicamentosmateriais[l].quantidadeEstoque,
                                            medicamentosmateriais[l].precoCusto,
                                            medicamentosmateriais[l].precoVenda);
                                }
                            }
                        }
                    }
                }
            }
        }

        fclose(arquivo);
        printf("Relatório gerado com sucesso no arquivo relatorio.csv\n");
    }
}

void relatorioestoqueminimo(MedicamentoMaterial *medicamentomaterial, long int tammedicamentomaterial, int opcsv)
{
    if (medicamentomaterial == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tammedicamentomaterial; i++)
        {
            if (medicamentomaterial[i].quantidadeEstoque < medicamentomaterial[i].estoqueMinimo)
            {
                printf("Codigo do medicamento: %ld\n", medicamentomaterial[i].codigo);
                printf("Quantidade em estoque: %ld\n", medicamentomaterial[i].quantidadeEstoque);
                printf("Preço de custo: %.2f\n", medicamentomaterial[i].precoCusto);
                printf("Preço de venda: %.2f\n", medicamentomaterial[i].precoVenda);
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Codigo Medicamento,Quantidade Estoque,Preco Custo,Preco Venda\n");

        for (long int i = 0; i < tammedicamentomaterial; i++)
        {
            if (medicamentomaterial[i].quantidadeEstoque < medicamentomaterial[i].estoqueMinimo)
            {
                fprintf(arquivo, "%ld,%ld,%.2f,%.2f\n",
                        medicamentomaterial[i].codigo,
                        medicamentomaterial[i].quantidadeEstoque,
                        medicamentomaterial[i].precoCusto,
                        medicamentomaterial[i].precoVenda);
            }
        }

        fclose(arquivo);
        printf("Relatório gerado com sucesso em relatorio.csv\n");
    }
}

void relatorioestoquesemfiltro(MedicamentoMaterial *medicamentomaterial, long int tammedicamentomaterial, int opcsv)
{
    if (medicamentomaterial == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tammedicamentomaterial; i++)
        {
            if (medicamentomaterial[i].quantidadeEstoque > 0)
            {
                printf("Codigo do medicamento: %ld\n", medicamentomaterial[i].codigo);
                printf("Quantidade em estoque: %ld\n", medicamentomaterial[i].quantidadeEstoque);
                printf("Preço de custo: %.2f\n", medicamentomaterial[i].precoCusto);
                printf("Preço de venda: %.2f\n", medicamentomaterial[i].precoVenda);
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Codigo Medicamento,Quantidade Estoque,Preco Custo,Preco Venda\n");

        for (long int i = 0; i < tammedicamentomaterial; i++)
        {
            if (medicamentomaterial[i].quantidadeEstoque > 0)
            {
                fprintf(arquivo, "%ld,%ld,%.2f,%.2f\n",
                        medicamentomaterial[i].codigo,
                        medicamentomaterial[i].quantidadeEstoque,
                        medicamentomaterial[i].precoCusto,
                        medicamentomaterial[i].precoVenda);
            }
        }

        fclose(arquivo);
        printf("Relatório salvo no arquivo relatorio.csv\n");
    }
}

void relatoriobasicopacientecidade(Paciente *pacientes, long int tampacientes, char *cidade, int opcsv)
{
    if (pacientes == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tampacientes; i++)
        {
            if (strcmp(cidade, pacientes[i].endereco.cidade) == 0)
            {
                printf("Codigo: %ld\n", pacientes[i].codigo);
                printf("Nome: %s\n", pacientes[i].nomeCompleto);
                printf("Cidade: %s\n", pacientes[i].endereco.cidade);
                printf("-------------------------\n");
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Codigo,Nome,Cidade\n");
        for (long int i = 0; i < tampacientes; i++)
        {
            if (strcmp(cidade, pacientes[i].endereco.cidade) == 0)
            {
                fprintf(arquivo, "%ld,%s,%s\n",
                        pacientes[i].codigo,
                        pacientes[i].nomeCompleto,
                        pacientes[i].endereco.cidade);
            }
        }

        fclose(arquivo);
        printf("Relatório salvo em relatorio.csv\n");
    }
}

void relatoriobasicopacientesemfiltro(Paciente *paciente, long int tampacientes, int opscv)
{
    if (paciente == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opscv == 1)
    {
        listarpacientes(paciente, tampacientes);
    }
    else if (opscv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Codigo,Nome,Cidade\n");

        for (long int i = 0; i < tampacientes; i++)
        {
            fprintf(arquivo, "%ld,%s,%s\n",
                    paciente[i].codigo,
                    paciente[i].nomeCompleto,
                    paciente[i].endereco.cidade);
        }

        fclose(arquivo);
        printf("Relatório exportado para relatorio.csv com sucesso.\n");
    }
}

void relatorioprocedimentoprocedimento(Agendamento *agendamentos, long int tamagendamento,
                                       Procedimento *procedimentos, long int tamprocedimento,
                                       long int codprocedimento, int opcsv)
{

    if (agendamentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamagendamento; i++)
        {
            if (codprocedimento == agendamentos[i].codprocedimento)
            {
                printf("Data: %s", agendamentos[i].data);
                printf("Codigo do procedimento: %ld\n", agendamentos[i].codprocedimento);
                printf("Codigo do profissional responsavel: %ld\n", agendamentos[i].codprofissional);
                printf("Codigo do paciente: %ld\n", agendamentos[i].codpaciente);

                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        printf("Codigo do ambiente médico: %ld\n", procedimentos[j].codambientemedico);
                        printf("Valor total: %.2f\n", procedimentos[j].custo);
                    }
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Data,Cod procedimento,Cod profissional,Cod paciente,Cod ambiente medico,Valor total\n");

        for (long int i = 0; i < tamagendamento; i++)
        {
            if (codprocedimento == agendamentos[i].codprocedimento)
            {
                long int codambiente = -1;
                float custo = 0.0;

                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        codambiente = procedimentos[j].codambientemedico;
                        custo = procedimentos[j].custo;
                        break;
                    }
                }

                fprintf(arquivo, "%s,%ld,%ld,%ld,%ld,%.2f\n",
                        agendamentos[i].data,
                        agendamentos[i].codprocedimento,
                        agendamentos[i].codprofissional,
                        agendamentos[i].codpaciente,
                        codambiente,
                        custo);
            }
        }

        fclose(arquivo);
    }
}

void relatorioprocedimentopaciente(Agendamento *agendamentos, long int tamagendamento,
                                   Procedimento *procedimentos, long int tamprocedimento,
                                   Paciente *pacientes, long int tampacientes,
                                   long int codpaciente, int opcsv)
{

    if (agendamentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamagendamento; i++)
        {
            if (codpaciente == agendamentos[i].codpaciente)
            {
                printf("Data: %s", agendamentos[i].data);
                printf("Codigo do procedimento: %ld\n", agendamentos[i].codprocedimento);
                printf("Codigo do profissional responsavel: %ld\n", agendamentos[i].codprofissional);

                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        printf("Codigo do ambiente médico: %ld\n", procedimentos[j].codambientemedico);
                        printf("Valor total: %.2f\n", procedimentos[j].custo);
                    }
                }
                for (long int k = 0; k < tampacientes; k++)
                {
                    if (agendamentos[i].codpaciente == pacientes[k].codigo)
                    {
                        printf("Codigo do paciente: %ld\n", agendamentos[i].codpaciente);
                        printf("Nome do paciente: %s\n", pacientes[k].nomeCompleto);
                    }
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Data,Cod procedimento,Cod profissional,Cod ambiente medico,Valor total,Cod paciente,Nome\n");

        for (long int i = 0; i < tamagendamento; i++)
        {
            if (codpaciente == agendamentos[i].codpaciente)
            {

                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        for (long int k = 0; k < tampacientes; k++)
                        {
                            if (agendamentos[i].codpaciente == pacientes[k].codigo)
                            {
                                fprintf(arquivo, "%s,%ld,%ld,%ld,%.2f,%ld,%s\n",
                                        agendamentos[i].data,
                                        agendamentos[i].codprocedimento,
                                        agendamentos[i].codprofissional,
                                        procedimentos[j].codambientemedico,
                                        procedimentos[j].custo,
                                        agendamentos[i].codpaciente,
                                        pacientes[k].nomeCompleto);
                            }
                        }
                    }
                }
            }
        }

        fclose(arquivo);
    }
}

void relatorioprocedimentodata(Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento, char *data1, char *data2, int opcsv)
{
    if (agendamentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    int inicio = converterdata(data1);
    int fim = converterdata(data2);

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamagendamento; i++)
        {
            int atual = converterdata(agendamentos[i].data);
            if (atual >= inicio && atual <= fim)
            {
                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        printf("Codigo do procedimento:%ld", procedimentos[j].codigo);
                        printf("Codigo do ambiente médico:%ld", procedimentos[j].codambientemedico);
                        printf("Codigo do paciente:%ld", agendamentos[i].codpaciente);
                        printf("Data:%s", agendamentos[i].data);
                        printf("Custo total:%f", procedimentos[j].custo);
                    }
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Cod Procedimento,Cod ambiente,Cod paciente,Data,Custo\n");

        for (long int i = 0; i < tamagendamento; i++)
        {
            int atual = converterdata(agendamentos[i].data);
            if (atual >= inicio && atual <= fim)
            {
                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        fprintf(arquivo, "%ld,%ld,%ld,%s,%.2f\n",
                                procedimentos[j].codigo,
                                procedimentos[j].codambientemedico,
                                agendamentos[i].codpaciente,
                                agendamentos[i].data,
                                procedimentos[j].custo);
                    }
                }
            }
        }

        fclose(arquivo);
    }
}

void relatorioprocedimentoprofissional(Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento, Profissional *profissional, long int tamprofissional, long int codprofissional, int opcsv)
{

    if (agendamentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamagendamento; i++)
        {
            if (codprofissional == agendamentos[i].codprofissional)
            {
                printf("Data: %s", agendamentos[i].data);
                printf("Codigo do procedimento: %ld\n", agendamentos[i].codprocedimento);
                printf("Codigo do paciente: %ld\n", agendamentos[i].codpaciente);

                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        printf("Codigo do ambiente médico: %ld\n", procedimentos[j].codambientemedico);
                        printf("Valor total: %.2f\n", procedimentos[j].custo);
                    }
                }
                for (long int k = 0; k < tamprofissional; k++)
                {
                    if (agendamentos[i].codprofissional == profissional[k].codigo)
                    {
                        printf("Codigo do profissional: %ld\n", agendamentos[i].codprofissional);
                        printf("Nome do profissional: %s\n", profissional[k].nomeCompleto);
                    }
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Data,Cod procedimento,Cod paciente,Cod ambiente medico,Valor total,Cod profissional,Nome\n");

        for (long int i = 0; i < tamagendamento; i++)
        {
            if (codprofissional == agendamentos[i].codprofissional)
            {

                for (long int j = 0; j < tamprocedimento; j++)
                {
                    if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                    {
                        for (long int k = 0; k < tamprofissional; k++)
                        {
                            if (agendamentos[i].codprofissional == profissional[k].codigo)
                            {
                                fprintf(arquivo, "%s,%ld,%ld,%ld,%.2f,%ld,%s\n",
                                        agendamentos[i].data,
                                        agendamentos[i].codprocedimento,
                                        agendamentos[i].codpaciente,
                                        procedimentos[j].codambientemedico,
                                        procedimentos[j].custo,
                                        agendamentos[i].codprofissional,
                                        profissional[k].nomeCompleto);
                            }
                        }
                    }
                }
            }
        }

        fclose(arquivo);
    }
}

void relatorioprocedimentosemfiltro(Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento, int opcsv)
{
    if (agendamentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamagendamento; i++)
        {
            for (long int j = 0; j < tamprocedimento; j++)
            {
                if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                {
                    printf("Data: %s", agendamentos[i].data);
                    printf("Codigo do procedimento: %ld\n", agendamentos[i].codprocedimento);
                    printf("Codigo do paciente: %ld\n", agendamentos[i].codpaciente);
                    printf("Codigo do profissional: %ld\n", agendamentos[i].codprofissional);
                    printf("Valor total: %f\n", procedimentos[j].custo);
                }
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        fprintf(arquivo, "Data,Cod Procedimento,Cod Paciente,Cod Profissional,Valor Total\n");
        for (long int i = 0; i < tamagendamento; i++)
        {
            for (long int j = 0; j < tamprocedimento; j++)
            {
                if (agendamentos[i].codprocedimento == procedimentos[j].codigo)
                {
                    fprintf(arquivo, "%s,%ld,%ld,%ld,%.2f\n",
                            agendamentos[i].data,
                            agendamentos[i].codprocedimento,
                            agendamentos[i].codpaciente,
                            agendamentos[i].codprofissional,
                            procedimentos[j].custo);
                }
            }
        }

        fclose(arquivo);
        printf("Relatório salvo em relatorio.csv\n");
    }
}

void relatoriosbasicofornecedores(Fornecedor *fornecedores, long int tamfornecedores, char *estado, int opcsv)
{
    if (fornecedores == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamfornecedores; i++)
        {
            if (strcmp(fornecedores[i].endereco.estado, estado) == 0)
            {
                printf("Codigo: %ld\n", fornecedores[i].codigo);
                printf("CNPJ: %s\n", fornecedores[i].cnpj);
                printf("Email: %s\n", fornecedores[i].email);
                printf("Nome: %s\n", fornecedores[i].nomeFantasia);
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Codigo,CNPJ,Email,NomeFantasia\n");
        for (long int i = 0; i < tamfornecedores; i++)
        {
            if (strcmp(fornecedores[i].endereco.estado, estado) == 0)
            {
                fprintf(arquivo, "%ld,%s,%s,%s\n",
                        fornecedores[i].codigo,
                        fornecedores[i].cnpj,
                        fornecedores[i].email,
                        fornecedores[i].nomeFantasia);
            }
        }

        fclose(arquivo);
    }
}

void relatoriosbasicosfornecedoressemfiltro(Fornecedor *fornecedores, long int tamfornecedor, int opcsv)
{
    if (fornecedores == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
      listarfornecedores(fornecedores,tamfornecedor);
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Codigo,Nome Fantasia,Razao Social,Inscricao Estadual,CNPJ,Rua,Numero,Bairro,Cidade,Estado,Telefone,Email\n");

        for (long int i = 0; i < tamfornecedor; i++)
        {
            fprintf(arquivo, "%ld,%s,%s,%s,%s,%s,%ld,%s,%s,%s,%s,%s\n",
                    fornecedores[i].codigo,
                    fornecedores[i].nomeFantasia,
                    fornecedores[i].razaoSocial,
                    fornecedores[i].inscricaoEstadual,
                    fornecedores[i].cnpj,
                    fornecedores[i].endereco.rua,
                    fornecedores[i].endereco.numero,
                    fornecedores[i].endereco.bairro,
                    fornecedores[i].endereco.cidade,
                    fornecedores[i].endereco.estado,
                    fornecedores[i].telefone,
                    fornecedores[i].email);
        }

        fclose(arquivo);
        printf("Relatório gerado com sucesso no arquivo relatorio.csv\n");
    }
}

void relatoriobasicoambientes(AmbienteMedico *ambientes, long int tamabiente, int opcsv)
{
    if (ambientes == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }
    else if (opcsv == 1)
    {
        listarambiente(ambientes, tamabiente);
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Codigo;Descricao do Procedimento\n");
        for (long int i = 0; i < tamabiente; i++)
        {
            fprintf(arquivo, "%ld;%s\n", ambientes[i].codigo, ambientes[i].descricaoProcedimento);
        }

        fclose(arquivo);
        printf("Relatório gerado com sucesso em 'relatorio.csv'\n");
    }
}

void relatoriobasicomedicamentomaterialfornecedor(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codfornecedor, int opcsv)
{
    if (medicamentosmateriais == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tammedicamentomaterial; i++)
        {
            if (codfornecedor == medicamentosmateriais[i].codfornecedor)
            {
                printf("Código: %ld\n", medicamentosmateriais[i].codigo);
                printf("Descrição: %s\n", medicamentosmateriais[i].descricao);
                printf("Fabricante: %s\n", medicamentosmateriais[i].fabricante);
                printf("Preço de Custo: %.2f\n", medicamentosmateriais[i].precoCusto);
                printf("Preço de Venda: %.2f\n", medicamentosmateriais[i].precoVenda);
                printf("Quantidade em Estoque: %ld\n", medicamentosmateriais[i].quantidadeEstoque);
                printf("Estoque Mínimo: %ld\n", medicamentosmateriais[i].estoqueMinimo);
                printf("------------------------------------------\n");
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Codigo;Descricao;Fabricante;Preco de Custo;Preco de Venda;Quantidade em Estoque;Estoque Minimo\n");

        for (long int i = 0; i < tammedicamentomaterial; i++)
        {
            if (codfornecedor == medicamentosmateriais[i].codfornecedor)
            {
                fprintf(arquivo, "%ld;%s;%s;%.2f;%.2f;%ld;%ld\n",
                        medicamentosmateriais[i].codigo,
                        medicamentosmateriais[i].descricao,
                        medicamentosmateriais[i].fabricante,
                        medicamentosmateriais[i].precoCusto,
                        medicamentosmateriais[i].precoVenda,
                        medicamentosmateriais[i].quantidadeEstoque,
                        medicamentosmateriais[i].estoqueMinimo);
            }
        }

        fclose(arquivo);
        printf("Relatório gerado com sucesso em 'relatorio.csv'\n");
    }
}

void relatoriobasicomedicamentomaterialsemfiltro(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, int opcsv)
{

    if (medicamentosmateriais == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }
    if (opcsv == 1)
    {
        for (long int i = 0; i < tammedicamentomaterial; i++)
        {
            printf("Código: %ld\n", medicamentosmateriais[i].codigo);
            printf("Descrição: %s\n", medicamentosmateriais[i].descricao);
            printf("Fabricante: %s\n", medicamentosmateriais[i].fabricante);
            printf("Preço de Custo: %.2f\n", medicamentosmateriais[i].precoCusto);
            printf("Preço de Venda: %.2f\n", medicamentosmateriais[i].precoVenda);
            printf("Quantidade em Estoque: %ld\n", medicamentosmateriais[i].quantidadeEstoque);
            printf("Estoque Mínimo: %ld\n", medicamentosmateriais[i].estoqueMinimo);
            printf("------------------------------------------\n");
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Codigo;Descricao;Fabricante;Preco de Custo;Preco de Venda;Quantidade em Estoque;Estoque Minimo\n");

        for (long int i = 0; i < tammedicamentomaterial; i++)
        {
            fprintf(arquivo, "%ld;%s;%s;%.2f;%.2f;%ld;%ld\n",
                    medicamentosmateriais[i].codigo,
                    medicamentosmateriais[i].descricao,
                    medicamentosmateriais[i].fabricante,
                    medicamentosmateriais[i].precoCusto,
                    medicamentosmateriais[i].precoVenda,
                    medicamentosmateriais[i].quantidadeEstoque,
                    medicamentosmateriais[i].estoqueMinimo);
        }

        fclose(arquivo);
        printf("Relatório gerado com sucesso em 'relatorio.csv'\n");
    }
} 

void relatoriobasicoprocedimentoambiente(Procedimento *procedimentos, long int tamprocedimento, long int codambiente, int opcsv)
{
    if (procedimentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
        for (long int i = 0; i < tamprocedimento; i++)
        {
            if (procedimentos[i].codambientemedico == codambiente)
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
            }
        }
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }

        // Cabeçalho do CSV
        fprintf(arquivo, "Código do procedimento,Descrição,Custo,Tempo estimado (min),Código do ambiente médico,Código do material,Quantidade usada\n");

        for (long int i = 0; i < tamprocedimento; i++)
        {
            if (procedimentos[i].codambientemedico == codambiente)
            {
                if (procedimentos[i].codmedicamentosemateriais != NULL &&
                    procedimentos[i].tamcodmedicamentosmateriais > 0)
                {
                    for (int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
                    {
                        fprintf(arquivo, "%ld,%s,%.2f,%ld,%ld,%ld,%ld\n",
                                procedimentos[i].codigo,
                                procedimentos[i].descricao,
                                procedimentos[i].custo,
                                procedimentos[i].tempoEstimado,
                                procedimentos[i].codambientemedico,
                                procedimentos[i].codmedicamentosemateriais[j].codigo,
                                procedimentos[i].codmedicamentosemateriais[j].qnt);
                    }
                }
                else
                {
                    // Se não houver materiais, preenche os campos com vazio
                    fprintf(arquivo, "%ld,%s,%.2f,%ld,%ld,,\n",
                            procedimentos[i].codigo,
                            procedimentos[i].descricao,
                            procedimentos[i].custo,
                            procedimentos[i].tempoEstimado,
                            procedimentos[i].codambientemedico);
                }
            }
        }

        fclose(arquivo);
    }
}

void relatoriobasicoprocedimentosemfiltro(Procedimento *procedimentos,long int tamprocedimento,int opcsv){

       if (procedimentos == NULL)
    {
        printf("ERRO: lista vazia\n");
        return;
    }

    if (opcsv == 1)
    {
         listarprocedimento(procedimentos,tamprocedimento);
    }
    else if (opcsv == 2)
    {
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Código do procedimento,Descrição,Custo,Tempo estimado (min),Código do ambiente médico,Código do material,Quantidade usada\n");

        for (long int i = 0; i < tamprocedimento; i++)
        {
                if (procedimentos[i].codmedicamentosemateriais != NULL &&
                    procedimentos[i].tamcodmedicamentosmateriais > 0)
                {
                    for (int j = 0; j < procedimentos[i].tamcodmedicamentosmateriais; j++)
                    {
                        fprintf(arquivo, "%ld,%s,%.2f,%ld,%ld,%ld,%ld\n",
                                procedimentos[i].codigo,
                                procedimentos[i].descricao,
                                procedimentos[i].custo,
                                procedimentos[i].tempoEstimado,
                                procedimentos[i].codambientemedico,
                                procedimentos[i].codmedicamentosemateriais[j].codigo,
                                procedimentos[i].codmedicamentosemateriais[j].qnt);
                    }
                }
                else
                {
                    // Se não houver materiais, preenche os campos com vazio
                    fprintf(arquivo, "%ld,%s,%.2f,%ld,%ld,,\n",
                            procedimentos[i].codigo,
                            procedimentos[i].descricao,
                            procedimentos[i].custo,
                            procedimentos[i].tempoEstimado,
                            procedimentos[i].codambientemedico);
                }
            
        }

        fclose(arquivo);
    }
}
void relatoriobasicoprofissionaisespecialidade(Profissional *profissionais, long int tamprofissionais, char *especialidade, int opcsv){
    if(profissionais == NULL){
        printf("ERRO: lista vazia\n");
        return;
    }

    if(opcsv == 1){
        for(long int i = 0; i < tamprofissionais; i++){
            if(strcmp(profissionais[i].especialidade, especialidade) == 0){
                printf("Código: %ld\n", profissionais[i].codigo);
                printf("Nome completo: %s\n", profissionais[i].nomeCompleto);
                printf("CRM: %s\n", profissionais[i].crm);
                printf("Especialidade: %s\n", profissionais[i].especialidade);
                printf("CPF: %s\n", profissionais[i].cpf);
                printf("Telefone: %s\n", profissionais[i].telefone);
                printf("Email: %s\n\n", profissionais[i].email);
            }
        }
    }
    else if(opcsv == 2){
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Código,Nome completo,CRM,Especialidade,CPF,Telefone,Email\n");
        for(long int i = 0; i < tamprofissionais; i++){
            if(strcmp(profissionais[i].especialidade, especialidade) == 0){
                fprintf(arquivo, "%ld,%s,%s,%s,%s,%s,%s\n",
                        profissionais[i].codigo,
                        profissionais[i].nomeCompleto,
                        profissionais[i].crm,
                        profissionais[i].especialidade,
                        profissionais[i].cpf,
                        profissionais[i].telefone,
                        profissionais[i].email);
            }
        }

        fclose(arquivo);
    }
}
void relatoriobasicoprofissionaissemfiltro(Profissional *profissionais, long int tamprofissionais,int opcsv){
     if(profissionais == NULL){
        printf("ERRO: lista vazia\n");
        return;
    }

    if(opcsv == 1){
      listarprofissional(profissionais,tamprofissionais);
    }
    else if(opcsv == 2){
        FILE *arquivo = fopen("relatorio.csv", "w");
        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo relatorio.csv\n");
            return;
        }
        fprintf(arquivo, "Código,Nome completo,CRM,Especialidade,CPF,Telefone,Email\n");
        for(long int i = 0; i < tamprofissionais; i++){
                fprintf(arquivo, "%ld,%s,%s,%s,%s,%s,%s\n",
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
}

