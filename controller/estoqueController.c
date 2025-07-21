#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

Entradaestoque *cadastrarentradaestoque(Entradaestoque *entradaestoque, long int *tamentradaestoque,
                                        MedicamentoMaterial *medicamentosmateriais, long int tammedicamentosmaterial,
                                        Entradaestoque *novoentradaestoque, long int *codigoatual)
{
  // Verifica se todos os materiais/medicamentos existem
  for (int i = 0; i < novoentradaestoque->tammedicamentosmateriaisrecebidos; i++)
  {
    long int codbuscado = novoentradaestoque->codmedicamentosmateriaisrecebidos[i].codigo;
    int encontrado = -1;
    for (int j = 0; j < tammedicamentosmaterial; j++)
    {
      if (medicamentosmateriais[j].codigo == codbuscado)
      {
        encontrado = 0;
        break;
      }
    }
    if (encontrado == -1)
    {
      return entradaestoque;
    }
  }
  Entradaestoque *novo = realloc(entradaestoque, (*tamentradaestoque + 1) * sizeof(Entradaestoque));
  if (novo == NULL)
  {
    // erro ao alocar memoria
    return entradaestoque;
  }

  entradaestoque = novo;
  novoentradaestoque->codigo=*codigoatual;
  entradaestoque[*tamentradaestoque] = *novoentradaestoque;

  // Aloca novo vetor de structs Codmedicamentosmateriais
  entradaestoque[*tamentradaestoque].codmedicamentosmateriaisrecebidos = malloc(novoentradaestoque->tammedicamentosmateriaisrecebidos * sizeof(Codmateriaisrecebidos));

  if (entradaestoque[*tamentradaestoque].codmedicamentosmateriaisrecebidos == NULL)
  {
    // Erro ao alocar memória para os medicamentos/materiais
    return entradaestoque;
  }
  for (int i = 0; i < novoentradaestoque->tammedicamentosmateriaisrecebidos; i++)
  {
    entradaestoque[*tamentradaestoque].codmedicamentosmateriaisrecebidos[i] = novoentradaestoque->codmedicamentosmateriaisrecebidos[i];
    entradaestoque[*tamentradaestoque].codmedicamentosmateriaisrecebidos[i].total=novoentradaestoque->codmedicamentosmateriaisrecebidos[i].precocustounid*novoentradaestoque->codmedicamentosmateriaisrecebidos[i].qnt;
  }

  for (int i = 0; i < novoentradaestoque->tammedicamentosmateriaisrecebidos; i++)
  {
    for (int j = 0; j < tammedicamentosmaterial; j++)
    {
      if (medicamentosmateriais[j].codigo ==entradaestoque[*tamentradaestoque].codmedicamentosmateriaisrecebidos[i].codigo)
      {
        strncpy(entradaestoque[*tamentradaestoque].codmedicamentosmateriaisrecebidos[i].descricao,
                medicamentosmateriais[j].descricao,
                sizeof(entradaestoque[*tamentradaestoque].codmedicamentosmateriaisrecebidos[i].descricao));
        break;
      }
    }
  }
  entradaestoque[*tamentradaestoque].totaldetudo = 0;
  for (int i = 0; i < novoentradaestoque->tammedicamentosmateriaisrecebidos; i++) {
    entradaestoque[*tamentradaestoque].totaldetudo +=
        entradaestoque[*tamentradaestoque].codmedicamentosmateriaisrecebidos[i].total;
}
entradaestoque[*tamentradaestoque].totaldetudo=entradaestoque[*tamentradaestoque].totaldetudo+
entradaestoque[*tamentradaestoque].imposto+ entradaestoque[*tamentradaestoque].frete;

  (*tamentradaestoque)++;
  (*codigoatual)++;
  return entradaestoque;
}

void estoqueminimo(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial)
{
  for (int i = 0; i < tammedicamentomaterial; i++)
  {
    if (medicamentosmateriais[i].estoqueMinimo > medicamentosmateriais[i].quantidadeEstoque)
    {
      printf("Medicamento codigo %ld quantidade em estoque %ld está abaixo do estoque minimo:%ld\n",
             medicamentosmateriais[i].codigo,
             medicamentosmateriais[i].quantidadeEstoque, medicamentosmateriais[i].estoqueMinimo);
    }
  }
}

//modifica os preços dos medicamentos e materias com base nos calculos feitos com frete e imposto
void alterarpreco(Entradaestoque *novoentradaestoque, MedicamentoMaterial *medicamentomaterial, 
long int tammedicamentomaterial){
  float freteproduto=0, impostoproduto=0;
  //total de produtos recebidos é necessario para o calculo do imposto e frete sob cada produto temons que somar o valor do frete e do imposto por produto ao preço
  long int totalprodutos=0;
  for(int i=0;i<novoentradaestoque->tammedicamentosmateriaisrecebidos;i++){
    totalprodutos=totalprodutos+novoentradaestoque->codmedicamentosmateriaisrecebidos[i].qnt;
  }
  if(totalprodutos!=0){

  freteproduto= novoentradaestoque->frete/totalprodutos;
  impostoproduto=novoentradaestoque->imposto/totalprodutos;
}

  for(int i=0;i<novoentradaestoque->tammedicamentosmateriaisrecebidos;i++){
    for(int j=0;j<tammedicamentomaterial;j++){
      if(novoentradaestoque->codmedicamentosmateriaisrecebidos[i].codigo==medicamentomaterial[j].codigo){
       medicamentomaterial[j].precoCusto=novoentradaestoque->codmedicamentosmateriaisrecebidos[i].precocustounid;
       medicamentomaterial[j].precoVenda=medicamentomaterial[j].precoCusto+freteproduto+impostoproduto+((medicamentomaterial[j].precoCusto+freteproduto+impostoproduto)*0.15);
       medicamentomaterial[j].quantidadeEstoque += novoentradaestoque->codmedicamentosmateriaisrecebidos[i].qnt;

      }
    }
  }
  
}

long int importarentradaestoquetxt(Entradaestoque **entradaestoque, long int *tamentradaestoque, long int *codigoatual,
                                   MedicamentoMaterial *medicamentosmateriais, long int tammedicamentosmaterial,
                                   char *nome)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        return -1;
    }

    char linha[5000];
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        Entradaestoque novoentrada;

        linha[strcspn(linha, "\n")] = '\0';

        char *token = strtok(linha, ";");
        if (token == NULL) continue;
        novoentrada.codigo = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(novoentrada.cnpj, token, sizeof(novoentrada.cnpj));
        novoentrada.cnpj[sizeof(novoentrada.cnpj) - 1] = '\0';

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(novoentrada.fornecedor, token, sizeof(novoentrada.fornecedor));
        novoentrada.fornecedor[sizeof(novoentrada.fornecedor) - 1] = '\0';

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(novoentrada.data, token, sizeof(novoentrada.data));
        novoentrada.data[sizeof(novoentrada.data) - 1] = '\0';

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoentrada.frete = strtof(token, NULL);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoentrada.imposto = strtof(token, NULL);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoentrada.totaldetudo = strtof(token, NULL);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoentrada.codfornecedor = strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        novoentrada.tammedicamentosmateriaisrecebidos = strtol(token, NULL, 10);

        novoentrada.codmedicamentosmateriaisrecebidos = malloc(novoentrada.tammedicamentosmateriaisrecebidos * sizeof(Codmateriaisrecebidos));
        if (novoentrada.codmedicamentosmateriaisrecebidos == NULL)
        {
            fclose(arquivo);
            return -1;
        }

        for (int i = 0; i < novoentrada.tammedicamentosmateriaisrecebidos; i++)
        {
            token = strtok(NULL, ";");
            if (token == NULL) break;
            novoentrada.codmedicamentosmateriaisrecebidos[i].codigo = strtol(token, NULL, 10);

            token = strtok(NULL, ";");
            if (token == NULL) break;
            strncpy(novoentrada.codmedicamentosmateriaisrecebidos[i].descricao, token,
                    sizeof(novoentrada.codmedicamentosmateriaisrecebidos[i].descricao));
            novoentrada.codmedicamentosmateriaisrecebidos[i].descricao[sizeof(novoentrada.codmedicamentosmateriaisrecebidos[i].descricao) - 1] = '\0';

            token = strtok(NULL, ";");
            if (token == NULL) break;
            novoentrada.codmedicamentosmateriaisrecebidos[i].precocustounid = strtof(token, NULL);

            token = strtok(NULL, ";");
            if (token == NULL) break;
            novoentrada.codmedicamentosmateriaisrecebidos[i].total = strtof(token, NULL);

            token = strtok(NULL, ";");
            if (token == NULL) break;
            novoentrada.codmedicamentosmateriaisrecebidos[i].qnt = strtol(token, NULL, 10);
        }
        *entradaestoque = cadastrarentradaestoque(*entradaestoque, tamentradaestoque,
                                                  medicamentosmateriais, tammedicamentosmaterial,
                                                  &novoentrada, codigoatual);
    }

    fclose(arquivo);
    return 0;
}

void exportarentradaestoquetxt(Entradaestoque *entradaestoque, long int tam, const char *caminho)
{
    FILE *arquivo = fopen(caminho, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para exportar entrada de estoque.\n");
        return;
    }

    for (long int i = 0; i < tam; i++)
    {
        fprintf(arquivo, "%ld;%s;%s;%s;%.2f;%.2f;%.2f;%ld;%ld",
                entradaestoque[i].codigo,
                entradaestoque[i].cnpj,
                entradaestoque[i].fornecedor,
                entradaestoque[i].data,
                entradaestoque[i].frete,
                entradaestoque[i].imposto,
                entradaestoque[i].totaldetudo,
                entradaestoque[i].codfornecedor,
                entradaestoque[i].tammedicamentosmateriaisrecebidos);

        for (long int j = 0; j < entradaestoque[i].tammedicamentosmateriaisrecebidos; j++)
        {
            fprintf(arquivo, ";%ld;%s;%.2f;%.2f;%ld",
                    entradaestoque[i].codmedicamentosmateriaisrecebidos[j].codigo,
                    entradaestoque[i].codmedicamentosmateriaisrecebidos[j].descricao,
                    entradaestoque[i].codmedicamentosmateriaisrecebidos[j].precocustounid,
                    entradaestoque[i].codmedicamentosmateriaisrecebidos[j].total,
                    entradaestoque[i].codmedicamentosmateriaisrecebidos[j].qnt);
        }

        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

long int importarentradaestoquebin(Entradaestoque **entradas, long int *tamentradaestoque, long int *codigoatual,
                                   const char *nomearquivo,
                                   MedicamentoMaterial *medicamentosmateriais, long int tammedicamentosmaterial)
{
    FILE *arquivo = fopen(nomearquivo, "rb");
    if (!arquivo)
    {
        return -1; // erro abrir
    }

    long int total;
    if (fread(&total, sizeof(long int), 1, arquivo) != 1)
    {
        fclose(arquivo);
        return -2; // erro ler total
    }

    for (long int i = 0; i < total; i++)
    {
        Entradaestoque temp;
        memset(&temp, 0, sizeof(Entradaestoque)); // segurança

        if (fread(&temp.codigo, sizeof(long int), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(temp.cnpj, sizeof(char), 1000, arquivo) != 1000) { fclose(arquivo); return -3; }
        if (fread(temp.fornecedor, sizeof(char), 1000, arquivo) != 1000) { fclose(arquivo); return -3; }
        if (fread(temp.data, sizeof(char), 1000, arquivo) != 1000) { fclose(arquivo); return -3; }
        if (fread(&temp.frete, sizeof(float), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(&temp.imposto, sizeof(float), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(&temp.totaldetudo, sizeof(float), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(&temp.codfornecedor, sizeof(long int), 1, arquivo) != 1) { fclose(arquivo); return -3; }
        if (fread(&temp.tammedicamentosmateriaisrecebidos, sizeof(long int), 1, arquivo) != 1) { fclose(arquivo); return -3; }

        if (temp.tammedicamentosmateriaisrecebidos > 0)
        {
            temp.codmedicamentosmateriaisrecebidos = malloc(temp.tammedicamentosmateriaisrecebidos * sizeof(Codmateriaisrecebidos));
            if (!temp.codmedicamentosmateriaisrecebidos) { fclose(arquivo); return -4; }

            if (fread(temp.codmedicamentosmateriaisrecebidos,
                      sizeof(Codmateriaisrecebidos),
                      temp.tammedicamentosmateriaisrecebidos,
                      arquivo) != temp.tammedicamentosmateriaisrecebidos)
            {
                free(temp.codmedicamentosmateriaisrecebidos);
                fclose(arquivo);
                return -5;
            }
        }
        else
        {
            temp.codmedicamentosmateriaisrecebidos = NULL;
        }

        // Cadastrar entrada no sistema
        *entradas = cadastrarentradaestoque(*entradas, tamentradaestoque,
                                            medicamentosmateriais, tammedicamentosmaterial,
                                            &temp, codigoatual);
        if (temp.codmedicamentosmateriaisrecebidos)
            free(temp.codmedicamentosmateriaisrecebidos);
    }

    fclose(arquivo);
    return 0; // sucesso
}

void exportarentradaestoquebin(Entradaestoque *entradas, long int tamentradaestoque, const char *nomearquivo)
{
    FILE *arquivo = fopen(nomearquivo, "wb");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para escrita binária.\n");
        return;
    }

    fwrite(&tamentradaestoque, sizeof(long int), 1, arquivo);

    for (long int i = 0; i < tamentradaestoque; i++)
    {
        fwrite(&entradas[i].codigo, sizeof(long int), 1, arquivo);
        fwrite(entradas[i].cnpj, sizeof(char), 1000, arquivo);
        fwrite(entradas[i].fornecedor, sizeof(char), 1000, arquivo);
        fwrite(entradas[i].data, sizeof(char), 1000, arquivo);
        fwrite(&entradas[i].frete, sizeof(float), 1, arquivo);
        fwrite(&entradas[i].imposto, sizeof(float), 1, arquivo);
        fwrite(&entradas[i].totaldetudo, sizeof(float), 1, arquivo);
        fwrite(&entradas[i].codfornecedor, sizeof(long int), 1, arquivo);
        fwrite(&entradas[i].tammedicamentosmateriaisrecebidos, sizeof(long int), 1, arquivo);

        if (entradas[i].tammedicamentosmateriaisrecebidos > 0 && entradas[i].codmedicamentosmateriaisrecebidos != NULL)
        {
            fwrite(entradas[i].codmedicamentosmateriaisrecebidos,
                   sizeof(Codmateriaisrecebidos),
                   entradas[i].tammedicamentosmateriaisrecebidos,
                   arquivo);
        }
    }

    fclose(arquivo);
}

