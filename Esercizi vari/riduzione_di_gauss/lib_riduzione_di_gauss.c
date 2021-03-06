#include <stdio.h>
#include "riduzione_di_gauss.h"

#define DEBUG // Commentare per eliminare gli output di debug

/**
 * Autore: Alberto Nidasio
 * Scopo: Eseguire la riduzione di Gauss
 * Descrizione: Questo programma esegue il metodo della riduzione di Gauss
 * che si sviluppa in questi 3 passaggi:
 *   1: Si ordinano le righe per la posizione dei propri pivot
 *   2: Si modificano le righe successive in modo tale che la matrice diventi
 *      a scala (tramite la moltiplicazione)
 *   3: Si ripete il procedimento dal punto 1 considerando la matrice senza la
 *      prima riga
*/

void richiediMatrice(int m, int n, float matrice[m][n]);
void mostraMatrice(int m, int n, float matrice[m][n], int tab, int startN, int startM);
void metodoDiGauss(int m, int n, float matrice[m][n], int startM, int startN);
void trovaPivot(int m, int n, float matrice[m][n], int startM, int startN, int pivot[m - startM][2]);
void ordinaMatricePerPivot(int m, int n, float matrice[m][n], int startM, int pivot[m - startM][2]);

// Richiede all'utente di   inserire tutti gli elementi della matrice
void richiediMatrice(int m, int n, float matrice[m][n])
{
    int i, j;

    printf("Preparati ad inserire gli elementi del vettore (%d, %d)\n", m, n);

    // Per ogni vettore riga
    for (i = 0; i < m; i++)
    {
        printf("Riga n %d\n", i + 1);

        // Richiedo ciascun parametro
        for (j = 0; j < n; j++)
        {
            printf("\tInserisci il parametro n %d: ", j + 1);
            scanf("%f", &matrice[i][j]);
        }
    }
}

// Mostra gli elementi della matrice nel terminale
void mostraMatrice(int m, int n, float matrice[m][n], int tab, int startN, int startM)
{
    int i, j, t;

    // Mostro ciascun vettore riga
    for (i = 0; i < m; i++)
    {
        for (t = 0; t < tab; t++)
            printf("\t");

        // Simboli per l'apertura della matrice
        if (i == 0)
        {
            printf("\033[0;32m┌\033[0m");
        }
        else if (i == m - 1)
        {
            printf("\033[0;32m└\033[0m");
        }
        else
        {
            printf("\033[0;32m|\033[0m");
        }

        // Mostro ciascun parametro
        for (j = 0; j < n; j++)
        {
            // Evidenzio il carattere se succede alle coordinate indicate
            if (i >= startM && j >= startN)
                printf("\033[0;33m");

            printf("%.2f", matrice[i][j]);

            // Reimposto il colore se modificato
            if (i >= startM && j >= startN)
                printf("\033[0m");

            if (j < n - 1)
                printf(",");
            printf("\t");
        }

        // Simboli per la chiusura della matrice
        if (i == 0)
        {
            printf("\033[0;32m┐\033[0m");
        }
        else if (i == m - 1)
        {
            printf("\033[0;32m┘\033[0m");
        }
        else
        {
            printf("\033[0;32m|\033[0m");
        }

        printf("\n");
    }
    printf("\n");
}

// Esegue il metodo di Gauss trasformando la matrice in una matrice a scala
// (si aspetta una matrice con pivot ordinati)
void metodoDiGauss(int m, int n, float matrice[m][n], int startM, int startN)
{
    // Controllo i valori di startM e startN per vedere se il procedimento può essere portato avanti
    if (startM < m && startN < n)
    {
        int i, j, pivot[m - startM][2];
        float coeff;

#ifdef DEBUG
        printf("Porto a scala  partendo dalla posizione (%d, %d)\n", startM, startN);
#endif

        // 1: Si ordinano le righe per la posizione dei propri pivot

        // 1.1: Recupero i pivot
        trovaPivot(m, n, matrice, startM, startN, pivot);

#ifdef DEBUG
        printf("\n\tPivot della parte di matrice considerata\n");
        for(i = 0; i < m - startM; i++) printf("\tPivot %d: (%d, %d)\n", i, pivot[i][0], pivot[i][1]);
#endif

        // 1.2: Ordino la matrice in base ai pivot
        ordinaMatricePerPivot(m, n, matrice, startM, pivot);

#ifdef DEBUG
        printf("\n\tMatrice di partenza ordinata\n");
        mostraMatrice(m, n, matrice, 1, startM, startN);
        printf("\n");
#endif

        // Controllo se il primo valore (startM, startN) è nullo
        if (!matrice[startM][startN])
        {
            // In questo caso posso spostarmi di una colonna
            startN++;

            // N.B. Se il primo valore è nullo vuol dire che non c'è alcun'altra riga con
            // pivot in questa posizione
            //metodoDiGauss(matrice, startM, startN + 1);
        }

        // 2: Si modificano le righe successive alla prima in modo tale che i loro
        //    pivot non siano nella stessa posizione di quello della prima riga

        // Metodo: Se il pivot della prima riga è in colonna j si somma alla riga i per ogni i>1
        // la prima riga  moltiplicata per  –aij/a1j, in tal modo tutte le righe, eccetto la prima,
        // hanno tutti 0 nella colonna j (e tutte le righe hanno 0 nelle colonne h con h<j)

        for (i = startM + 1; i < m; i++)
        {
            // Controllo se l'elemento è diverso da 0
            if (matrice[i][startN] != 0) {
                coeff = -matrice[i][startN] / matrice[startM][startN];
                for (j = startN; j < n; j++)
                {
                    matrice[i][j] += matrice[startM][j] * coeff;
                }
#ifdef DEBUG
                printf("\tCoefficiente per riga %d: %f\n", i, coeff);
#endif
            }
        }

#ifdef DEBUG
        printf("\n\tRisultato\n");
        mostraMatrice(m, n, matrice, 1, startM, startN);
#endif

        // 3: Proseguo con la ricorsione spostandomi di una colonna e di una riga
        metodoDiGauss(m, n, matrice, startM + 1, startN + 1);
    }
}

// Permette di trovare il pivot di una matrice partendo da una colonna startM e una riga startN
void trovaPivot(int m, int n, float matrice[m][n], int startM, int startN, int pivot[m - startM][2])
{
    int i, j;
    int nPivot = m - startM;

    // Inizializzo la matrice di pivot a 0
    for (i = 0; i < nPivot; i++)
    {
        pivot[i][0] = 0;
        pivot[i][1] = 0;
    }

    // Recupero i pivot per ciascuna riga partendo da startM
    for (i = startM; i < m; i++)
    {
        pivot[i - startM][0] = -1; // Nel posto 0 salvo il valore del pivot
        pivot[i - startM][1] = i; // Nel posto 1 salvo il numero della riga

        // Trovo la colonna del pivot controllando, nella riga specificata,
        // il valore di ciasuna colonna in ordine crescente
        for (j = startN; j < n; j++)
        {
            if (matrice[i][j])
            {
                pivot[i - startM][0] = j; // Salvo la posizione n del pivot
                j = n; // Fermo il ciclo for
            }
        }
    }
}

// Ordinamento dei pivot
void ordinaMatricePerPivot(int m, int n, float matrice[m][n], int startM, int pivot[m - startM][2])
{
    int i, j, k;
    int pivot0, pivot1;
    int elementoMatrice;

    // Ordino la matrice in base ai pivot
    for (i = startM; i < m; i++)
    {
        for (j = i + 1; j < m; j++)
        {
            if (pivot[i - startM][0] > pivot[j][0])
            {
                // Pivot
                pivot0 = pivot[i - startM][0];
                pivot1 = pivot[i - startM][1];

                pivot[i - startM][0] = pivot[j][0];
                pivot[i - startM][1] = pivot[j][1];

                pivot[j][0] = pivot0;
                pivot[j][1] = pivot1;

                // Matrice
                for (k = 0; k < n; k++)
                {
                    elementoMatrice = matrice[i - startM][k];
                    matrice[i - startM][k] = matrice[j][k];
                    matrice[j][k] = elementoMatrice;
                }
            }
        }
    }
}