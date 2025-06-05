#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller/biblioteca.h"

int main()
{
    int op;
    do
    {
        printf("Bem vindo\n");
        printf("Selecione qual aréa do sistema desesja acessar\n");
        printf("1:Pacientes\n");
        printf("2:Ambientes Medicos\n");
        printf("3:Fornecedores\n");
        printf("4:Medicamentos e Materiais\n");
        printf("5:Profisionais\n");
        printf("6:Procedimentos\n");
        printf("7:Sair\n");
        scanf("%d", &op);

        if (op == 1)
        {
            menuPacientes();
        }
        else if (op == 2)
        {
            menuambientesmedicos();
        }
        else if (op == 3)
        {
            menufornecedores();
        }
        else if (op == 4)
        {
            menumedicamentos_materiais();
        }
        else if (op == 5)
        {
            menuprofisionais();
        }
        else if (op == 6)
        {
            menuprocedimentos();
        }
        else if (op < 1 || op > 7)
        {
            printf("opção inválida, tente novamente\n");
        }

    } while (op != 7);

    return 0;
}
