#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menuagendamento_controle(Agendamento **agendamentos,long int *tamagendamento,long int *codigoatual,Procedimento *procedimentos,
long int *tamprocedimento,MedicamentoMaterial *medicamentosmateriais,
long int tammedicamentomaterial,Paciente *pacientes,long int tampacientes,
Profissional *profissionais,long int tamprofissionais){
int op;
long int auxtam=0;
do{
op=0;
printf("1:Marcar agendamento\n");
printf("2:Sair\n");
if(op<=0 || op>2){
  printf("opção invalida tente novamente\n");
}
else if(op==1){
Agendamento novoagendamento;
auxtam= *tamagendamento;
printf("Digite o código do paciente:");
scanf("%ld",novoagendamento.codpaciente);
printf("Digite o código do profissionais:");
scanf("%ld",novoagendamento.codprofissional);
printf("Digite o código do ambiente médico:");
scanf("%ld",novoagendamento.codambientemedico);
printf("Digite o código do procedimento:");
scanf("%ld",novoagendamento.codprocedimento);


}


}while(op!=2);
}