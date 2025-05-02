#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuprofisionais()
{
    Profissional *profisionais=NULL;
    long int tamprocedimento = 0;
    int op, cpf;

    do
    {
        op = 0, cpf = 0;
        printf("1:Cadastrar profisional\n:");
        printf("2:Alterar profisional\n:");
        printf("3: Excluir profisional");
        printf("4:Listar profisionais");
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
                  
            }
            else if (op == 2)
            {
            }
            else if (op == 3)
            {
            }
            else if (op == 4)
            {
            }
        }

    } while (op != 5);
}
Profissional* cadastrarprofissionalsaude(Profissional *profissionais, long int *tamprocedimento) {
    Profissional *novo = realloc(profissionais, (*tamprocedimento + 1) * sizeof(Profissional));
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return profissionais;
    }

    profissionais = novo;

    printf("Digite o código: ");
    scanf("%d", &profissionais[*tamprocedimento].codigo);

    printf("Digite o nome completo: ");
    scanf(" %[^\n]", profissionais[*tamprocedimento].nomeCompleto);

    printf("Digite o CRM: ");
    scanf(" %[^\n]", profissionais[*tamprocedimento].crm);

    printf("Digite a especialidade: ");
    scanf(" %[^\n]", profissionais[*tamprocedimento].especialidade);

    printf("Digite o CPF: ");
    scanf(" %[^\n]", profissionais[*tamprocedimento].cpf);

    printf("Digite o telefone: ");
    scanf(" %[^\n]", profissionais[*tamprocedimento].telefone);

    printf("Digite o email: ");
    scanf(" %[^\n]", profissionais[*tamprocedimento].email);

    (*tamprocedimento)++;
    return profissionais;
}
