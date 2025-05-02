#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuPacientes()
{
    Paciente *pacientes = NULL;
    long int tampacientes = 0;
    int op, cpf;

    do
    {
        op = 0, cpf = 0;
        printf("1:Cadastrar paciente\n:");
        printf("2:Alterar paciente\n:");
        printf("3: Excluir paciente");
        printf("4:Listar pacientes");
        printf("5:Sair");
        scanf("%d", &op);

        if (op <= 0 && op > 5)
        {
            printf("opção invalida! tente novamente");
        }
        else
        {
            if (op == 1)
            {
                cadastrarpaciente(pacientes, &tampacientes);
            }
            else if (op == 2)
            {
                printf("digite o cpf");
                scanf("%d", &cpf);
                pacientes = alterercliente(pacientes, tampacientes, cpf);
            }
        }

    } while (op != 5);
}

Paciente *cadastrarpaciente(Paciente *pacientes, long int *tampacientes)
{
    Paciente *novopaciente = realloc(pacientes, (*tampacientes + 1) * sizeof(Paciente));
    if (novopaciente == NULL)
    {
        printf("Erro ao alocar memória\n");
        return pacientes; // Retorna o vetor original caso a alocação falhe
    }

    pacientes = novopaciente;

    printf("Digite o código: ");
    scanf("%d", &pacientes[*tampacientes].codigo);

    printf("Digite o nome completo: ");
    scanf(" %[^\n]", pacientes[*tampacientes].nomeCompleto);

    printf("Digite o CPF: ");
    scanf("%d", &pacientes[*tampacientes].cpf);

    printf("Digite a sigla do estado: ");
    scanf(" %[^\n]", pacientes[*tampacientes].endereco.estado);

    printf("Digite a cidade: ");
    scanf(" %[^\n]", pacientes[*tampacientes].endereco.cidade);

    printf("Digite o bairro: ");
    scanf(" %[^\n]", pacientes[*tampacientes].endereco.bairro);

    printf("Digite a rua: ");
    scanf(" %[^\n]", pacientes[*tampacientes].endereco.rua);

    printf("Digite seu telefone: ");
    scanf("%d", &pacientes[*tampacientes].telefone);

    printf("Digite sua data de nascimento: ");
    scanf(" %[^\n]", pacientes[*tampacientes].dataNascimento);

    printf("Digite o histórico médico: ");
    scanf(" %[^\n]", pacientes[*tampacientes].historicoMedico);

    (*tampacientes)++; // Atualiza a quantidade de pacientes
    return pacientes;  // Retorna o ponteiro com o novo paciente inserido
}

Paciente *altererpaciente(Paciente *pacientes, long int *tampacientes, int cpf)
{
    if (pacientes == NULL)
    {
        printf("Lista de pacientes vazia");
        return pacientes;
    }
    else
    {
        for (int i = 0; i < *tampacientes; i++)
        {
            if (pacientes[i].cpf == cpf)
            {
                printf("Digite o código: ");
                scanf("%d", &pacientes[i].codigo);

                printf("Digite o nome completo: ");
                scanf(" %[^\n]", pacientes[i].nomeCompleto);

                printf("Digite o CPF: ");
                scanf("%d", &pacientes[i].cpf);

                printf("Digite a sigla do estado: ");
                scanf(" %[^\n]", pacientes[i].endereco.estado);

                printf("Digite a cidade: ");
                scanf(" %[^\n]", pacientes[i].endereco.cidade);

                printf("Digite o bairro: ");
                scanf(" %[^\n]", pacientes[i].endereco.bairro);

                printf("Digite a rua: ");
                scanf(" %[^\n]", pacientes[i].endereco.rua);

                printf("Digite seu telefone: ");
                scanf("%d", &pacientes[i].telefone);

                printf("Digite sua data de nascimento: ");
                scanf(" %[^\n]", pacientes[i].dataNascimento);

                printf("Digite o histórico médico: ");
                scanf(" %[^\n]", pacientes[i].historicoMedico);
            }
        }
    }
    return pacientes;
}
