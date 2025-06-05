#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view/biblioteca.h"

void menuPacientes()
{
    Paciente *pacientes = NULL;
    long int tampacientes = 0, codigoatual = 0, codigo, posicao, auxtam = 0;
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
                Paciente novopaciente;
                 auxtam=tampacientes;
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

                pacientes = cadastrarpaciente(pacientes, &tampacientes, &codigoatual, &novopaciente);

                if (tampacientes > auxtam)
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
                printf("digite o codigo");
                scanf("%ld", &codigo);
                posicao = alterarpaciente(pacientes, tampacientes, codigo);
                if (posicao == -1)
                {
                    printf("Paciente não encontrado ou lista vazia\n");
                }
                else
                {
                    printf("Digite o nome completo: ");
                    scanf(" %199[^\n]", pacientes[posicao].nomeCompleto);

                    printf("Digite o CPF: ");
                    scanf(" %49[^\n]",pacientes[posicao].cpf);

                    printf("Digite a sigla do estado: ");
                    scanf(" %9[^\n]", pacientes[posicao].endereco.estado);

                    printf("Digite a cidade: ");
                    scanf(" %199[^\n]", pacientes[posicao].endereco.cidade);

                    printf("Digite o bairro: ");
                    scanf(" %199[^\n]", pacientes[posicao].endereco.bairro);

                    printf("Digite a rua: ");
                    scanf(" %199[^\n]", pacientes[posicao].endereco.rua);

                    printf("Digite seu telefone: ");
                    scanf(" %19[^\n]",pacientes[posicao].telefone);

                    printf("Digite sua data de nascimento: ");
                    scanf(" %39[^\n]", pacientes[posicao].dataNascimento);

                    printf("Digite o histórico médico: ");
                    scanf(" %1999[^\n]", pacientes[posicao].historicoMedico);
                    printf("alteração feita com sucesso\n");
                }
            }
            else if (op == 3)
            {
                printf("digite o código:");
                scanf("%ld", &codigo);
                auxtam = tampacientes;
                pacientes = excluirpaciente(pacientes, &tampacientes, codigo);
                if (tampacientes < auxtam)
                {
                    printf(" Paciente excluido com sucesso\n");
                }
                else
                {
                    printf("Paciente não encontrado\n");
                }
            }
            else if (op == 4)
            {
                listarpacientes(pacientes, tampacientes);
            }
            else if (op == 5)
            {
                printf("digite o código:");
                scanf("%ld", &codigo);

                posicao = consultapaciente(pacientes, tampacientes, codigo);

                if (posicao == -1)
                {
                    printf("paciente não encontrado\n");
                }
                else
                {
                    printf("Codigo:%ld\n", pacientes[posicao].codigo);
                    printf("Nome:%s\n", pacientes[posicao].nomeCompleto);
                    printf("Cpf:%s\n", pacientes[posicao].cpf);
                    printf("Endereço:%s \t %s\t %s \t %s\n", pacientes[posicao].endereco.estado, pacientes[posicao].endereco.cidade,
                           pacientes[posicao].endereco.bairro, pacientes[posicao].endereco.rua);
                    printf("Telefone:%s\n", pacientes[posicao].telefone);
                    printf("Data de nascimento:%s\n", pacientes[posicao].dataNascimento);
                    printf("Historico médico:%s\n", pacientes[posicao].historicoMedico);
                }
            }
        }

    } while (op != 6);
    free(pacientes);
}

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
