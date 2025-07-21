#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

Agendamento *cadastraragendamento(Agendamento *agendamentos, long int *tamagendamentos, long int *codigoatual,
                                  Agendamento *novoagendamento, Paciente *pacientes, long int tampacientes, Profissional *profissionais, long int tamprofissionais,
                                  Procedimento *procedimentos, long int tamprocedimento,
                                  MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial)
{
    long int epaciente = -1, eprofissional = -1, eprocedimento = -1, aux; // e de encontrado
    int flag = 0;                                                         // vou usar isso pra saber se tem um agendamento conflitante
    // verificar se existe o paciente
    for (int i = 0; i < tampacientes; i++)
    {
        if (novoagendamento->codpaciente == pacientes[i].codigo)
        {
            epaciente = 0;
        }
    }
    if (epaciente == -1)
    {
        return agendamentos; // nao encontrado paciente
    }
    // verifica profissional
    for (int i = 0; i < tamprofissionais; i++)
    {
        if (novoagendamento->codprofissional == profissionais[i].codigo)
        {
            eprofissional = 0;
        }
    }
    if (eprofissional == -1)
    {
        return agendamentos; // não encontrado profissional
    }
    for (int i = 0; i < tamprocedimento; i++)
    {
        if (novoagendamento->codprocedimento == procedimentos[i].codigo)
        {
            eprocedimento = 0;
            aux = i;
        }
    }
    if (eprocedimento == -1)
    {
        return agendamentos; // não encontrado o procedimento
    }

    // calcular horário final logo no início
    int hora, minuto;
    sscanf(novoagendamento->horario, "%d:%d", &hora, &minuto);
    int totalMinutos = hora * 60 + minuto + procedimentos[aux].tempoEstimado;
    int horaFim = totalMinutos / 60;
    int minutoFim = totalMinutos % 60;
    sprintf(novoagendamento->horariofim, "%02d:%02d", horaFim, minutoFim);

    // aqui como eu ja sei que o medicamento existe basta so e la e verificar a quantidade
    for (int i = 0; i < procedimentos[aux].tamcodmedicamentosmateriais; i++)
    {
        for (int j = 0; j < tammedicamentomaterial; j++)
        {
            if (procedimentos[aux].codmedicamentosemateriais[i].codigo == medicamentosmateriais[j].codigo)
            {
                if (medicamentosmateriais[j].quantidadeEstoque < procedimentos[aux].codmedicamentosemateriais[i].qnt)
                {
                    return agendamentos; // quantidade disponivel é menor que a que o procedimento precisa
                }
            }
        }
    }

    if (agendamentos != NULL && *tamagendamentos > 0)
    {
        for (int i = 0; i < *tamagendamentos; i++)
        {
            // pega o caso de fazer ao mesmo tempo
            if (strcmp(novoagendamento->data, agendamentos[i].data) == 0 &&
                strcmp(novoagendamento->horario, agendamentos[i].horario) == 0)
            {
                if (novoagendamento->codprocedimento == agendamentos[i].codprocedimento)
                {
                    flag = -1; // conflito de ambiente
                    return agendamentos;
                }
                if (novoagendamento->codprofissional == agendamentos[i].codprofissional)
                {
                    flag = -1; // conflito de profissional
                    return agendamentos;
                }
            }

            // pega o caso do horario
            else if (strcmp(novoagendamento->horariofim, agendamentos[i].horariofim) < 0 &&
                     strcmp(novoagendamento->data, agendamentos[i].data) == 0)
            {

                if (novoagendamento->codprocedimento == agendamentos[i].codprocedimento)
                {
                    flag = -1; // conflito de ambiente
                    return agendamentos;
                }
                if (novoagendamento->codprofissional == agendamentos[i].codprofissional)
                {
                    flag = -1; // conflito de profissional
                    return agendamentos;
                }
            }
        }
    }

    if (flag == 0)
    {
        Agendamento *novo = realloc(agendamentos, (*tamagendamentos + 1) * sizeof(Agendamento));
        if (novo == NULL)
        {
            return agendamentos;
        }

        agendamentos = novo;
        novoagendamento->codigo = *codigoatual;

        agendamentos[*tamagendamentos] = *novoagendamento;

        for (int i = 0; i < procedimentos[aux].tamcodmedicamentosmateriais; i++)
        {
            for (int j = 0; j < tammedicamentomaterial; j++)
            {
                if (procedimentos[aux].codmedicamentosemateriais[i].codigo == medicamentosmateriais[j].codigo)
                {
                    medicamentosmateriais[j].quantidadeEstoque -= procedimentos[aux].codmedicamentosemateriais[i].qnt;
                }
            }
        }

        (*tamagendamentos)++;
        (*codigoatual)++;
    }

    return agendamentos;
}

long int importaragendamento(Agendamento **agendamentos, char *nome, long int *tamagendamento, long int *codigoatualagendamento,
                             Paciente *pacientes, long int tampacientes,
                             Profissional *profissionais, long int tamprofissionais,
                             Procedimento *procedimentos, long int tamprocedimento,
                             MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
        return -1;

    char linha[1000];
    Agendamento novo;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "<tabela nome=\"agendamento\">") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</tabela>") == NULL)
            {
                if (strstr(linha, "<codigo>") != NULL)
                    sscanf(linha, "<codigo>%ld</codigo>", &novo.codigo);

                if (strstr(linha, "<paciente>") != NULL)
                    sscanf(linha, "<paciente>%ld</paciente>", &novo.codpaciente);

                if (strstr(linha, "<profissional>") != NULL)
                    sscanf(linha, "<profissional>%ld</profissional>", &novo.codprofissional);

                if (strstr(linha, "<procedimento>") != NULL)
                    sscanf(linha, "<procedimento>%ld</procedimento>", &novo.codprocedimento);

                if (strstr(linha, "<data>") != NULL)
                    sscanf(linha, "<data>%19[^<]</data>", novo.data);

                if (strstr(linha, "<hora>") != NULL)
                    sscanf(linha, "<hora>%19[^<]</hora>", novo.horario);

                if (strstr(linha, "</registro>") != NULL)
                {
                    *agendamentos = cadastraragendamento(*agendamentos, tamagendamento, codigoatualagendamento,
                                                         &novo, pacientes, tampacientes,
                                                         profissionais, tamprofissionais,
                                                         procedimentos, tamprocedimento,
                                                         medicamentosmateriais, tammedicamentomaterial);
                }
            }
            break;
        }
    }

    fclose(arquivo);
    return 0;
}

long int exportaragendamento(Agendamento *agendamentos, char *nome, long int tamagendamento)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
    {
        return -1;
    }

    if (agendamentos == NULL)
    {
        fclose(arquivo);
        return -1;
    }

    fprintf(arquivo, "<dados>\n");
    fprintf(arquivo, "<!-- Tabela de Agendamentos -->\n");
    fprintf(arquivo, "<tabela nome=\"agendamento\">\n");

    for (long int i = 0; i < tamagendamento; i++)
    {
        fprintf(arquivo, "<registro>\n");
        fprintf(arquivo, "<codigo>%ld</codigo>\n", agendamentos[i].codigo);
        fprintf(arquivo, "<paciente>%ld</paciente>\n", agendamentos[i].codpaciente);
        fprintf(arquivo, "<profissional>%ld</profissional>\n", agendamentos[i].codprofissional);
        fprintf(arquivo, "<procedimento>%ld</procedimento>\n", agendamentos[i].codprocedimento);
        fprintf(arquivo, "<data>%s</data>\n", agendamentos[i].data);
        fprintf(arquivo, "<hora>%s</hora>\n", agendamentos[i].horario);
        fprintf(arquivo, "</registro>\n");
    }

    fprintf(arquivo, "</tabela>\n");
    fprintf(arquivo, "</dados>\n");

    fclose(arquivo);
    return 0; // sucesso ao exportar
}

long int importaragendamentotxt(Agendamento **agendamentos, long int *tamagendamentos, long int *codigoatual, char *nome,
                                Paciente *pacientes, long int tampacientes,
                                Profissional *profissionais, long int tamprofissionais,
                                Procedimento *procedimentos, long int tamprocedimento,
                                MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1; // erro ao abrir arquivo
    }

    char linha[1024];
    Agendamento novoagendamento;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        char *token = strtok(linha, ";");
        if (token != NULL)
            novoagendamento.codigo = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            novoagendamento.codpaciente = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            novoagendamento.codprofissional = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            novoagendamento.codprocedimento = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novoagendamento.data, token, sizeof(novoagendamento.data));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novoagendamento.horario, token, sizeof(novoagendamento.horario));

        token = strtok(NULL, ";\n");
        if (token != NULL)
            strncpy(novoagendamento.horariofim, token, sizeof(novoagendamento.horariofim));

        *agendamentos = cadastraragendamento(*agendamentos, tamagendamentos, codigoatual, &novoagendamento,
                                             pacientes, tampacientes, profissionais, tamprofissionais,
                                             procedimentos, tamprocedimento,
                                             medicamentosmateriais, tammedicamentomaterial);
    }

    fclose(arquivo);
    return 0;
}

void exportaragendamentotxt(Agendamento *agendamentos, char *nome, long int tamagendamentos)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
    {
        return; // erro ao abrir arquivo
    }

    for (long int i = 0; i < tamagendamentos; i++)
    {
        fprintf(arquivo, "%ld;%ld;%ld;%ld;%s;%s;%s\n",
                agendamentos[i].codigo,
                agendamentos[i].codpaciente,
                agendamentos[i].codprofissional,
                agendamentos[i].codprocedimento,
                agendamentos[i].data,
                agendamentos[i].horario,
                agendamentos[i].horariofim);
    }

    fclose(arquivo);
} 

long int importaragendamentobin(Agendamento **agendamentos,long int *tamagendamentos,long int *codigoatual,const char *nomearquivo,Paciente *pacientes,long int tampacientes,Profissional *profissionais,long int tamprofissionais,Procedimento *procedimentos,long int tamprocedimento,MedicamentoMaterial *medicamentosmateriais,long int tammedicamentomaterial)
{
    FILE *arquivo = fopen(nomearquivo, "rb");
    if (!arquivo)
        return -1; // erro ao abrir arquivo

    long int total;
    if (fread(&total, sizeof(long int), 1, arquivo) != 1)
    {
        fclose(arquivo);
        return -2; // erro na leitura do total
    }

    for (long int i = 0; i < total; i++)
    {
        Agendamento temp;
        if (fread(&temp, sizeof(Agendamento), 1, arquivo) != 1)
        {
            fclose(arquivo);
            return -3; // erro na leitura do agendamento
        }

        *agendamentos = cadastraragendamento(
            *agendamentos, tamagendamentos, codigoatual,
            &temp, pacientes, tampacientes,
            profissionais, tamprofissionais,
            procedimentos, tamprocedimento,
            medicamentosmateriais, tammedicamentomaterial);
    }

    fclose(arquivo);
    return 0; // sucesso
}

void exportaragendamentobin(Agendamento *agendamentos, long int tamagendamentos, const char *nomearquivo)
{
    FILE *arquivo = fopen(nomearquivo, "wb");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para escrita binária\n");
        return;
    }

    fwrite(&tamagendamentos, sizeof(long int), 1, arquivo);
    fwrite(agendamentos, sizeof(Agendamento), tamagendamentos, arquivo);

    fclose(arquivo);
}

