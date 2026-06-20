#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PUNKTOW 100

/* wczytuje liczbe punktow i ich wspolrzedne */
void czytajPunkty(int *n, float x[], float y[])
{
    int i;
    printf("Podaj liczbe punktow: ");
    scanf("%d", n);

    for (i = 0; i < *n; i++)
    {
        printf("Punkt %d - wspolrzedna x: ", i + 1);
        scanf("%f", &x[i]);
        printf("Punkt %d - wspolrzedna y: ", i + 1);
        scanf("%f", &y[i]);
    }
}

/* wypisuje punkty znajdujace sie w podanej cwiartce ukladu wspolrzednych (1-4) */
void drukujCwiartke(int n, float x[], float y[], int cwiartka)
{
    int i;
    printf("Punkty w cwiartce %d:\n", cwiartka);

    for (i = 0; i < n; i++)
    {
        int wCwiartce = 0;

        switch (cwiartka)
        {
            case 1: wCwiartce = (x[i] > 0 && y[i] > 0); break;
            case 2: wCwiartce = (x[i] < 0 && y[i] > 0); break;
            case 3: wCwiartce = (x[i] < 0 && y[i] < 0); break;
            case 4: wCwiartce = (x[i] > 0 && y[i] < 0); break;
        }

        if (wCwiartce)
            printf("(%.2f, %.2f)\n", x[i], y[i]);
    }
}

/* liczy odleglosc kazdego punktu od poczatku ukladu i zapisuje w tablicy odl[] */
void obliczOdleglosci(int n, float x[], float y[], float odl[])
{
    int i;
    for (i = 0; i < n; i++)
        odl[i] = sqrt(x[i] * x[i] + y[i] * y[i]);
}

/* zwraca INDEKS punktu najbardziej oddalonego od poczatku ukladu */
int indeksNajdalszego(int n, float odl[])
{
    int i, indeksMax = 0;
    for (i = 1; i < n; i++)
        if (odl[i] > odl[indeksMax])
            indeksMax = i;
    return indeksMax;
}

/* wybiera do tablic xWew/yWew punkty lezace w okregu o promieniu r,
   zwraca ile takich punktow znaleziono */
int punktyWOkregu(int n, float odl[], float x[], float y[], float r, float xWew[], float yWew[])
{
    int i, licznik = 0;

    for (i = 0; i < n; i++)
    {
        if (odl[i] <= r)
        {
            xWew[licznik] = x[i];
            yWew[licznik] = y[i];
            licznik++;
        }
    }

    return licznik;
}

int main()
{
    float x[MAX_PUNKTOW], y[MAX_PUNKTOW], odl[MAX_PUNKTOW];
    float xWew[MAX_PUNKTOW], yWew[MAX_PUNKTOW];
    int n, cwiartka, indeksMax, liczbaWewnatrz, i;
    float promien;

    czytajPunkty(&n, x, y);

    printf("\nPodaj numer cwiartki do wyswietlenia (1-4): ");
    scanf("%d", &cwiartka);
    drukujCwiartke(n, x, y, cwiartka);

    obliczOdleglosci(n, x, y, odl);
    printf("\nOdleglosci punktow od poczatku ukladu:\n");
    for (i = 0; i < n; i++)
        printf("Punkt %d (%.2f, %.2f) -> odleglosc = %.2f\n", i + 1, x[i], y[i], odl[i]);

    indeksMax = indeksNajdalszego(n, odl);
    printf("\nNajdalszy punkt: (%.2f, %.2f), odleglosc = %.2f\n",
           x[indeksMax], y[indeksMax], odl[indeksMax]);

    printf("\nPodaj promien okregu: ");
    scanf("%f", &promien);

    liczbaWewnatrz = punktyWOkregu(n, odl, x, y, promien, xWew, yWew);
    printf("Punkty w okregu o promieniu %.2f:\n", promien);
    for (i = 0; i < liczbaWewnatrz; i++)
        printf("(%.2f, %.2f)\n", xWew[i], yWew[i]);

    return EXIT_SUCCESS;
}
