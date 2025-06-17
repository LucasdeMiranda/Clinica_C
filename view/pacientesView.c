#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuPacientes(Paciente **pacientes, long int *tampacientes, long int *codigoatual)
{
    long int codigo, posicao, auxtam = 0;
    int op;

    do
    {
        op = 0, codigo = 0;
        printf("1: Cadastrar paciente\n");
        printf("2: Alterar paciente\n");
        printf("3: Excluir paciente\n");
        printf("4: Listar pacientes\n");
        printf("5: Consultar paciente\n");
        printf("6: Sair\n");
        scanf("%d", &op);

        if (op <= 0 || op > 6)
        {
            printf("Opção inválida! Tente novamente\n");
        }
        else
        {
            if (op == 1)
            {
                Paciente novopaciente;
                auxtam = *tampacientes;

                printf("Digite o nome completo: ");
                scanf(" %199[^\n]", novopaciente.nomeCompleto);

                printf("Digite o CPF: ");
                scanf(" %49[^\n]", novopaciente.cpf);

                printf("Digite a sigla do estado: ");
                scanf(" %9[^\n]", novopaciente.endereco.estado);

                printf("Digite a cidade: ");
                scanf(" %199[^\n]", novopaciente.endereco.cidade);

                printf("Digite o bairro: ");
                scanf(" %199[^\n]", novopaciente.endereco.bairro);

                printf("Digite a rua: ");
                scanf(" %199[^\n]", novopaciente.endereco.rua);

                printf("Digite seu telefone: ");
                scanf(" %19[^\n]", novopaciente.telefone);

                printf("Digite sua data de nascimento: ");
                scanf(" %39[^\n]", novopaciente.dataNascimento);

                printf("Digite o histórico médico: ");
                scanf(" %1999[^\n]", novopaciente.historicoMedico);

                *pacientes = cadastrarpaciente(*pacientes, tampacientes, codigoatual, &novopaciente);

                if (*tampacientes > auxtam)
                {
                    printf("Paciente cadastrado com sucesso\n");
                }
                else
                {
                    printf("Erro ao cadastrar paciente\n");
                }
            }
            else if (op == 2)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                posicao = alterarpaciente(*pacientes, *tampacientes, codigo);

                if (posicao == -1)
                {
                    printf("Paciente não encontrado ou lista vazia\n");
                }
                else
                {
                    printf("Digite o nome completo: ");
                    scanf(" %199[^\n]", (*pacientes)[posicao].nomeCompleto);

                    printf("Digite o CPF: ");
                    scanf(" %49[^\n]", (*pacientes)[posicao].cpf);

                    printf("Digite a sigla do estado: ");
                    scanf(" %9[^\n]", (*pacientes)[posicao].endereco.estado);

                    printf("Digite a cidade: ");
                    scanf(" %199[^\n]", (*pacientes)[posicao].endereco.cidade);

                    printf("Digite o bairro: ");
                    scanf(" %199[^\n]", (*pacientes)[posicao].endereco.bairro);

                    printf("Digite a rua: ");
                    scanf(" %199[^\n]", (*pacientes)[posicao].endereco.rua);

                    printf("Digite seu telefone: ");
                    scanf(" %19[^\n]", (*pacientes)[posicao].telefone);

                    printf("Digite sua data de nascimento: ");
                    scanf(" %39[^\n]", (*pacientes)[posicao].dataNascimento);

                    printf("Digite o histórico médico: ");
                    scanf(" %1999[^\n]", (*pacientes)[posicao].historicoMedico);

                    printf("Alteração feita com sucesso\n");
                }
            }
            else if (op == 3)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                auxtam = *tampacientes;

                *pacientes = excluirpaciente(*pacientes, tampacientes, codigo);

                if (*tampacientes < auxtam)
                {
                    printf("Paciente excluído com sucesso\n");
                }
                else
                {
                    printf("Paciente não encontrado\n");
                }
            }
            else if (op == 4)
            {
                listarpacientes(*pacientes, *tampacientes);
            }
            else if (op == 5)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                posicao = consultapaciente(*pacientes, *tampacientes, codigo);

                if (posicao == -1)
                {
                    printf("Paciente não encontrado\n");
                }
                else
                {
                    printf("Código: %ld\n", (*pacientes)[posicao].codigo);
                    printf("Nome: %s\n", (*pacientes)[posicao].nomeCompleto);
                    printf("CPF: %s\n", (*pacientes)[posicao].cpf);
                    printf("Endereço: %s \t %s \t %s \t %s\n", (*pacientes)[posicao].endereco.estado,
                           (*pacientes)[posicao].endereco.cidade,
                           (*pacientes)[posicao].endereco.bairro,
                           (*pacientes)[posicao].endereco.rua);
                    printf("Telefone: %s\n", (*pacientes)[posicao].telefone);
                    printf("Data de nascimento: %s\n", (*pacientes)[posicao].dataNascimento);
                    printf("Histórico médico: %s\n", (*pacientes)[posicao].historicoMedico);
                }
            }
        }

    } while (op != 6);
}
