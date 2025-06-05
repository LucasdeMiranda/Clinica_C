#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view/biblioteca.h"

void menufornecedores()
{
   Fornecedor *fornecedores = NULL;
   long int tamfornecedor = 0, codigoatual = 0, codigo, auxtam = 0, posicao;
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
            Fornecedor novofornecedor;
            auxtam = tamfornecedor;

            printf("Digite o nome: ");
            scanf(" %99[^\n]", novofornecedor.nomeFantasia);

            printf("Digite a razão social: ");
            scanf(" %199[^\n]", novofornecedor.razaoSocial);

            printf("Digite a inscrição estadual: ");
            scanf(" %199[^\n]", novofornecedor.inscricaoEstadual);

            printf("Digite o CNPJ: ");
            scanf(" %39[^\n]", novofornecedor.cnpj);

            printf("Digite a rua: ");
            scanf(" %199[^\n]", novofornecedor.endereco.rua);

            printf("Digite o bairro: ");
            scanf(" %199[^\n]", novofornecedor.endereco.bairro);

            printf("Digite a cidade: ");
            scanf(" %199[^\n]", novofornecedor.endereco.cidade);

            printf("Digite o estado: ");
            scanf(" %9[^\n]", novofornecedor.endereco.estado);

            printf("Digite o telefone: ");
            scanf(" %19[^\n]", novofornecedor.telefone);

            printf("Digite o email: ");
            scanf(" %299[^\n]", novofornecedor.email);

            fornecedores = cadastrarfornecedor(fornecedores, &tamfornecedor, &codigoatual, &novofornecedor);

            if (tamfornecedor > auxtam)
            {
               printf("Fornecedor cadastrado com sucesso\n");
            }
            else
            {
               printf("Erro ao cadastrar fornecedor\n");
            }
         }
         else if (op == 2)
         {
            printf("digite o codigo:");
            scanf("%ld", &codigo);

            posicao = alterarfornecedor(fornecedores, tamfornecedor, codigo);

            if (posicao == -1)
            {
               printf("Forncecedor não encontrado ou lista vazia.\n");
            }
            else
            {
               printf("Digite o nome: ");
               scanf(" %99[^\n]", fornecedores[posicao].nomeFantasia);

               printf("Digite a razão social: ");
               scanf(" %199[^\n]", fornecedores[posicao].razaoSocial);

               printf("Digite a inscrição estadual: ");
               scanf(" %199[^\n]", fornecedores[posicao].inscricaoEstadual);

               printf("Digite o CNPJ: ");
               scanf(" %39[^\n]", fornecedores[posicao].cnpj);

               printf("Digite o estado: ");
               scanf(" %9[^\n]", fornecedores[posicao].endereco.estado);

               printf("Digite a cidade: ");
               scanf(" %199[^\n]", fornecedores[posicao].endereco.cidade);

               printf("Digite o bairro: ");
               scanf(" %199[^\n]", fornecedores[posicao].endereco.bairro);

               printf("Digite a rua: ");
               scanf(" %199[^\n]", fornecedores[posicao].endereco.rua);

               printf("Digite o telefone: ");
               scanf(" %19[^\n]", fornecedores[posicao].telefone);

               printf("Digite o email: ");
               scanf(" %299[^\n]", fornecedores[posicao].email);
               printf("alteração feita com sucesso\n");
            }
         }
         else if (op == 3)
         {
            printf("digite o codigo:");
            scanf("%ld", &codigo);
            auxtam = tamfornecedor;
            fornecedores = excluirfornecedor(fornecedores, &tamfornecedor, codigo);
            if (tamfornecedor < auxtam)
            {
               printf("Fornecedor excluido com sucesso\n");
            }
            else
            {
               printf("Forncedor não encontrado para exclusão\n");
            }
         }
         else if (op == 4)
         {
            listarfornecedores(fornecedores, tamfornecedor);
         }

         else if (op == 5)
         {
            printf("digite o codigo");
            scanf("%ld", &codigo);
            posicao = consultafornecedor(fornecedores, tamfornecedor, codigo);
            if (posicao == -1)
            {
               printf("Fornecedor não encontrado\n");
            }
            else
            {
               printf("Código: %ld\n", fornecedores[posicao].codigo);
               printf("Nome Fantasia: %s\n", fornecedores[posicao].nomeFantasia);
               printf("Razão Social: %s\n", fornecedores[posicao].razaoSocial);
               printf("Inscrição Estadual: %s\n", fornecedores[posicao].inscricaoEstadual);
               printf("CNPJ: %s\n", fornecedores[posicao].cnpj);
               printf("Endereço: %s\t%s\t%s\t%s\n", fornecedores[posicao].endereco.estado, fornecedores[posicao].endereco.cidade,
                      fornecedores[posicao].endereco.bairro, fornecedores[posicao].endereco.rua);
               printf("Telefone: %s\n", fornecedores[posicao].telefone);
               printf("Email: %s\n", fornecedores[posicao].email);
            }
         }
      }

   } while (op != 6);
   free(fornecedores);
}
Fornecedor *cadastrarfornecedor(Fornecedor *fornecedores, long int *tamfornecedor, long int *codigoatual, Fornecedor *novofornecedor)
{
   Fornecedor *novo = realloc(fornecedores, (*tamfornecedor + 1) * sizeof(Fornecedor));
   if (novo == NULL)
   {
      return fornecedores;
   }

   fornecedores = novo;
   novofornecedor->codigo = *codigoatual;
   fornecedores[*tamfornecedor] = *novofornecedor;
   (*tamfornecedor)++;
   (*codigoatual)++;
   return fornecedores;
}

long int alterarfornecedor(Fornecedor *fornecedores, long int tamfornecedor, long int codigo)
{
   if (fornecedores == NULL)
   {
      printf("Lista de fornecedores vazia\n");
      return -1;
   }

   for (int i = 0; i < tamfornecedor; i++)
   {
      if (fornecedores[i].codigo == codigo)
      {
         return i;
      }
   }
   return -1;
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
      return fornecedores; // ta vazio
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
      return fornecedores; // não encontrou
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
      }
   }
   return fornecedores;
}

long int consultafornecedor(Fornecedor *fornecedores, long int tamfornecedor, long int codigo)
{
   if (fornecedores == NULL || tamfornecedor == 0)
   {
      return -1; // vazio
   }
   for (int i = 0; i < tamfornecedor; i++)
   {
      if (fornecedores[i].codigo == codigo)
      {
         return i;
      }
   }
   return -1;
}
