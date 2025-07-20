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
        printf("Endereço:%s \t %s\t %s \t %s %ld\n", pacientes[i].endereco.estado, pacientes[i].endereco.cidade,
               pacientes[i].endereco.bairro, pacientes[i].endereco.rua, pacientes[i].endereco.numero);
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

long int importarpaciente(Paciente **pacientes, char *nome, long int *tampacientes, long int *codigoatual)
{
    char linha[1000];
    FILE *arquivo = fopen(nome, "r");
    char enderco[1000], *token; // token será usado para repartir a string de endereco
    if (arquivo == NULL)
    {
        return -1;
    }

    Paciente novopaciente;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {

        if (strstr(linha, "<tabela nome=\"paciente\">") != NULL)
        {
            // A partir daqui, processamos os registros de paciente
            while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</tabela>") == NULL)
            {
                if (strstr(linha, "<codigo>") != NULL)
                {
                    sscanf(linha, "<codigo>%ld</codigo>", &novopaciente.codigo);
                }

                if (strstr(linha, "<nome>") != NULL)
                {
                    sscanf(linha, "<nome>%199[^<]</nome>", novopaciente.nomeCompleto);
                }

                if (strstr(linha, "<cpf>") != NULL)
                {
                    sscanf(linha, "<cpf>%49[^<]</cpf>", novopaciente.cpf);
                }

                if (strstr(linha, "<telefone>") != NULL)
                {
                    sscanf(linha, "<telefone>%19[^<]</telefone>", novopaciente.telefone);
                }

                if (strstr(linha, "<endereco>") != NULL)
                {
                    sscanf(linha, "<endereco>%[^<]</endereco>", enderco);
                    token = strtok(enderco, ","); // Rua
                    if (token != NULL)
                    {
                        strncpy(novopaciente.endereco.rua, token, sizeof(novopaciente.endereco.rua));
                    }

                    token = strtok(NULL, ","); // Número
                    if (token != NULL)
                    {
                        novopaciente.endereco.numero = strtol(token, NULL, 10); // serve pra tranformar string em numero
                        // o ultimo parametro é a base do numero
                    }

                    token = strtok(NULL, ","); // Bairro
                    if (token != NULL)
                    {
                        strncpy(novopaciente.endereco.bairro, token, sizeof(novopaciente.endereco.bairro));
                    }

                    token = strtok(NULL, ","); // Cidade
                    if (token != NULL)
                    {
                        strncpy(novopaciente.endereco.cidade, token, sizeof(novopaciente.endereco.cidade));
                    }

                    token = strtok(NULL, ","); // Estado
                    if (token != NULL)
                    {
                        strncpy(novopaciente.endereco.estado, token, sizeof(novopaciente.endereco.estado));
                    }
                }

                if (strstr(linha, "<data_nascimento>") != NULL)
                {
                    sscanf(linha, "<data_nascimento>%10[^<]</data_nascimento>", novopaciente.dataNascimento);
                }

                if (strstr(linha, "<historico>") != NULL)
                {
                    sscanf(linha, "<historico>%199[^<]</historico>", novopaciente.historicoMedico);
                }

                if (strstr(linha, "</registro>") != NULL)
                {
                    *pacientes = cadastrarpaciente(*pacientes, tampacientes, codigoatual, &novopaciente);
                }
            }
            break;
        }
    }

    fclose(arquivo);
    return 0;
}

long int exportarpaciente(Paciente *pacientes, char *nome, long int tampacientes)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
    {
        return -1;
    }

    if (pacientes == NULL)
    {
        fclose(arquivo);
        return -1;
    }

    fprintf(arquivo, "<dados>\n");
    fprintf(arquivo, "<!-- Tabela de Pacientes -->\n");
    fprintf(arquivo, "<tabela nome=\"paciente\">\n");

    for (long int i = 0; i < tampacientes; i++)
    {
        fprintf(arquivo, "<registro>\n");
        fprintf(arquivo, "<codigo>%ld</codigo>\n", pacientes[i].codigo);
        fprintf(arquivo, "<nome>%s</nome>\n", pacientes[i].nomeCompleto);
        fprintf(arquivo, "<cpf>%s</cpf>\n", pacientes[i].cpf);
        fprintf(arquivo, "<telefone>%s</telefone>\n", pacientes[i].telefone);
        fprintf(arquivo, "<endereco>%s,%ld,%s,%s,%s</endereco>\n",
                pacientes[i].endereco.rua,
                pacientes[i].endereco.numero,
                pacientes[i].endereco.bairro,
                pacientes[i].endereco.cidade,
                pacientes[i].endereco.estado);
        fprintf(arquivo, "<data_nascimento>%s</data_nascimento>\n", pacientes[i].dataNascimento);
        fprintf(arquivo, "<historico>%s</historico>\n", pacientes[i].historicoMedico);
        fprintf(arquivo, "</registro>\n");
    }

    fprintf(arquivo, "</tabela>\n");
    fprintf(arquivo, "</dados>\n");

    fclose(arquivo);
    return 0; // sucesso ao exportar
}

// essa função vai ser a responsavel por abrir o arquivo txt joga pra memoria
long int importarpacientetxt(Paciente **pacientes, long int *tampacientes, long int *codigoatual, char *nome)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1;
    }

    char linha[1024];
    Paciente novopaciente;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        char *token = strtok(linha, ";");
        if (token != NULL)
            novopaciente.codigo = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novopaciente.nomeCompleto, token, sizeof(novopaciente.nomeCompleto));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novopaciente.cpf, token, sizeof(novopaciente.cpf));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novopaciente.endereco.rua, token, sizeof(novopaciente.endereco.rua));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novopaciente.endereco.bairro, token, sizeof(novopaciente.endereco.bairro));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novopaciente.endereco.cidade, token, sizeof(novopaciente.endereco.cidade));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novopaciente.endereco.estado, token, sizeof(novopaciente.endereco.estado));

        token = strtok(NULL, ";");
        if (token != NULL)
            novopaciente.endereco.numero = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novopaciente.telefone, token, sizeof(novopaciente.telefone));

        token = strtok(NULL, ";");
        if (token != NULL)
            strncpy(novopaciente.dataNascimento, token, sizeof(novopaciente.dataNascimento));

        token = strtok(NULL, ";\n");
        if (token != NULL)
            strncpy(novopaciente.historicoMedico, token, sizeof(novopaciente.historicoMedico));

        *pacientes = cadastrarpaciente(*pacientes, tampacientes, codigoatual, &novopaciente);
    }

    fclose(arquivo);
    return 0;
}

void exportarpacientetxt(Paciente *pacientes, char *nome, long int tampacientes)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL)
    {
        return; // erro
    }

    for (long int i = 0; i < tampacientes; i++)
    {
        fprintf(arquivo, "%ld;%s;%s;%s;%s;%s;%s;%ld;%s;%s;%s\n",
                pacientes[i].codigo,
                pacientes[i].nomeCompleto,
                pacientes[i].cpf,
                pacientes[i].endereco.rua,
                pacientes[i].endereco.bairro,
                pacientes[i].endereco.cidade,
                pacientes[i].endereco.estado,
                pacientes[i].endereco.numero,
                pacientes[i].telefone,
                pacientes[i].dataNascimento,
                pacientes[i].historicoMedico);
    }

    fclose(arquivo);
}
