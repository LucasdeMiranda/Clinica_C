#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuPacientes()
{
    Paciente *pacientes = NULL;
    long int tampacientes = 0, codigoatual = 0, codigo;
    int op;

    do
    {
        op = 0, codigo = 0;
        printf("1:Cadastrar paciente\n:");
        printf("2:Alterar paciente\n:");
        printf("3:Excluir paciente\n");
        printf("4:Listar pacientes\n");
        printf("5:Consultar paciente\n");
        printf("6:Sair\n");
        scanf("%d", &op);

        if (op <= 0 || op > 6)
        {
            printf("opção invalida! tente novamente\n");
        }
        else
        {
            if (op == 1)
            {
                pacientes = cadastrarpaciente(pacientes, &tampacientes, &codigoatual);
            }
            else if (op == 2)
            {
                printf("digite o codigo");
                scanf("%ld", &codigo);
                alterarpaciente(pacientes, tampacientes, codigo);
            }
            else if (op == 3)
            {
                printf("digite o código:");
                scanf("%ld", &codigo);
                pacientes = excluirpaciente(pacientes, &tampacientes, codigo);
            }
            else if (op == 4)
            {
                listarpacientes(pacientes, tampacientes);
            }
            else if (op == 5)
            {
                printf("digite o código:");
                scanf("%ld", &codigo);

                consultapaciente(pacientes, tampacientes, codigo);
            }
        }

    } while (op != 6);
    free(pacientes);
}

Paciente *cadastrarpaciente(Paciente *pacientes, long int *tampacientes, long int *codigoatual)
{
    Paciente *novopaciente = realloc(pacientes, (*tampacientes + 1) * sizeof(Paciente)); // usa um ponteiro auxiliar para o caso de não ser bem sucedido
    // não sobrescreve ou perde as informações anteriores por erros de realocação
    if (novopaciente == NULL)
    {
        printf("Erro ao alocar memória\n");
        return pacientes; // Retorna o vetor original caso a alocação falhe
    }

    pacientes = novopaciente;

    pacientes[*tampacientes].codigo = *codigoatual;

    printf("Digite o nome completo: ");
    scanf(" %[^\n]", pacientes[*tampacientes].nomeCompleto);

    printf("Digite o CPF: ");
    scanf(" %[^\n]", &pacientes[*tampacientes].cpf);

    printf("Digite a sigla do estado: ");
    scanf(" %[^\n]", pacientes[*tampacientes].endereco.estado);

    printf("Digite a cidade: ");
    scanf(" %[^\n]", pacientes[*tampacientes].endereco.cidade);

    printf("Digite o bairro: ");
    scanf(" %[^\n]", pacientes[*tampacientes].endereco.bairro);

    printf("Digite a rua: ");
    scanf(" %[^\n]", pacientes[*tampacientes].endereco.rua);

    printf("Digite seu telefone: ");
    scanf(" %[^\n]", pacientes[*tampacientes].telefone);

    printf("Digite sua data de nascimento: ");
    scanf(" %[^\n]", pacientes[*tampacientes].dataNascimento);

    printf("Digite o histórico médico: ");
    scanf(" %[^\n]", pacientes[*tampacientes].historicoMedico);
    printf("Paciente cadastrado com sucesso\n");
    (*tampacientes)++; // Atualiza a quantidade de pacientes
    (*codigoatual)++;
    return pacientes; // Retorna o ponteiro com o novo paciente inserido
}

void alterarpaciente(Paciente *pacientes, long int tampacientes, long int codigo)
{
    if (pacientes == NULL)
    {
        printf("Lista de pacientes vazia");
        return;
    }
    // não precisa de else porque caso entre no if ja retorna e se não ja ta implicito um else no for
    for (int i = 0; i < tampacientes; i++)
    {
        if (pacientes[i].codigo == codigo)
        {

            printf("Digite o nome completo: ");
            scanf(" %[^\n]", pacientes[i].nomeCompleto);

            printf("Digite o CPF: ");
            scanf(" %[^\n]", &pacientes[i].cpf);

            printf("Digite a sigla do estado: ");
            scanf(" %[^\n]", pacientes[i].endereco.estado);

            printf("Digite a cidade: ");
            scanf(" %[^\n]", pacientes[i].endereco.cidade);

            printf("Digite o bairro: ");
            scanf(" %[^\n]", pacientes[i].endereco.bairro);

            printf("Digite a rua: ");
            scanf(" %[^\n]", pacientes[i].endereco.rua);

            printf("Digite seu telefone: ");
            scanf(" %[^\n]", &pacientes[i].telefone);

            printf("Digite sua data de nascimento: ");
            scanf(" %[^\n]", pacientes[i].dataNascimento);

            printf("Digite o histórico médico: ");
            scanf(" %[^\n]", pacientes[i].historicoMedico);
            printf("alteração feita com sucesso\n");
            return;
        }
    }

    printf("Paciente não encontrado\n");
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
        printf("Lista de pacientes vazia.\n");
        return pacientes;
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
        printf(" paciente não encontrado\n");
        return pacientes;
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
            printf("excluido com sucesso\n");
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
            printf("excluido com sucesso\n");
        }
    }

    return pacientes;
}

void consultapaciente(Paciente *pacientes, long int tampacientes, long int codigo)
{
    if (pacientes == NULL || tampacientes == 0)
    {
        printf("Lista de pacientes vazia.\n");
        return;
    }
    for (int i = 0; i < tampacientes; i++)
    {
        if (pacientes[i].codigo == codigo)
        {
            printf("Codigo:%ld\n", pacientes[i].codigo);
            printf("Nome:%s\n", pacientes[i].nomeCompleto);
            printf("Cpf:%s\n", pacientes[i].cpf);
            printf("Endereço:%s \t %s\t %s \t %s\n", pacientes[i].endereco.estado, pacientes[i].endereco.cidade,
                   pacientes[i].endereco.bairro, pacientes[i].endereco.rua);
            printf("Telefone:%s\n", pacientes[i].telefone);
            printf("Data de nascimento:%s\n", pacientes[i].dataNascimento);
            printf("Historico médico:%s\n", pacientes[i].historicoMedico);
            printf("\n");
            return;
        }
    }
    printf("paciente não encontrado\n");
    return;
}
