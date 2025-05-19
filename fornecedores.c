#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void menufornecedores()
{
   Fornecedor *fornecedores = NULL;
   long int tamfornecedor = 0, codigoatual = 0, codigo;
   int op;

   do
   {
      op = 0, codigo = 0;
      printf("1:Cadastrar fornecedor\n:");
      printf("2:Alterar fornecedor\n:");
      printf("3: Excluir fornecedor\n");
      printf("4:Listar fornecedores\n");
      printf("5:Consultar fornecedor\n");
      printf("6:Sair\n");
      scanf("%d", &op);

      if (op <= 0 || op > 6)
      {
         printf("opção invalida! tente novamente\n");
      }
      else
      {
         if (op == 1)
         {
            fornecedores = cadastrarfornecedor(fornecedores, &tamfornecedor, &codigoatual);
         }
         else if (op == 2)
         {
            printf("digite o codigo");
            scanf("%ld", &codigo);

            alterarfornecedor(fornecedores, tamfornecedor, codigo);
         }
         else if (op == 3)
         {
            printf("digite o codigo");
            scanf("%ld", &codigo);
            fornecedores = excluirfornecedor(fornecedores, &tamfornecedor, codigo);
         }
         else if (op == 4)
         {
            listarfornecedores(fornecedores, tamfornecedor);
         }

         else if (op == 5)
         {
            printf("digite o codigo");
            scanf("%ld", &codigo);
            consultafornecedor(fornecedores, tamfornecedor,codigo);
         }
      }

   } while (op != 6);
   free(fornecedores);
}
Fornecedor *cadastrarfornecedor(Fornecedor *fornecedores, long int *tamfornecedor, long int *codigoatual)
{
   Fornecedor *novo = realloc(fornecedores, (*tamfornecedor + 1) * sizeof(Fornecedor));
   if (novo == NULL)
   {
      printf("Erro ao alocar memória\n");
      return fornecedores;
   }

   fornecedores = novo;

   fornecedores[*tamfornecedor].codigo = *codigoatual;

   printf("Digite o nome: ");
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
   printf("Fornecedor cadastrado com sucesso\n");
   (*tamfornecedor)++;
   (*codigoatual)++;
   return fornecedores;
}

void alterarfornecedor(Fornecedor *fornecedores, long int tamfornecedor, long int codigo)
{
   if (fornecedores == NULL)
   {
      printf("Lista de fornecedores vazia\n");
      return;
   }

   for (int i = 0; i < tamfornecedor; i++)
   {
      if (fornecedores[i].codigo == codigo)
      {
         printf("Digite o nome: ");
         scanf(" %[^\n]", fornecedores[i].nomeFantasia);

         printf("Digite a razão social: ");
         scanf(" %[^\n]", fornecedores[i].razaoSocial);

         printf("Digite a inscrição estadual: ");
         scanf(" %[^\n]", fornecedores[i].inscricaoEstadual);

         printf("Digite o CNPJ: ");
         scanf(" %[^\n]", fornecedores[i].cnpj);

         printf("Digite o estado: ");
         scanf(" %[^\n]", fornecedores[i].endereco.estado);

         printf("Digite a cidade: ");
         scanf(" %[^\n]", fornecedores[i].endereco.cidade);

         printf("Digite o bairro: ");
         scanf(" %[^\n]", fornecedores[i].endereco.bairro);

         printf("Digite a rua: ");
         scanf(" %[^\n]", fornecedores[i].endereco.rua);

         printf("Digite o telefone: ");
         scanf(" %[^\n]", fornecedores[i].telefone);

         printf("Digite o email: ");
         scanf(" %[^\n]", fornecedores[i].email);
         printf("alteração feita com sucesso\n");

         return;
      }
   }
   printf("fornecedor não encontrado");
}

void listarfornecedores(Fornecedor *fornecedores, long int tamfornecedor)
{
   if (fornecedores == NULL || tamfornecedor == 0)
   {
      printf("Lista de fornecedores vazia.\n");
      return;
   }

   for (int i = 0; i < tamfornecedor; i++)
   {
      printf("Código: %ld\n", fornecedores[i].codigo);
      printf("Nome Fantasia: %s\n", fornecedores[i].nomeFantasia);
      printf("Razão Social: %s\n", fornecedores[i].razaoSocial);
      printf("Inscrição Estadual: %s\n", fornecedores[i].inscricaoEstadual);
      printf("CNPJ: %s\n", fornecedores[i].cnpj);
      printf("Endereço: %s\t%s\t%s\t%s\n", fornecedores[i].endereco.estado, fornecedores[i].endereco.cidade,
             fornecedores[i].endereco.bairro, fornecedores[i].endereco.rua);
      printf("Telefone: %s\n", fornecedores[i].telefone);
      printf("Email: %s\n", fornecedores[i].email);
   }
   return;
}

Fornecedor *excluirfornecedor(Fornecedor *fornecedores, long int *tamfornecedor, long int codigo)
{
   int encontrado = -1;
   if (fornecedores == NULL || *tamfornecedor == 0)
   {
      printf("Lista de fornecedores vazia.\n");
      return fornecedores;
   }

   for (int i = 0; i < *tamfornecedor; i++)
   {
      if (fornecedores[i].codigo == codigo)
      {
         encontrado = i;
         break;
      }
   }
   if (encontrado == -1)
   {
      printf(" fornecedor não encontrado\n");
      return fornecedores;
   }
   else
   {
      for (int j = encontrado; j < *tamfornecedor - 1; j++)
      {
         fornecedores[j] = fornecedores[j + 1];
      }
      (*tamfornecedor)--;

      if (*tamfornecedor == 0)
      {
         printf("excluido com sucesso\n");
         free(fornecedores);
         return NULL;
      }

      Fornecedor *aux = realloc(fornecedores, (*tamfornecedor) * sizeof(Fornecedor));
      if (aux == NULL)
      {
         printf("erro ao reallocar memoria\n");
         return fornecedores;
      }
      else
      {
         fornecedores = aux;
         printf("excluido com sucesso\n");
      }
   }
   return fornecedores;
}

void consultafornecedor(Fornecedor *fornecedores, long int tamfornecedor, long int codigo)
{
   if (fornecedores == NULL || tamfornecedor == 0)
   {
      printf("Lista de fornecedores vazia.\n");
      return;
   }
   for (int i = 0; i < tamfornecedor; i++)
   {
      if (fornecedores[i].codigo == codigo)
      {
         printf("Código: %ld\n", fornecedores[i].codigo);
         printf("Nome Fantasia: %s\n", fornecedores[i].nomeFantasia);
         printf("Razão Social: %s\n", fornecedores[i].razaoSocial);
         printf("Inscrição Estadual: %s\n", fornecedores[i].inscricaoEstadual);
         printf("CNPJ: %s\n", fornecedores[i].cnpj);
         printf("Endereço: %s\t%s\t%s\t%s\n", fornecedores[i].endereco.estado, fornecedores[i].endereco.cidade,
                fornecedores[i].endereco.bairro, fornecedores[i].endereco.rua);
         printf("Telefone: %s\n", fornecedores[i].telefone);
         printf("Email: %s\n", fornecedores[i].email);
         return;
      }
   }
   printf(" fornecedor não encontrado\n");
}
