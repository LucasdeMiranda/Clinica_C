#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

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
