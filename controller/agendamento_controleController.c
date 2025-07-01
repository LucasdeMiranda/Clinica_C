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
        return -1; // não encontrado profissional
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

    if (agendamentos != NULL && tamagendamentos > 0)
    {
        for (int i = 0; i < *tamagendamentos; i++)
        {

            if (strcmp(novoagendamento->data, agendamentos[i].data) == 0 && strcmp(novoagendamento->horario, agendamentos[i].horario) == 0)
            {
                if (novoagendamento->codprocedimento == agendamentos[i].codprocedimento)
                {
                    flag = -1;
                    return agendamentos; // siginifica que o ambiente que o procedimento usa ja vai ser usado nesse dia
                }
                if (novoagendamento->codprofissional == agendamentos[i].codprofissional)
                {
                    flag = -1;
                    return agendamentos; // profissional ja vai atender nesse horario
                }
            }
        }
    }
    else if (agendamentos == NULL || flag == 0)
    {
        // aqui que começa o cadastro
        Agendamento *novo = realloc(agendamentos, (*tamagendamentos + 1) * sizeof(Agendamento));
        if (novo == NULL)
        {
            return agendamentos; // 2 vai ser pra que deu erro ao alocar a memoria
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
                    medicamentosmateriais[j].quantidadeEstoque = medicamentosmateriais[j].quantidadeEstoque - procedimentos[aux].codmedicamentosemateriais[i].qnt;
                }
            }
        }
        (*tamagendamentos)++;
        (*codigoatual)++;

        return agendamentos;
    }
}