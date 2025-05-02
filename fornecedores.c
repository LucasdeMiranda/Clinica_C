#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menufornecedores(){
  Fornecedor *fornecedores = NULL;
 long int tamfornecedor= 0;
    int op,cpf;

    do{
     op=0,cpf=0;
     printf("1:Cadastrar fornecedor\n:");
     printf("2:Alterar fornecedor\n:");
     printf("3: Excluir fornecedor");
     printf("4:Listar fornecedores");
     printf("5:Sair");
     scanf("%d",&op);

     if(op<=0 && op>5){
        printf("opção invalida! tente novamente");
     }
     else{
        if(op==1){
           fornecedores= cadastrarfornecedor(fornecedores,&tamfornecedor); 
        }
        else if(op==2){
              
        }
        else if(op==3){

        }
        else if(op==4){
            
        }
     }

    }while(op!=5);
}
Fornecedor* cadastrarfornecedor(Fornecedor *fornecedores, long int *tamfornecedor) {
    Fornecedor *novo = realloc(fornecedores, (*tamfornecedor + 1) * sizeof(Fornecedor));
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return fornecedores;
    }

    fornecedores = novo;

    printf("Digite o código: ");
    scanf("%d", &fornecedores[*tamfornecedor].codigo);

    printf("Digite o nome fantasia: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].nomeFantasia);

    printf("Digite a razão social: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].razaoSocial);

    printf("Digite a inscrição estadual: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].inscricaoEstadual);

    printf("Digite o CNPJ: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].cnpj);

    printf("Digite a rua: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].endereco.rua);

    printf("Digite o bairro: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].endereco.bairro);

    printf("Digite a cidade: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].endereco.cidade);

    printf("Digite o estado: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].endereco.estado);

    printf("Digite o telefone: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].telefone);

    printf("Digite o email: ");
    scanf(" %[^\n]", fornecedores[*tamfornecedor].email);

    (*tamfornecedor)++;
    return fornecedores;
}
