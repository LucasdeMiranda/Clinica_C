#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

Agendamento *cadastraragendamento(Agendamento *agendamentos, long int *tamagendamentos, long int *codigoatual,
                                  Agendamento *novoagendamento, Paciente *pacientes, long int tampacientes, Profissional *profissionais, long int tamprofissionais,
                                  Procedimento *procedimentos, long int tamprocedimento,
                                  MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial)
{
    long int epaciente = -1, eprofissional = -1, eprocedimento = -1,
             emedicamentomaterial = -1, eambientesmedicos = -1, aux,cont1,cont2; // e de encontrado

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
            aux=i;
        }
    }
    if (eprocedimento == -1)
    {
        return agendamentos; // não encontrado o procedimento
    }
    //aqui eu vou contar quantos medicamentos e materias diferentes eu tenho no procedimento escolhido caso ele exista
    for(int i=0;i<procedimentos[aux].codmedicamentosemateriais;i++){
    cont1=procedimentos[aux].codmedicamentosemateriais[i];
    for(int j=0;j<procedimentos[aux].codmedicamentosemateriais;j++){
    if(procedimentos[aux].codmedicamentosemateriais[j]!=cont1){
        cont2++;
    }
    }
    }

}