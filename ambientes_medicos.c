#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuambientesmedicos()
{
    AmbienteMedico *ambientes = NULL;
    long int tamambiente = 0, codigoatual = 0, codigo, auxtam = 0, posicao;
    int op;

    do
    {
        op = 0, posicao = -1;
        printf("1: Cadastrar ambiente\n");
        printf("2: Alterar ambiente\n");
        printf("3: Excluir ambiente\n");
        printf("4: Listar ambientes\n");
        printf("5: Consultar ambientes médicos\n");
        printf("6: Sair\n");
        scanf("%d", &op);

        if (op <= 0 || op > 6)
        {
            printf("Opção inválida! Tente novamente.\n");
        }
        else
        {
            if (op == 1)
            {
                AmbienteMedico novoambiente;
                novoambiente.codigo = codigoatual;
                auxtam = tamambiente;

                printf("Digite a descrição do procedimento: ");
                scanf(" %[^\n]", novoambiente.descricaoProcedimento);

                ambientes = cadastrarambientemedico(ambientes, &tamambiente, &codigoatual, &novoambiente);
                if (tamambiente > auxtam)
                {
                    printf("Ambiente médico cadastrado com sucesso\n");
                }
                else
                {
                    printf("Erro ao cadastrar o ambiente médico.\n");
                }
            }
            else if (op == 2)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);

                posicao = alterarambientemedico(ambientes, tamambiente, codigo);
                if (posicao == -1)
                {
                    printf("Ambiente não encontrado ou lista vazia.\n");
                }
                else
                {
                    printf("Digite a nova descrição do procedimento: ");
                    scanf(" %[^\n]", ambientes[posicao].descricaoProcedimento); // altera direto no vetor

                    printf("Alteração feita com sucesso.\n");
                }
            }
            else if (op == 3)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);
                auxtam = tamambiente;
                ambientes = excluirambientemedico(ambientes, &tamambiente, codigo);

                if (tamambiente < auxtam)
                {
                    printf("Ambiente excluído com sucesso!\n");
                }
                else
                {
                    printf("Ambiente não encontrado para exclusão.\n");
                }
            }
            else if (op == 4)
            {
                listarambiente(ambientes, tamambiente);
            }
            else if (op == 5)
            {
                printf("Digite o código: ");
                scanf("%ld", &codigo);
                posicao = consultaambiente(ambientes, tamambiente, codigo);
                if(posicao==-1){
                    printf("Ambiente não encontrado\n");
                }
                else{
                   printf("Código: %ld\n", ambientes[posicao].codigo);
                printf("Descrição do procedimento: %s\n", ambientes[posicao].descricaoProcedimento);
                }
                 
            }
        }

    } while (op != 6);

    free(ambientes);
}

AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambiente, long int *codigoatual, AmbienteMedico *novoambiente)
{
    AmbienteMedico *novo = realloc(ambientes, (*tamambiente + 1) * sizeof(AmbienteMedico));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return ambientes;
    }

    ambientes = novo;

    // Copia os dados preenchidos no main para a nova posição do vetor
    ambientes[*tamambiente] = *novoambiente;

    (*tamambiente)++;
    (*codigoatual)++;

    return ambientes;
}

long int alterarambientemedico(AmbienteMedico *ambientes, long int tamambiente, long int codigo)
{
    if (ambientes == NULL || tamambiente == 0)
    {
        return -1; // lista vazia
    }
    for (int i = 0; i < tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {
            return i; // retorna a posição
        }
    }
    return -1;
}

void listarambiente(AmbienteMedico *ambientes, long int tamambiente)
{
    if (ambientes == NULL || tamambiente == 0)
    {
        printf("lista de ambientes vazia\n");
        return;
    }
    for (int i = 0; i < tamambiente; i++)
    {
        printf("Código: %ld\n", ambientes[i].codigo);
        printf("Descrição do procedimento: %s\n", ambientes[i].descricaoProcedimento);
    }
    return;
}

AmbienteMedico *excluirambientemedico(AmbienteMedico *ambientes, long int *tamambiente, int codigo)
{
    int encontrado = -1;
    if (ambientes == NULL || *tamambiente == 0)
    {
        return ambientes;
    }

    for (int i = 0; i < *tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        return ambientes;
    }
    else
    {
        for (int j = encontrado; j < *tamambiente - 1; j++)
        {
            ambientes[j] = ambientes[j + 1];
        }
        (*tamambiente)--;

        if (*tamambiente == 0)
        {
            free(ambientes);
            return NULL;
        }
        AmbienteMedico *aux = realloc(ambientes, (*tamambiente) * sizeof(AmbienteMedico));
        if (aux == NULL)
        {
            printf("erro ao realocar memoria\n");
            return ambientes;
        }
        else
        {
            ambientes = aux;
        }
    }
    return ambientes;
}

long int consultaambiente(AmbienteMedico *ambientes, long int tamambiente, long int codigo)
{
    if (ambientes == NULL || tamambiente == 0)
    {

        return -1;
    }
    for (int i = 0; i < tamambiente; i++)
    {
        if (ambientes[i].codigo == codigo)
        {

            return i;
        }
    }

    return -1;
}