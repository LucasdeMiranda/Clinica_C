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

long int importarfornecedor(Fornecedor **fornecedores, char *nome, long int *tamfornecedor, long int *codigoatualfornecedor)
{
   char linha[1024];
   FILE *arquivo = fopen(nome, "r");
   if (arquivo == NULL)
   {
      return -1;
   }

   char endereco[1000], *token;
   Fornecedor novo;

   while (fgets(linha, sizeof(linha), arquivo) != NULL)
   {
      if (strstr(linha, "<tabela nome=\"fornecedor\">") != NULL)
      {
         while (fgets(linha, sizeof(linha), arquivo) != NULL && strstr(linha, "</tabela>") == NULL)
         {
            if (strstr(linha, "<codigo>") != NULL)
               sscanf(linha, "<codigo>%ld</codigo>", &novo.codigo);

            if (strstr(linha, "<nome_fantasia>") != NULL)
               sscanf(linha, "<nome_fantasia>%99[^<]</nome_fantasia>", novo.nomeFantasia);

            if (strstr(linha, "<razao_social>") != NULL)
               sscanf(linha, "<razao_social>%199[^<]</razao_social>", novo.razaoSocial);

            if (strstr(linha, "<inscricao_estadual>") != NULL)
               sscanf(linha, "<inscricao_estadual>%199[^<]</inscricao_estadual>", novo.inscricaoEstadual);

            if (strstr(linha, "<cnpj>") != NULL)
               sscanf(linha, "<cnpj>%39[^<]</cnpj>", novo.cnpj);

            if (strstr(linha, "<endereco>") != NULL)
            {
               sscanf(linha, "<endereco>%[^<]</endereco>", endereco);
               token = strtok(endereco, ",");
               if (token != NULL)
                  strncpy(novo.endereco.rua, token, sizeof(novo.endereco.rua));
               token = strtok(NULL, ",");
               if (token != NULL)
                  novo.endereco.numero = strtol(token, NULL, 10);
               token = strtok(NULL, ",");
               if (token != NULL)
                  strncpy(novo.endereco.bairro, token, sizeof(novo.endereco.bairro));
               token = strtok(NULL, ",");
               if (token != NULL)
                  strncpy(novo.endereco.cidade, token, sizeof(novo.endereco.cidade));
               token = strtok(NULL, ",");
               if (token != NULL)
                  strncpy(novo.endereco.estado, token, sizeof(novo.endereco.estado));
            }

            if (strstr(linha, "<telefone>") != NULL)
               sscanf(linha, "<telefone>%19[^<]</telefone>", novo.telefone);

            if (strstr(linha, "<email>") != NULL)
               sscanf(linha, "<email>%299[^<]</email>", novo.email);

            if (strstr(linha, "</registro>") != NULL)
            {
               *fornecedores = cadastrarfornecedor(*fornecedores, tamfornecedor, codigoatualfornecedor, &novo);
            }
         }
         break;
      }
   }

   fclose(arquivo);
   return 0;
}

long int exportarfornecedor(Fornecedor *fornecedores, char *nome, long int tamfornecedor)
{
   FILE *arquivo = fopen(nome, "w");
   if (arquivo == NULL || fornecedores == NULL)
   {
      return -1;
   }

   fprintf(arquivo, "<dados>\n");
   fprintf(arquivo, "<!-- Tabela de Fornecedores -->\n");
   fprintf(arquivo, "<tabela nome=\"fornecedor\">\n");

   for (long int i = 0; i < tamfornecedor; i++)
   {
      fprintf(arquivo, "<registro>\n");
      fprintf(arquivo, "<codigo>%ld</codigo>\n", fornecedores[i].codigo);
      fprintf(arquivo, "<nome_fantasia>%s</nome_fantasia>\n", fornecedores[i].nomeFantasia);
      fprintf(arquivo, "<razao_social>%s</razao_social>\n", fornecedores[i].razaoSocial);
      fprintf(arquivo, "<inscricao_estadual>%s</inscricao_estadual>\n", fornecedores[i].inscricaoEstadual);
      fprintf(arquivo, "<cnpj>%s</cnpj>\n", fornecedores[i].cnpj);
      fprintf(arquivo, "<endereco>%s,%ld,%s,%s,%s</endereco>\n",
              fornecedores[i].endereco.rua,
              fornecedores[i].endereco.numero,
              fornecedores[i].endereco.bairro,
              fornecedores[i].endereco.cidade,
              fornecedores[i].endereco.estado);
      fprintf(arquivo, "<telefone>%s</telefone>\n", fornecedores[i].telefone);
      fprintf(arquivo, "<email>%s</email>\n", fornecedores[i].email);
      fprintf(arquivo, "</registro>\n");
   }

   fprintf(arquivo, "</tabela>\n");
   fprintf(arquivo, "</dados>\n");
   fclose(arquivo);

   return 0;
}

long int importarfornecedortxt(Fornecedor **fornecedores, long int *tamfornecedores, long int *codigoatual, char *nome)
{
   FILE *arquivo = fopen(nome, "r");
   if (arquivo == NULL)
   {
      return -1;
   }

   char linha[1024];
   Fornecedor novo;

   while (fgets(linha, sizeof(linha), arquivo) != NULL)
   {
      char *token = strtok(linha, ";");
      if (token != NULL)
         novo.codigo = strtol(token, NULL, 10);

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.nomeFantasia, token, sizeof(novo.nomeFantasia));

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.razaoSocial, token, sizeof(novo.razaoSocial));

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.inscricaoEstadual, token, sizeof(novo.inscricaoEstadual));

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.cnpj, token, sizeof(novo.cnpj));

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.endereco.rua, token, sizeof(novo.endereco.rua));

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.endereco.bairro, token, sizeof(novo.endereco.bairro));

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.endereco.cidade, token, sizeof(novo.endereco.cidade));

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.endereco.estado, token, sizeof(novo.endereco.estado));

      token = strtok(NULL, ";");
      if (token != NULL)
         novo.endereco.numero = strtol(token, NULL, 10);

      token = strtok(NULL, ";");
      if (token != NULL)
         strncpy(novo.telefone, token, sizeof(novo.telefone));

      token = strtok(NULL, ";\n");
      if (token != NULL)
         strncpy(novo.email, token, sizeof(novo.email));

      *fornecedores = cadastrarfornecedor(*fornecedores, tamfornecedores, codigoatual, &novo);
   }

   fclose(arquivo);
   return 0;
}

void exportarfornecedortxt(Fornecedor *fornecedores, char *nome, long int tamfornecedores)
{
   FILE *arquivo = fopen(nome, "w");
   if (arquivo == NULL)
   {
      return; // erro ao abrir
   }

   for (long int i = 0; i < tamfornecedores; i++)
   {
      fprintf(arquivo, "%ld;%s;%s;%s;%s;%s;%s;%s;%s;%ld;%s;%s\n",
              fornecedores[i].codigo,
              fornecedores[i].nomeFantasia,
              fornecedores[i].razaoSocial,
              fornecedores[i].inscricaoEstadual,
              fornecedores[i].cnpj,
              fornecedores[i].endereco.rua,
              fornecedores[i].endereco.bairro,
              fornecedores[i].endereco.cidade,
              fornecedores[i].endereco.estado,
              fornecedores[i].endereco.numero,
              fornecedores[i].telefone,
              fornecedores[i].email);
   }

   fclose(arquivo);
}
