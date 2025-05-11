#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuPacientes()
{
    Paciente *pacientes = NULL;
    long int tampacientes = 0, codigoatual=0;
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
                pacientes=cadastrarpaciente(pacientes, &tampacientes,&codigoatual);
            }
            else if (op == 2)
            {
                printf("digite o cpf");
                scanf("%d", &cpf);
             alterercliente(&pacientes, &tampacientes, cpf);
            }
            else if(op==3){

            }
            else if(op==4){
                listarpacientes(pacientes,tampacientes);
            }
        }

    } while (op != 5);
}

Paciente *cadastrarpaciente(Paciente *pacientes, long int *tampacientes,long int *codigoatual)
{
    Paciente *novopaciente = realloc(pacientes, (*tampacientes + 1) * sizeof(Paciente));//usa um ponteiro auxiliar para o caso de não ser bem sucedido
    //não sobrescreve ou perde as informações anteriores por erros de realocação
    if (novopaciente == NULL)
    {
        printf("Erro ao alocar memória\n");
        return pacientes; // Retorna o vetor original caso a alocação falhe
    }

    pacientes = novopaciente;

     pacientes[*tampacientes].codigo=*codigoatual;
      

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
    (*codigoatual)++;
    return pacientes;  // Retorna o ponteiro com o novo paciente inserido
}

 void alterarpaciente(Paciente *pacientes, long int *tampacientes, int cpf)
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

void listarpacientes( Paciente *pacientes, long int *tampacientes){
  for(int i=0;i<*tampacientes;i++){
    printf("Codigo:%ld\n",pacientes[i].codigo);
    printf("Nome:%s\n",pacientes[i].nomeCompleto);
    printf("Cpf:%d\n",pacientes[i].cpf);
    printf("Endereço:%s \t %s\t %s \t %s\n",pacientes[i].endereco.estado,pacientes[i].endereco.cidade,
        pacientes[i].endereco.bairro,pacientes[i].endereco.rua);
    printf("Telefone:%ld\n",pacientes[i].telefone);
    printf("Data de nascimento:%s\n",pacientes[i].dataNascimento);
    printf("Historico médico:%s\n",pacientes[i].historicoMedico);
  }
}
