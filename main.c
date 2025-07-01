#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller/biblioteca.h"

int main()
{
    Procedimento *procedimentos = NULL;
    AmbienteMedico *ambientes = NULL;
    Fornecedor *fornecedores = NULL;
    MedicamentoMaterial *medicamentosmateriais = NULL;
    Paciente *pacientes = NULL;
    Profissional *profissionais = NULL;
    Agendamento *agendamentos=NULL;
    long int tamprocedimento = 0, codigoatualprocedimentos = 0, tamambiente = 0, codigoatualambiente = 0,
    tamfornecedor = 0, codigoatualfornecedor= 0, tammedicamentomaterial = 0, codigoatualmedicamentomaterial = 0,
    tampacientes = 0, codigoatualpacientes = 0,tamprofissionais = 0, codigoatualprofissionais = 0,
    tamagendamento=0,codigoatualagendamento=0;
    int op = 0, op2 = 0, oparquivo = 0;
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
        printf("7:Agendar Procedimento/Consulta\n");
        printf("8:Sair\n");
        scanf("%d", &op);

        if (op == 1)
        {
            menuPacientes(&pacientes,&tampacientes,&codigoatualpacientes);
        }
        else if (op == 2)
        {
            menuambientesmedicos(&ambientes, &tamambiente, &codigoatualambiente);
        }
        else if (op == 3)
        {
            menufornecedores(&fornecedores,&tamfornecedor,&codigoatualfornecedor);
        }
        else if (op == 4)
        {
            menumedicamentos_materiais(&medicamentosmateriais,&tammedicamentomaterial,&codigoatualmedicamentomaterial);
        }
        else if (op == 5)
        {
            menuprofisionais(&profissionais,&tamprofissionais,&codigoatualprofissionais);
        }
        else if (op == 6)
        {
            menuprocedimentos(&procedimentos, &tamprocedimento, &codigoatualprocedimentos,ambientes,medicamentosmateriais,tamambiente,tammedicamentomaterial);
        }
        else if (op == 7)
        {
            printf("1:Memoria\n2:Arquivo\n");
            scanf("%d", &op2);
            if (op2 == 1)
            {
                menuagendamento_controle(&agendamentos,&tamagendamento,&codigoatualagendamento,
                procedimentos,tamprocedimento,&medicamentosmateriais,
                tammedicamentomaterial,pacientes,tampacientes,profissionais,tamprofissionais);
            }
            else if (op2 == 2)
            {
                printf("1:Arquivo texto \n 2:Arquivo binario\n");
                scanf("%d", &oparquivo);
                if (oparquivo <= 0 || op > 2)
                {
                    printf("opção de arquivo invalida tente novamente\n");
                }
                else
                {
                    menuagendamento_controle_arquivo(oparquivo);
                }
            }
            else
            {
                printf("opção invalida tente novamente\n");
            }
        }
        else if (op == 8)
        {
            for (int i = 0; i < tamprocedimento; i++){
                free((procedimentos)[i].codmedicamentosemateriais);
            }
            free(procedimentos);
            free(ambientes);
            free(fornecedores);
            free(medicamentosmateriais);
            free(pacientes);
            free(profissionais);
            free(agendamentos);
        }
        else if (op < 1 || op > 8)
        {
            printf("opção inválida, tente novamente\n");
        }

    } while (op != 8);

    return 0;
}