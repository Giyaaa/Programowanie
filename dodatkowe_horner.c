#include <stdio.h>
#include <stdlib.h>

/* Konwencja: wsp[0] to wspolczynnik przy najwyzszej potedze (an),
   wsp[st] to wyraz wolny (a0). Stopien wielomianu to "st".          */

/* wartosc wielomianu - wersja REKURENCYJNA (z tresci zadania) */
int hornerRek(int wsp[], int st, int x)
{
    if (st == 0)
        return wsp[0];
    return x * hornerRek(wsp, st - 1, x) + wsp[st];
}

/* wartosc wielomianu - wersja ITERACYJNA (rownowazna powyzszej) */
int hornerIter(int wsp[], int st, int x)
{
    int i, wynik = wsp[0];

    for (i = 1; i <= st; i++)
        wynik = wynik * x + wsp[i];

    return wynik;
}

/* liczy wspolczynniki pochodnej wielomianu, zapisuje je w wspPochodnej[],
   zwraca stopien pochodnej (o 1 mniejszy niz oryginal) */
int pochodna(int wsp[], int st, int wspPochodnej[])
{
    int i;

    if (st == 0)
    {
        wspPochodnej[0] = 0;   /* pochodna stalej wynosi 0 */
        return 0;
    }

    /* wspolczynnik przy x^(n-k) w oryginale daje po pochodnej
       wspolczynnik (n-k)*wsp[k] przy x^(n-k-1)                 */
    for (i = 0; i < st; i++)
        wspPochodnej[i] = (st - i) * wsp[i];

    return st - 1;
}

int main()
{
    /* przykladowy wielomian: w(x) = 3x^2 + 2x + 5 */
    int wsp[] = {3, 2, 5};
    int st = 2;
    int x = 4;
    int wspPochodnej[10];
    int stPochodnej, i;

    printf("Wielomian: w(x) = 3x^2 + 2x + 5\n\n");

    printf("Wartosc w(%d) (rekurencyjnie): %d\n", x, hornerRek(wsp, st, x));
    printf("Wartosc w(%d) (iteracyjnie):   %d\n\n", x, hornerIter(wsp, st, x));

    stPochodnej = pochodna(wsp, st, wspPochodnej);

    printf("Pochodna ma stopien %d, wspolczynniki (od najwyzszej potegi): ", stPochodnej);
    for (i = 0; i <= stPochodnej; i++)
        printf("%d ", wspPochodnej[i]);
    printf("\n\n");

    printf("Wartosc pochodnej w'(%d): %d\n", x, hornerIter(wspPochodnej, stPochodnej, x));

    return EXIT_SUCCESS;
}
