//Librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Definizione costanti
#define MAX_LUNGHEZZA_ESPRESSIONE 100
#define PARENTESI_APERTA '('
#define PARENTESI_CHIUSA ')'
#define SPAZIO ' '
#define SOMMA '+'
#define SOTTRAZIONE '-'
#define MOLTIPLICAZIONE '*'
#define DIVISIONE '/'



//Definizione tipi utilizzati
typedef int Contatore;
typedef enum {parentesi,numero,operatore} Tipo;
typedef struct
{
  Tipo Tipologia;
  char Parentesi;
  char Operatore;
  unsigned int Numero;
} Oggetto;
typedef struct
{
  Oggetto Lista[MAX_LUNGHEZZA_ESPRESSIONE];
  int Numero_elementi;
} Espressione;

//Definizione funzioni
void compilaEspressione(Espressione *expression);
void leggiEspressione(Espressione *expression);
void trovaEspressione(Espressione *expression);
void risolviEspressione(Espressione *expression, Contatore inizioEspressione, Contatore fineEspressione);
void removeSpaces(char espressione[]);


//Main
int main(int argc, char const *argv[]) {
  Espressione expression;

  compilaEspressione(&expression);
  leggiEspressione(&expression);
  risolviEspressione(&expression);

  return 0;
}

void compilaEspressione(Espressione *expression)
{
  char espressione[MAX_LUNGHEZZA_ESPRESSIONE];
  Contatore i;

  // Starting input Phase
  printf("\nInserisci l'espressione da calcolare:\nL'espressione deve essere scritta nella seguente maniera : ((a+(b+c))+d), ovvero con ogni operazione separata dall'apertura e chiusura delle parentesi.\n!!!CARATTERI CONSENTITI!!! ---> numeri, '+' , '-' , '*' , '/' , ' '\nDigita la tua espressione : ");
  fgets(espressione, MAX_LUNGHEZZA_ESPRESSIONE, stdin);

  if ((strlen(espressione) > 0) && (espressione[strlen(espressione)-1] == '\n'))
  {
    espressione[strlen(espressione)-1] = '\0';
  }
  //End of input phase

  //Removing useless spaces ;)
  removeSpaces(espressione);

  //Compiling the List
  (*expression).Numero_elementi = 0;
  for(i=0; espressione[i]!='\0'; i++)
  {
    if(espressione[i]==PARENTESI_APERTA || espressione[i]==PARENTESI_CHIUSA)
    {
      (*expression).Lista[(*expression).Numero_elementi].Tipologia = parentesi;
      (*expression).Lista[(*expression).Numero_elementi].Parentesi = espressione[i];
    }
    else if(espressione[i]==SOMMA || espressione[i]==DIFFERENZA || espressione[i]==MOLTIPLICAZIONE || espressione[i]==DIVISIONE)
    {
      (*expression).Lista[(*expression).Numero_elementi].Tipologia = operatore;
      (*expression).Lista[(*expression).Numero_elementi].Operatore = espressione[i];
    }
    else if(espressione[i]>='0' && espressione[i]<='9')
    {
      (*expression).Lista[(*expression).Numero_elementi].Tipologia = numero;
      (*expression).Lista[(*expression).Numero_elementi].Numero = (int)(espressione[i] - '0');
    }

    (*expression).Numero_elementi++;
  }
}

void leggiEspressione(Espressione *expression)
{
  Contatore j;
  for(j=0;j<(*expression).Numero_elementi;j++)
  {
    switch((*expression).Lista[j].Tipologia)
    {
      case parentesi:
        printf("%c", (*expression).Lista[j].Parentesi);
        break;
      case operatore:
        printf("%c", (*expression).Lista[j].Operatore);
        break;
      case numero:
        printf("%d", (*expression).Lista[j].Numero);
        break;
    }
  }
}

void trovaEspressione(Espressione *expression)
{
  Contatore i,k;

  for(i=0;i<(*expression).Numero_elementi;i++)
  {
    if((*expression).Lista[i].Tipologia == parentesi)
    {
      if((*expression).Lista[i].Parentesi == PARENTESI_APERTA)
      {
        k=i+1;
        while((*expression).Lista[k].Tipologia!=parentesi)
        {
          ++k;
        }
        if((*expression).Lista[k].Parentesi == PARENTESI_CHIUSA)
        {
          risolviEspressione(&expression,i+1,k-1);
        } else {
          i=k-1;
        }
      }
    }
  }
}

void risolviEspressione(Espressione *expression, Contatore inizioEspressione, Contatore fineEspressione)
{
  Contatore currentPos,contOperatori,newPos,k,j,esponente;
  int Operatori[2],numeroDaInserire;
  char tipoOperazione;

  currentPos = inizioEspressione;
  contOperatori = 0;

  while(currentPos<fineEspressione)
  {
    if((*expression).Lista[currentPos].Tipologia == numero)
    {
      k=currentPos;
      j=0;
      while((*expression).Lista[k].Tipologia == numero)
      {
        ++k;
        ++j;
      }
      numeroDaInserire=0;
      newPos = k;
      k--;
      for(esponente=0;esponente<j;esponente++)
      {
        numeroDaInserire+=(*expression).Lista[k].Numero * pow(10,esponente);
        k--;
      }
      Operatori[contOperatori]=numeroDaInserire;
      ++contOperatori;
      currentPos = newPos;
    } else {
      tipoOperazione = (*expression).Lista[currentPos].Operatore;
    }
  }

  //Qui ho finito di ordinare l'espressione in una struttura precisa. E' ora necessario calcolare il risultato e scalare la lista sequenziale expression
  //DA FARE
}

void removeSpaces(char espressione[])
{
  Contatore i, counter;

  counter = 0;
  for(i=0;espressione[i]!='\0';i++)
  {
    if(espressione[i] != SPAZIO)
    {
      espressione[counter++] = espressione[i];
    }
  }
  espressione[counter] = '\0';
}
