#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

Paciente *cadastrarpaciente(Paciente *pacientes, long int *tampacientes, long int *codigoatual, Paciente *novopaciente)
{
    Paciente *novo = realloc(pacientes, (*tampacientes + 1) * sizeof(Paciente)); // usa um ponteiro auxiliar para o caso de não ser bem sucedido
    // não sobrescreve ou perde as informações anteriores por erros de realocação
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return pacientes; // Retorna o vetor original caso a alocação falhe
    }

    pacientes = novo;
    novopaciente->codigo = *codigoatual;
    pacientes[*tampacientes] = *novopaciente;
    (*tampacientes)++; // Atualiza a quantidade de pacientes
    (*codigoatual)++;
    return pacientes; // Retorna o ponteiro com o novo paciente inserido
}

long int alterarpaciente(Paciente *pacientes, long int tampacientes, long int codigo)
{
    if (pacientes == NULL)
    {
        return -1; // vazio
    }
    // não precisa de else porque caso entre no if ja retorna e se não ja ta implicito um else no for
    for (int i = 0; i < tampacientes; i++)
    {
        if (pacientes[i].codigo == codigo)
        {
            return i; // retorna o indice de onde ta o paciente
        }
    }

    return -1;
}

void listarpacientes(Paciente *pacientes, long int tampacientes)
{
    if (pacientes == NULL || tampacientes == 0)
    {
        printf("A lista de pacientes está vazia\n");
        return;
    }
    for (int i = 0; i < tampacientes; i++)
    {
        printf("Codigo:%ld\n", pacientes[i].codigo);
        printf("Nome:%s\n", pacientes[i].nomeCompleto);
        printf("Cpf:%s\n", pacientes[i].cpf);
        printf("Endereço:%s \t %s\t %s \t %s\n", pacientes[i].endereco.estado, pacientes[i].endereco.cidade,
               pacientes[i].endereco.bairro, pacientes[i].endereco.rua);
        printf("Telefone:%s\n", pacientes[i].telefone);
        printf("Data de nascimento:%s\n", pacientes[i].dataNascimento);
        printf("Historico médico:%s\n", pacientes[i].historicoMedico);
    }
    return;
}

Paciente *excluirpaciente(Paciente *pacientes, long int *tampacientes, long int codigo)
{
    int encontrado = -1;
    if (pacientes == NULL || *tampacientes == 0)
    {
        return pacientes; // vazio
    }

    for (int i = 0; i < *tampacientes; i++)
    {
        if (pacientes[i].codigo == codigo)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        return pacientes; // não encontrado
    }

    else
    {
        for (int j = encontrado; j < *tampacientes - 1; j++)
        {
            pacientes[j] = pacientes[j + 1];
        }
        (*tampacientes)--;

        if (*tampacientes == 0)
        {
            free(pacientes);
            return NULL;
        }

        Paciente *aux = realloc(pacientes, (*tampacientes) * sizeof(Paciente));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return pacientes;
        }
        else
        {
            pacientes = aux;
        }
    }

    return pacientes;
}

long int consultapaciente(Paciente *pacientes, long int tampacientes, long int codigo)
{
    if (pacientes == NULL || tampacientes == 0)
    {
        return -1; // vazio
    }
    for (int i = 0; i < tampacientes; i++)
    {
        if (pacientes[i].codigo == codigo)
        {
            return i; // retorna indice
        }
    }
    return -1; // não encontrado
}
