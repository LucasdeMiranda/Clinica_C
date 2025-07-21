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
    Entradaestoque *entradaestoque = NULL;
    LacamentosRetiradas *lacamentosretiradas = NULL;
    Receber *receber = NULL;

    long int tamprocedimento = 0, codigoatualprocedimentos = 0, tamambiente = 0, codigoatualambiente = 0,
             tamfornecedor = 0, codigoatualfornecedor = 0, tammedicamentomaterial = 0, codigoatualmedicamentomaterial = 0,
             tampacientes = 0, tamentradaestoque = 0, codigoatualentradaestoque=0,codigoatualpacientes = 0, tamprofissionais = 0, codigoatualprofissionais = 0,
             tamagendamento = 0, codigoatualagendamento = 0, tamlancamentosretiradas = 0, tamreceber = 0, codigoatualreceber = 0;

    int op1, op2, leitura, oparma, r,p,a,f,m,pro,ag,en,lan,pf;

    char *agendamentostxt = "agendamentos.txt", *ambientestxt="ambientes.txt",
         *fornecedorestxt = "fornecedores.txt", *medicamentosmateriaistxt = "medicamentosmateriais.txt",
         *pacientestxt = "pacientes.txt", *procedimentostxt = "procedimentos.txt", *receberbin="contasreceber.bin", *entradaestoquebin="entradaestoque.bin",
         *profissionaistxt = "profissionais.txt",*recebertxt="contasreceber.txt",
          *ambientesbin = "ambientes.bin", *fornecedoresbin = "fornecedores.bin", *agendamentobin="agendamentos.bin",
         *medicamentosmateriaisbin = "medicamentosmateriais.bin", *pacientesbin = "pacientes.bin", *lancamentoretiradastxt="lancamentoseretiradas.txt", *lancamentosretiradasbin="lancamentoseretiradas.bin",
         *procedimentosbin = "procedimentos.bin", *entradaestoquetxt="entradaestoque.txt",
         *profissionaisbin = "profissionais.bin", *nome = "arquivo.xml", *pacientexml = "paciente.xml", *relatorio = "relatorio.csv",
         *ambientesmedicosxml = "ambientes.xml", *fornecedoresxml = "fornecedores.xml", *medicamentosxml = "medicamentos.xml",
         *profissionaisxml = "profissionais.xml", *agendamentosxml = "agendamentos.xml", *procedimentosxml = "procedimentos.xml";

    float saldototal = 10000; // saldo total disponivel no caixa ja coloquei um saldo incial para testes

    do
    {
        printf("Escolha o modo de armazenamento:\n");
        printf("1: Memoria\n2: Arquivo txt\n3: Arquivo bin\n4: Sair\n");
        scanf("%d", &oparma);
        if (oparma < 1 || oparma > 4)
        {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (oparma < 1 || oparma > 4);

    if (oparma == 4)
    {
        printf("Encerrando programa.\n");
        return 0;
    }

    // Faz a leitura inicial conforme o modo escolhido
    if (oparma == 2)
    {
        p=importarpacientetxt(&pacientes, &tampacientes, &codigoatualpacientes, pacientestxt);
        f=importarfornecedortxt(&fornecedores,&tamfornecedor,&codigoatualfornecedor,fornecedorestxt);
        m=importarmedicamentotxt(&medicamentosmateriais,&tammedicamentomaterial,&codigoatualmedicamentomaterial,medicamentosmateriaistxt);
        pf=importarprofissionaltxt(&profissionais,&tamprofissionais,&codigoatualprofissionais,profissionaistxt);
        a=importarambientemedicotxt(&ambientes,&tamambiente,&codigoatualambiente,ambientestxt);
        pro=importarprocedimentotxt(&procedimentos,&tamprocedimento,&codigoatualprocedimentos,ambientes,medicamentosmateriais,tamambiente,tammedicamentomaterial,procedimentostxt);
        ag=importaragendamentotxt(&agendamentos,&tamagendamento,&codigoatualagendamento,agendamentostxt,pacientes,tampacientes,profissionais,tamprofissionais,procedimentos,tamprocedimento,medicamentosmateriais,tammedicamentomaterial);
        r=importarrecebertxt(&receber,&tamreceber,&codigoatualreceber,recebertxt,agendamentos,tamagendamento,procedimentos,tamprocedimento);
        en=importarentradaestoquetxt(&entradaestoque,&tamentradaestoque,&codigoatualentradaestoque,medicamentosmateriais,tammedicamentomaterial,entradaestoquetxt);
        lan= importarlancamentosretiradastxt(&lacamentosretiradas,&tamlancamentosretiradas,agendamentos,tamagendamento,procedimentos,tamprocedimento,&saldototal,entradaestoque,tamentradaestoque,lancamentoretiradastxt);
        if (p == -1)
        {
            printf("Erro ao abrir arquivo de pacientes\n");
        }
        else
        {
            printf("Pacientes carregados com sucesso do TXT\n");
        }
        
        if (f == -1)
        {
            printf("Erro ao abrir arquivo de  fornecedores\n");
        }
        else
        {
            printf("fornecedores carregados com sucesso do TXT\n");
        }
          if (m == -1)
        {
            printf("Erro ao abrir arquivo de  medicamentos\n");
        }
        else
        {
            printf("medicamentos carregados com sucesso do TXT\n");
        }

         if (pf == -1)
        {
            printf("Erro ao abrir arquivo de  profissionais \n");
        }
        else
        {
            printf("profissionais carregados com sucesso do TXT\n");
        }

        if (a == -1)
        {
            printf("Erro ao abrir arquivo de  ambientes \n");
        }
        else
        {
            printf("ambientes carregados com sucesso do TXT\n");
        }
        if (pro == -1)
        {
            printf("Erro ao abrir arquivo de  procedimentos \n");
        }
        else
        {
            printf("procedimentos carregados com sucesso do TXT\n");
        }
         if (ag == -1)
        {
            printf("Erro ao abrir arquivo de  agendamentos \n");
        }
        else
        {
            printf("agendamentos carregados com sucesso do TXT\n");
        }

          if (r == -1)
        {
            printf("Erro ao abrir arquivo de  contas a receber \n");
        }
        else
        {
            printf("receber carregados com sucesso do TXT\n");
        }

         if (en == -1)
        {
            printf("Erro ao abrir arquivo de  entrada estoque \n");
        }
        else
        {
            printf("entrada estoque carregados com sucesso do TXT\n");
        }
         if (lan == -1)
        {
            printf("Erro ao abrir arquivo de lançamentos e entradas \n");
        }
        else
        {
            printf(" lancamentos e entradas carregados com sucesso do TXT\n");
        }
        
        
        

    }
    else if(oparma==3){
        p=importarpacientebin(&pacientes,&tampacientes,&codigoatualpacientes,pacientesbin);
        f=importarfornecedorbin(&fornecedores,&tamfornecedor,&codigoatualfornecedor,fornecedoresbin);
        m=importarmedicamentomaterialbin(&medicamentosmateriais,&tammedicamentomaterial,&codigoatualmedicamentomaterial,medicamentosmateriaisbin);
        pf=importarprofissionalbin(&profissionais,&tamprofissionais,&codigoatualprofissionais,profissionaisbin);
        a=importarambientemedicobin(&ambientes,&tamambiente,&codigoatualambiente,ambientesbin);
        pro= importarprocedimentobin(&procedimentos,&tamprocedimento,&codigoatualprocedimentos,procedimentosbin,ambientes,tamambiente,medicamentosmateriais,tammedicamentomaterial);
        r=importarreceberbin(&receber,&tamreceber,&codigoatualreceber,receberbin,agendamentos,tamagendamento,procedimentos,tamprocedimento);
        en=importarentradaestoquebin(&entradaestoque,&tamentradaestoque,&codigoatualentradaestoque,entradaestoquebin,medicamentosmateriais,tammedicamentomaterial);
        ag=importaragendamentobin(&agendamentos,&tamagendamento,&codigoatualagendamento,agendamentobin,pacientes,tampacientes,profissionais,tamprofissionais,procedimentos,tamprocedimento,medicamentosmateriais,tammedicamentomaterial);
        lan= importarlancamentoretiradabin(&lacamentosretiradas,&tamlancamentosretiradas,agendamentos,tamagendamento,procedimentos,tamprocedimento,&saldototal,entradaestoque,tamentradaestoque,lancamentosretiradasbin);
        
        if (p == -1)
        {
            printf("Erro ao abrir arquivo de pacientes\n");
        }
        else
        {
            printf("Pacientes carregados com sucesso do bin\n");
        }

        if (f == -1)
        {
            printf("Erro ao abrir arquivo de  fornecedores\n");
        }
        else
        {
            printf("fornecedores carregados com sucesso do bin\n");
        }

         if (m == -1)
        {
            printf("Erro ao abrir arquivo de  medicamentos\n");
        }
        else
        {
            printf("medicamentos carregados com sucesso do bin\n");
        }

         if (pf == -1)
        {
            printf("Erro ao abrir arquivo de  profissionais \n");
        }
        else
        {
            printf("profissionais carregados com sucesso do bin\n");
        }
        if (a == -1)
        {
            printf("Erro ao abrir arquivo de  ambientes \n");
        }
        else
        {
            printf("ambientes carregados com sucesso do bin\n");
        }
         if (pro == -1)
        {
            printf("Erro ao abrir arquivo de  procedimentos \n");
        }
        else
        {
            printf("procedimentos carregados com sucesso do bin\n");
        }
        if (ag == -1)
        {
            printf("Erro ao abrir arquivo de  agendamentos \n");
        }
        else
        {
            printf("agendamentos carregados com sucesso do bin\n");
        }
        if (r == -1)
        {
            printf("Erro ao abrir arquivo de  contas a receber \n");
        }
        else
        {
            printf("receber carregados com sucesso do bin\n");
        }

         if (en == -1)
        {
            printf("Erro ao abrir arquivo de  entrada estoque \n");
        }
        else
        {
            printf("entrada estoque carregados com sucesso do bin\n");
        }
        if (lan == -1)
        {
            printf("Erro ao abrir arquivo de lançamentos e entradas \n");
        }
        else
        {
            printf(" lancamentos e entradas carregados com sucesso do bin\n");
        }
        
    
    }

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
        printf("10:Estoque\n");
        printf("11:Verificar caixa\n");
        printf("12:Relatorios\n");
        printf("13:Sair\n");
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
            printf("6:Agendamentos\n");
            printf("7:Procedimentos\n");

            scanf("%d", &op1);
            if (op1 < 1 || op1 > 7)
            {
                printf("opção inválida, tente novamente\n");
            }
            else if (op1 == 1)
            {
                leitura = importarpaciente(&pacientes, nome, &tampacientes, &codigoatualpacientes);
                if (leitura == -1)
                {
                    printf("erro ao importar pacientes\n");
                }
                else
                {
                    printf("pacientes importados com sucesso\n");
                }
            }
            else if (op1 == 2)
            {
                leitura=importarambiente(&ambientes,nome,&tamambiente,&codigoatualambiente);
                if (leitura == -1)
                {
                    printf("erro ao importar ambientes\n");
                }
                else
                {
                    printf("ambientes importados com sucesso\n");
                }
            }
            else if (op1 == 3)
            {
                leitura = importarfornecedor(&fornecedores, nome, &tamfornecedor, &codigoatualfornecedor);
                if (leitura == -1)
                {
                    printf("erro ao importar fornecedores\n");
                }
                else
                {
                    printf("fornecedores importados com sucesso\n");
                }
            }
            else if (op1 == 4)
            {
                leitura = importarmedicamento(&medicamentosmateriais, nome, &tammedicamentomaterial,
                                              &codigoatualmedicamentomaterial);
                if (leitura == -1)
                {
                    printf("erro ao importar medicamentos\n");
                }
                else
                {
                    printf("medicamentos importados com sucesso\n");
                }
            }
            else if (op1 == 5)
            {
                leitura = importarprofissional(&profissionais, nome, &tamprofissionais, &codigoatualprofissionais);
                if (leitura == -1)
                {
                    printf("erro ao importar profissionais\n");
                }
                else
                {
                    printf("profissionais importados com sucesso\n");
                }
            }
            else if (op1 == 6)
            {
                leitura = importaragendamento(&agendamentos, nome, &tamagendamento,
                                              &codigoatualagendamento, pacientes, tampacientes, profissionais,
                                              tamprofissionais, procedimentos, tamprocedimento,
                                              medicamentosmateriais, tammedicamentomaterial);
                if (leitura == -1)
                {
                    printf("erro ao importar agendamentos\n");
                }
                else
                {
                    printf("agendamentos importados com sucesso\n");
                }
            }
            else if (op1 == 7)
            {
                leitura= importarprocedimento(&procedimentos,nome,&tamprocedimento,&codigoatualprocedimentos,ambientes,medicamentosmateriais,tamambiente,tammedicamentomaterial);
                  if (leitura == -1)
                {
                    printf("erro ao importar procedimentos\n");
                }
                else
                {
                    printf("procedimentos importados com sucesso\n");
                }
            }
        }

        else if (op2 == 9)
        {
            printf("1:Pacientes\n");
            printf("2:Ambientes Medicos\n");
            printf("3:Fornecedores\n");
            printf("4:Medicamentos e Materiais\n");
            printf("5:Profisionais\n");
            printf("6:Agendamentos\n");
            printf("7:Procedimentos\n");
            scanf("%d", &op1);

            if (op1 < 1 || op1 > 7)
            {
                printf("opção inválida, tente novamente\n");
            }

            else if (op1 == 1)
            {
                leitura = exportarpaciente(pacientes, pacientexml, tampacientes);
                if (leitura == -1)
                {
                    printf("erro ao abrir arquivo ou não havia pacientes");
                }
                else
                {
                    printf("pacientes exportados com sucesso\n");
                }
            }
            else if (op1 == 2)
            {
                leitura = exportarambiente(ambientes, ambientesmedicosxml, tamambiente);
                if (leitura == -1)
                {
                    printf("erro ao abrir arquivo ou não havia ambientes");
                }
                else
                {
                    printf("ambientes exportados com sucesso\n");
                }
            }
            else if (op1 == 3)
            {
                leitura = exportarfornecedor(fornecedores, fornecedoresxml, tamfornecedor);
                if (leitura == -1)
                {
                    printf("erro ao abrir arquivo ou não havia fornecedores");
                }
                else
                {
                    printf("fornecedores exportados com sucesso\n");
                }
            }
            else if (op1 == 4)
            {
                leitura = exportarmedicamento(medicamentosmateriais, medicamentosxml, tammedicamentomaterial);
                if (leitura == -1)
                {
                    printf("erro ao abrir arquivo ou não havia medicamentos");
                }
                else
                {
                    printf("medicamentos exportados com sucesso\n");
                }
            }
            else if (op1 == 5)
            {
                leitura = exportarprofissional(profissionais, profissionaisxml, tamprofissionais);
                if (leitura == -1)
                {
                    printf("erro ao abrir arquivo ou não havia profissionais");
                }
                else
                {
                    printf("profissionaiss exportados com sucesso\n");
                }
            }
            else if (op1 == 6)
            {
                leitura = exportaragendamento(agendamentos, agendamentosxml, tamagendamento);
                if (leitura == -1)
                {
                    printf("erro ao abrir arquivo ou não havia agendamentos");
                }
                else
                {
                    printf("agendamentos exportados com sucesso\n");
                }
            }
            else if (op1 == 7)
            {
                leitura = exportarprocedimento(procedimentos, procedimentosxml, tamprocedimento);
                if (leitura == -1)
                {
                    printf("erro ao abrir arquivo ou não havia procedimentos");
                }
                else
                {
                    printf("procedimentos exportados com sucesso\n");
                }
            }
        }
        else if (op2 == 10)
        {
            menuestoque(&entradaestoque, &medicamentosmateriais, tammedicamentomaterial, &tamentradaestoque,&codigoatualentradaestoque);
        }
        else if (op2 == 11)
        {
            menucaixa(&saldototal, &lacamentosretiradas, &receber,
                      &tamlancamentosretiradas, &tamreceber,
                      &codigoatualreceber, agendamentos, tamagendamento, procedimentos, tamprocedimento, entradaestoque, tamentradaestoque);
        }
        else if(op2==12){
          menurelatorios(agendamentos,tamagendamento,ambientes,tamambiente,lacamentosretiradas,
            tamlancamentosretiradas,entradaestoque,tamentradaestoque,
            fornecedores,tamagendamento,medicamentosmateriais,
            tammedicamentomaterial,pacientes,tampacientes,procedimentos,
            tamprocedimento,profissionais,tamprofissionais,receber,tamreceber);
        }
        else if (op2 == 13 && oparma==2)
        {
            exportarpacientetxt(pacientes,pacientestxt,tampacientes);
            exportarfornecedortxt(fornecedores,fornecedorestxt,tamfornecedor);
            exportarmedicamentotxt(medicamentosmateriais,medicamentosmateriaistxt,tammedicamentomaterial);
            exportarprofissionaltxt(profissionais,profissionaistxt,tamprofissionais);
            exportarambientemedicotxt(ambientes,ambientestxt,tamambiente);
            exportarprocedimentotxt(procedimentos,tamprocedimento,procedimentostxt);
            exportaragendamentotxt(agendamentos,agendamentostxt,tamagendamento);
            exportarrecebertxt(receber,recebertxt,tamreceber);
            exportarentradaestoquetxt(entradaestoque,tamentradaestoque,entradaestoquetxt);
            exportarlancamentosretiradastxt(lacamentosretiradas,tamlancamentosretiradas,lancamentoretiradastxt);

            for (long int i = 0; i < tamprocedimento; i++)
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
            free(receber);
            free(lacamentosretiradas);

            for(long int i=0;i<tamentradaestoque;i++){
             free((entradaestoque)[i].codmedicamentosmateriaisrecebidos);
            }
            free(entradaestoque);
        }
        
           else if (op2 == 13 && oparma==3)
        {
            exportarpacientebin(pacientes,tampacientes,pacientesbin);
            exportarfornecedorbin(fornecedores,tamfornecedor,fornecedoresbin);
            exportarmedicamentomaterialbin(medicamentosmateriais,tammedicamentomaterial,medicamentosmateriaisbin);
            exportarprofissionalbin(profissionais,tamprofissionais,profissionaisbin);
            exportarambientemedicobin(ambientes,tamambiente,ambientesbin);
            exportarprocedimentobin(procedimentos,tamprocedimento,procedimentosbin);
            exportaragendamentobin(agendamentos,tamagendamento,agendamentobin);
            exportarreceberbin(receber,tamreceber,receberbin);
            exportarentradaestoquebin(entradaestoque,tamentradaestoque,entradaestoquebin);
            exportarlancamentoretiradabin(lacamentosretiradas,tamlancamentosretiradas,lancamentosretiradasbin);

            for (long int i = 0; i < tamprocedimento; i++)
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
            free(receber);
            free(lacamentosretiradas);

            for(long int i=0;i<tamentradaestoque;i++){
             free((entradaestoque)[i].codmedicamentosmateriaisrecebidos);
            }
            free(entradaestoque);
        

        }
        else if(op2==13 &&oparma==1){
            for (long int i = 0; i < tamprocedimento; i++)
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
            free(receber);
            free(lacamentosretiradas);

            for(long int i=0;i<tamentradaestoque;i++){
             free((entradaestoque)[i].codmedicamentosmateriaisrecebidos);
            }
            free(entradaestoque);
        }
        

        else if (op2 < 1 || op2 > 13)
        {
            printf("opção inválida, tente novamente\n");
        }

    } while (op2 != 13);

    return 0;
}