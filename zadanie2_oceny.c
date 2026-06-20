#include <stdio.h>
#include <stdlib.h>

#define MAX_OCEN 100

/* ---- funkcje z przykladu 1 (bez zmian) ---- */

void czytaj(const char napis[], int *n, float tab[])
{
    int i;
    printf("%s\n", napis);
    scanf("%d", n);
    for (i = 0; i < *n; i++)
    {
        printf("Wartosc %d: ", i + 1);
        scanf("%f", &tab[i]);
    }
}

void drukuj(const char napis[], int n, float tab[])
{
    int i;
    printf("%s\n", napis);
    for (i = 0; i < n; i++)
        printf("%.2f\n", tab[i]);
}

void srednia(int n, float tab[], float *wynik)
{
    int i;
    float suma = 0;
    for (i = 0; i < n; i++)
        suma += tab[i];
    *wynik = suma / n;
}

int liczba(int n, float tab[], float w)
{
    int i, l = 0;
    for (i = 0; i < n; i++)
        if (tab[i] > w) l++;
    return l;
}

/* ---- zadanie 2 ---- */

/* procent ocen w przedziale [0.3w, 0.7w] */
float procentWPrzedziale(int n, float tab[], float w)
{
    int i, licznik = 0;
    float dolna = 0.3f * w;
    float gorna = 0.7f * w;

    for (i = 0; i < n; i++)
        if (tab[i] >= dolna && tab[i] <= gorna)
            licznik++;

    return (100.0f * licznik) / n;
}

/* ocena minimalna i maksymalna - wyniki przez wskazniki */
void minMaxOcena(int n, float tab[], float *minOcena, float *maxOcena)
{
    int i;
    *minOcena = tab[0];
    *maxOcena = tab[0];

    for (i = 1; i < n; i++)
    {
        if (tab[i] < *minOcena) *minOcena = tab[i];
        if (tab[i] > *maxOcena) *maxOcena = tab[i];
    }
}

/* przeliczenie pojedynczej liczby punktow (0-40) na stopien */
float stopienZPunktow(float punkty)
{
    if (punkty < 20)      return 2.0f;
    else if (punkty < 24) return 3.0f;
    else if (punkty < 28) return 3.5f;
    else if (punkty < 32) return 4.0f;
    else if (punkty < 36) return 4.5f;
    else                  return 5.0f;
}

/* tablica stopni dla wszystkich studentow (na podstawie tablicy punktow) */
void wyznaczStopnie(int n, float punkty[], float stopnie[])
{
    int i;
    for (i = 0; i < n; i++)
        stopnie[i] = stopienZPunktow(punkty[i]);
}

/* ---- zadanie dodatkowe 1 ---- */

/* sześcioelementowa tablica: ile osob ma 2.0, ile 3.0, 3.5, 4.0, 4.5, 5.0 */
void zliczStopnie(int n, float stopnie[], int wyniki[6])
{
    int i;
    for (i = 0; i < 6; i++)
        wyniki[i] = 0;

    for (i = 0; i < n; i++)
    {
        if (stopnie[i] == 2.0f)      wyniki[0]++;
        else if (stopnie[i] == 3.0f) wyniki[1]++;
        else if (stopnie[i] == 3.5f) wyniki[2]++;
        else if (stopnie[i] == 4.0f) wyniki[3]++;
        else if (stopnie[i] == 4.5f) wyniki[4]++;
        else if (stopnie[i] == 5.0f) wyniki[5]++;
    }
}

int main()
{
    float punkty[MAX_OCEN], stopnie[MAX_OCEN], sr, minP, maxP;
    int n, wynikiStopni[6], i;
    const char *nazwyStopni[6] = {"2.0", "3.0", "3.5", "4.0", "4.5", "5.0"};

    czytaj("Podaj liczbe studentow i ich punkty (0-40):", &n, punkty);
    drukuj("Punkty studentow:", n, punkty);

    srednia(n, punkty, &sr);
    printf("\nSrednia: %.2f\n", sr);
    printf("Powyzej sredniej: %d osob.\n", liczba(n, punkty, sr));

    printf("Procent w przedziale [0.3*sr, 0.7*sr]: %.2f%%\n",
           procentWPrzedziale(n, punkty, sr));

    minMaxOcena(n, punkty, &minP, &maxP);
    printf("Minimalna liczba punktow: %.2f\n", minP);
    printf("Maksymalna liczba punktow: %.2f\n", maxP);

    wyznaczStopnie(n, punkty, stopnie);
    drukuj("\nStopnie studentow:", n, stopnie);

    zliczStopnie(n, stopnie, wynikiStopni);
    printf("\nLiczba osob z poszczegolnymi stopniami:\n");
    for (i = 0; i < 6; i++)
        printf("Stopien %s: %d osob\n", nazwyStopni[i], wynikiStopni[i]);

    return EXIT_SUCCESS;
}
