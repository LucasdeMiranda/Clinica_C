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
    Agendamento *agendamentos = NULL;
    long int tamprocedimento = 0, codigoatualprocedimentos = 0, tamambiente = 0, codigoatualambiente = 0,
             tamfornecedor = 0, codigoatualfornecedor = 0, tammedicamentomaterial = 0, codigoatualmedicamentomaterial = 0,
             tampacientes = 0, codigoatualpacientes = 0, tamprofissionais = 0, codigoatualprofissionais = 0,
             tamagendamento = 0, codigoatualagendamento = 0;
    int op1, op2,leitura;

    char *agendamentostxt = "agendamentos.txt", ambientestxt = "ambientes.txt", 
    *fornecedorestxt = "fornecedores.txt", *medicamentosmateriaistxt = "medicamentosmateriais.txt", 
    *pacientestxt = "pacientes.txt", *procedimentostxt = "procedimentos.txt", 
    *profissionaistxt = "profissionais.txt",
     *agendamentosbin = "agendamentos.bin", *ambientesbin = "ambientes.bin", *fornecedoresbin = "fornecedores.bin",
     *medicamentosmateriaisbin = "medicamentosmateriais.bin", *pacientesbin = "pacientes.bin", 
     *procedimentosbin = "procedimentos.bin", *profissionaisbin = "profissionais.bin", *nome="arquivo.xml";

    do
    {

        printf("Bem Vindo\n");
        printf("Selecione qual aréa do sistema desesja acessar\n");
        printf("1:Pacientes\n");
        printf("2:Ambientes Medicos\n");
        printf("3:Fornecedores\n");
        printf("4:Medicamentos e Materiais\n");
        printf("5:Profisionais\n");
        printf("6:Procedimentos\n");
        printf("7:Agendar Procedimento/Consulta\n");
        printf("8:Importar dados\n");
        printf("9:Exportar dados\n");
        printf("10:Sair\n");
        scanf("%d", &op2);

        if (op2 == 1)
        {
            menupacientes(&pacientes, &tampacientes, &codigoatualpacientes);
        }
        else if (op2 == 2)
        {
            menuambientesmedicos(&ambientes, &tamambiente, &codigoatualambiente);
        }
        else if (op2 == 3)
        {
            menufornecedores(&fornecedores, &tamfornecedor, &codigoatualfornecedor);
        }
        else if (op2 == 4)
        {
            menumedicamentos_materiais(&medicamentosmateriais, &tammedicamentomaterial, &codigoatualmedicamentomaterial);
        }
        else if (op2 == 5)
        {
            menuprofisionais(&profissionais, &tamprofissionais, &codigoatualprofissionais);
        }
        else if (op2 == 6)
        {
            menuprocedimentos(&procedimentos, &tamprocedimento, &codigoatualprocedimentos, ambientes, medicamentosmateriais, tamambiente, tammedicamentomaterial);
        }
        else if (op2 == 7)
        {
            menuagendamento_controle(&agendamentos, &tamagendamento, &codigoatualagendamento,
                                     procedimentos, tamprocedimento, &medicamentosmateriais,
                                     tammedicamentomaterial, pacientes, tampacientes, profissionais, tamprofissionais);
        }
        else if (op2 == 8)
        {
            printf("1:Pacientes\n");
            printf("2:Ambientes Medicos\n");
            printf("3:Fornecedores\n");
            printf("4:Medicamentos e Materiais\n");
            printf("5:Profisionais\n");
            printf("6:Procedimentos\n");
            printf("7:Procedimento/Consulta\n");
            scanf("%d", &op1);
            if (op1 < 1 || op1 > 7)
            {
                printf("opção inválida, tente novamente\n");
            }
            else if (op1 == 1)
            {
               leitura=importarpaciente(&pacientes,nome,&tampacientes,&codigoatualpacientes);
               if(leitura==-1){
                printf("erro ao importar\n");
               }
               else{
                printf("pacientes importados com sucesso\n");
               }
            }
        }
        else if (op2 == 10)
        {
            for (int i = 0; i < tamprocedimento; i++)
            {
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
        else if (op2 < 1 || op2 > 10)
        {
            printf("opção inválida, tente novamente\n");
        }

    } while (op2 != 10);

    return 0;
}