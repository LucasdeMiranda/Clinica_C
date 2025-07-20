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
