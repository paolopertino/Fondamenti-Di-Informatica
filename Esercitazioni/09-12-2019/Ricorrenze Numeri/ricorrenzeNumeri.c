#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "./Input.txt"

typedef struct ELEMENTO
{
  int valore;
  int numRicorrenze;
  struct ELEMENTO *pProx;
} ElemLista;
typedef ElemLista *Lista;
typedef enum{false,true}bool;

/*
  Tipo input:
  5, 0, -3, 0, 5, 2, 0, 121, -18
  Tipo output:
  Lista dinamica con numero ricorrenze
*/
Lista contaOccorrenze(FILE *Stream);

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}

Lista contaOccorrenze(FILE *Stream)
{
  Lista testaLista,nuovoElem,ultimoElem,cursore;
  int valoreLetto,risultatoLettura;
  bool giaPresente;

  testaLista = NULL;

  do {
    risultatoLettura = fscanf(Stream,"%d",&valoreLetto);

    if(risultatoLettura == 1)
    {
      cursore = testaLista;
      giaPresente = false;
      while((cursore != NULL) && (false==giaPresente))
      {
        ultimoElem = cursore;
        if(valoreLetto == cursore->valore)
        {
          giaPresente = true;
        }
        cursore = cursore->pProx;
      }

      if(giaPresente == true) ultimoElem->numRicorrenze += 1;
      else
      {
        nuovoElem = malloc(sizeof(ElemLista));
        nuovoElem->valore = valoreLetto;
        nuovoElem->numRicorrenze = 1;
        nuovoElem->pProx = NULL;
        if(testaLista==NULL)
        {
          testaLista = nuovoElem;
        } else {
          ultimoElem->pProx = nuovoElem;
        }
      }
    }
  } while(risultatoLettura==1);

  return testaLista;
}
