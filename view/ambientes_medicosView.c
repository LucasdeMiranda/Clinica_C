#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuambientesmedicos()
{
    AmbienteMedico *ambientes = NULL;
    long int tamambiente = 0, codigoatual = 0, codigo, auxtam = 0, posicao;//auxtam vai guardar uma copia do tamnho do betor que será muito util
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
                auxtam = tamambiente;

                printf("Digite a descrição do procedimento: ");
                scanf(" %999[^\n]", novoambiente.descricaoProcedimento);

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
                    scanf(" %999[^\n]", ambientes[posicao].descricaoProcedimento); // altera direto no vetor

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
