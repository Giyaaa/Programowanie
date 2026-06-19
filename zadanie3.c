#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main()
{
    char nazwaPliku[256];
    FILE *plikWsk;
    int znak;

    printf("Podaj nazwe pliku: ");
    scanf("%255s", nazwaPliku);

    plikWsk = fopen(nazwaPliku, "r");
    if (plikWsk == NULL)
    {
        printf("Blad otwarcia pliku.\n");
        return EXIT_FAILURE;
    }

    /* czytamy plik znak po znaku */
    while ((znak = fgetc(plikWsk)) != EOF)
    {
        /* isspace() rozpoznaje spacje, tabulacje, znaki konca linii itp. */
        /* wypisujemy znak tylko wtedy, gdy NIE jest bialym znakiem */
        if (!isspace(znak))
        {
            putchar(znak);
        }
    }

    fclose(plikWsk);

    return EXIT_SUCCESS;
}
