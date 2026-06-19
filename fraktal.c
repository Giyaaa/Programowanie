#include <stdlib.h>
#include <stdio.h>

int main()
{
    const int dX = 512;
    const int dY = 512;
    const int maxIter = 100;
    const char *plikNazwa = "fraktal.ppm";
    int i, j, iter;
    unsigned char color[3];
    FILE *plikWsk;
    double cRe, cIm, zRe, zIm, zReNowe;

    plikWsk = fopen(plikNazwa, "wb");
    if (plikWsk == NULL)
    {
        printf("Blad tworzenia pliku.");
        return EXIT_FAILURE;
    }

    /* naglowek pliku PPM (tak jak w przykladzie) */
    fprintf(plikWsk, "P6\n%d %d\n255\n", dX, dY);

    for (j = 0; j < dY; ++j)
    {
        for (i = 0; i < dX; ++i)
        {
            /* przeskalowujemy wspolrzedne piksela (i, j) na fragment
               plaszczyzny zespolonej, w ktorym widac caly fraktal */
            cRe = (i - dX / 2.0) * 4.0 / dX;
            cIm = (j - dY / 2.0) * 4.0 / dY;

            /* startujemy z z = 0 i liczymy z = z^2 + c wielokrotnie */
            zRe = 0.0;
            zIm = 0.0;
            iter = 0;

            while (zRe * zRe + zIm * zIm < 4.0 && iter < maxIter)
            {
                zReNowe = zRe * zRe - zIm * zIm + cRe;
                zIm = 2.0 * zRe * zIm + cIm;
                zRe = zReNowe;
                iter++;
            }

            if (iter == maxIter)
            {
                /* punkt nalezy do zbioru Mandelbrota -> kolor czarny */
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            }
            else
            {
                /* punkt poza zbiorem -> kolor zalezny od liczby iteracji
                   (jak szybko "uciekl" w nieskonczonosc) */
                color[0] = (unsigned char)((iter * 5) % 256);
                color[1] = (unsigned char)((iter * 9) % 256);
                color[2] = (unsigned char)((iter * 13) % 256);
            }

            fwrite(color, 1, 3, plikWsk);
        }
    }

    fclose(plikWsk);

    printf("Zapisano fraktal do pliku \"%s\".\n", plikNazwa);

    return EXIT_SUCCESS;
}
