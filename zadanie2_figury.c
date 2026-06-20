#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* jak zanjdzie napis MAX_FIGUR to przeczyta to jako 10 */
#define MAX_FIGUR 10

/* jeden typ struktury obslugujacy zarowno kwadrat, jak i prostokat
   - dla kwadratu bokA == bokB                                    */
typedef struct figura
{
    char nazwa[20];   /* "kwadrat" lub "prostokat" */
    double bokA;
    double bokB;
} figura;

/* cztery funkcje liczace pola i obwody przyjmują WSKAZNIK do struktury */
/* -> to wskaźnik */
double poleKwadratu(figura *f)
{
    return f->bokA * f->bokA;
}

double obwodKwadratu(figura *f)
{
    return 4.0 * f->bokA;
}

double poleProstokata(figura *f)
{
    return f->bokA * f->bokB;
}

double obwodProstokata(figura *f)
{
    return 2.0 * (f->bokA + f->bokB);
}

/* funkcja sumujaca pola i obwody wszystkich figur z tablicy,
   korzysta z czterech funkcji zdefiniowanych powyzej */
void podsumujFigury(figura tab[], int n, double *sumaPol, double *sumaObwodow)
{
    int i;
    *sumaPol = 0.0;
    *sumaObwodow = 0.0;

    for (i = 0; i < n; ++i)
    {
        /* strcmp porównuje dwa napisy znak po znaku, jak zwróci 0 to są identyczne */
        if (strcmp(tab[i].nazwa, "kwadrat") == 0)
        {
            *sumaPol += poleKwadratu(&tab[i]);
            *sumaObwodow += obwodKwadratu(&tab[i]);
        }
        else if (strcmp(tab[i].nazwa, "prostokat") == 0)
        {
            *sumaPol += poleProstokata(&tab[i]);
            *sumaObwodow += obwodProstokata(&tab[i]);
        }
    }
}

int main()
{
    figura figury[MAX_FIGUR];
    int n = 0;
    double sumaPol, sumaObwodow;
    int i;

    /* wypelniamy tablice kilkoma przykladowymi figurami */
    strcpy(figury[n].nazwa, "kwadrat");
    figury[n].bokA = 5.0;
    figury[n].bokB = 5.0;
    n++;

    strcpy(figury[n].nazwa, "prostokat");
    figury[n].bokA = 3.0;
    figury[n].bokB = 7.0;
    n++;

    strcpy(figury[n].nazwa, "kwadrat");
    figury[n].bokA = 2.0;
    figury[n].bokB = 2.0;
    n++;

    strcpy(figury[n].nazwa, "prostokat");
    figury[n].bokA = 4.0;
    figury[n].bokB = 6.0;
    n++;

    printf("Lista figur:\n");
    for (i = 0; i < n; ++i)
    {
        if (strcmp(figury[i].nazwa, "kwadrat") == 0)
        {
            printf("%d. Kwadrat o boku %.2f -> pole = %.2f, obwod = %.2f\n",
                   i + 1, figury[i].bokA,
                   poleKwadratu(&figury[i]), obwodKwadratu(&figury[i]));
        }
        else
        {
            printf("%d. Prostokat %.2f x %.2f -> pole = %.2f, obwod = %.2f\n",
                   i + 1, figury[i].bokA, figury[i].bokB,
                   poleProstokata(&figury[i]), obwodProstokata(&figury[i]));
        }
    }

    podsumujFigury(figury, n, &sumaPol, &sumaObwodow);

    printf("\nSuma wszystkich pol:     %.2f\n", sumaPol);
    printf("Suma wszystkich obwodow: %.2f\n", sumaObwodow);

    return EXIT_SUCCESS;
}
