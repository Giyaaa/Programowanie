#include <stdlib.h>
#include <stdio.h>

int main()
{
    char nazwaZrodlowa[256];
    const char *nazwaDocelowa = "kopia.txt";
    FILE *plikZrodlowy, *plikDocelowy;
    int znak;

    printf("Podaj nazwe pliku zrodlowego: ");
    /* %255s to string z ograniczeniem do 255 zanków */
    scanf("%255s", nazwaZrodlowa);

    /* otwieramy plik oryginalny do odczytu */
    plikZrodlowy = fopen(nazwaZrodlowa, "r");
    if (plikZrodlowy == NULL)
    {
        printf("Blad otwarcia pliku zrodlowego.\n");
        return EXIT_FAILURE;
    }

    /* otwieramy/tworzymy plik docelowy do zapisu*/
    plikDocelowy = fopen(nazwaDocelowa, "w");
    if (plikDocelowy == NULL)
    {
        printf("Blad utworzenia pliku docelowego.\n");
        fclose(plikZrodlowy);
        return EXIT_FAILURE;
    }

    /* czytamy plik znak po znaku az do konca pliku (EOF) */
    /* fgetc czyta jeden znak */
    while ((znak = fgetc(plikZrodlowy)) != EOF)
    {
        /* fputc zapisuje ten znak do tego pliku */
        fputc(znak, plikDocelowy);
    }

    fclose(plikZrodlowy);
    fclose(plikDocelowy);

    printf("Zawartosc skopiowano do pliku \"%s\".\n", nazwaDocelowa);

    return EXIT_SUCCESS;
}
