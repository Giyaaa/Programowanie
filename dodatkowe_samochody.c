#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AUT 50

/* date MUSI byc zdefiniowane przed car, bo car uzywa date jako typu pola */
typedef struct date
{
    int day;
    int month;
    int year;
} date;

typedef struct car
{
    char brand[30];
    char model[30];
    int year;
    date regDate;   /* struktura zagniezdzona */
} car;

/* drukuje informacje o jednym samochodzie (wskaznik - zeby nie kopiowac
   calej struktury przy kazdym wywolaniu) */
void drukujSamochod(const car *c)
{
    printf("%s %s (%d), data rejestracji: %02d-%02d-%d\n",
           c->brand, c->model, c->year,
           c->regDate.day, c->regDate.month, c->regDate.year);
}

/* drukuje informacje o wszystkich samochodach w tablicy */
void drukujWszystkieSamochody(const car tab[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d. ", i + 1);
        drukujSamochod(&tab[i]);
    }
}

/* pozwala uzytkownikowi dodac samochod do tablicy (jesli jest miejsce) */
void dodajSamochod(car tab[], int *n, int maxRozmiar)
{
    car nowy;

    if (*n >= maxRozmiar)
    {
        printf("Brak miejsca w tablicy - nie mozna dodac kolejnego samochodu.\n");
        return;
    }

    printf("Marka: ");
    scanf("%29s", nowy.brand);

    printf("Model: ");
    scanf("%29s", nowy.model);

    printf("Rok produkcji: ");
    scanf("%d", &nowy.year);

    printf("Data rejestracji (dzien miesiac rok): ");
    scanf("%d %d %d", &nowy.regDate.day, &nowy.regDate.month, &nowy.regDate.year);

    tab[*n] = nowy;
    (*n)++;
}

/* zapisuje cala tablice samochodow do pliku binarnego jednym wywolaniem fwrite */
void zapiszDoPliku(const car tab[], int n, const char *nazwaPliku)
{
    FILE *plik = fopen(nazwaPliku, "wb");
    if (plik == NULL)
    {
        printf("Blad otwarcia pliku do zapisu.\n");
        return;
    }

    /* najpierw zapisujemy liczbe samochodow, zeby przy odczycie
       wiedziec ile rekordow nalezy wczytac */
    fwrite(&n, sizeof(int), 1, plik);
    fwrite(tab, sizeof(car), n, plik);

    fclose(plik);
    printf("Zapisano %d samochod(ow) do pliku \"%s\".\n", n, nazwaPliku);
}

/* odczytuje tablice samochodow z pliku binarnego */
void wczytajZPliku(car tab[], int *n, const char *nazwaPliku)
{
    FILE *plik = fopen(nazwaPliku, "rb");
    if (plik == NULL)
    {
        printf("Blad otwarcia pliku do odczytu.\n");
        return;
    }

    fread(n, sizeof(int), 1, plik);
    fread(tab, sizeof(car), *n, plik);

    fclose(plik);
    printf("Wczytano %d samochod(ow) z pliku \"%s\".\n", *n, nazwaPliku);
}

int main()
{
    car flota[MAX_AUT];
    int liczbaAut = 0;
    car wczytaneAuta[MAX_AUT];
    int wczytanaLiczba = 0;

    /* dwa samochody "na sztywno", zeby od razu bylo cos w tablicy */
    /* strcpy tylko do stringa */
    strcpy(flota[liczbaAut].brand, "Toyota");
    strcpy(flota[liczbaAut].model, "Corolla");
    flota[liczbaAut].year = 2019;
    flota[liczbaAut].regDate.day = 12;
    flota[liczbaAut].regDate.month = 6;
    flota[liczbaAut].regDate.year = 2019;
    liczbaAut++;

    strcpy(flota[liczbaAut].brand, "Ford");
    strcpy(flota[liczbaAut].model, "Focus");
    flota[liczbaAut].year = 2021;
    flota[liczbaAut].regDate.day = 3;
    flota[liczbaAut].regDate.month = 9;
    flota[liczbaAut].regDate.year = 2021;
    liczbaAut++;

    printf("=== Samochody na starcie ===\n");
    drukujWszystkieSamochody(flota, liczbaAut);

    /* uzytkownik dodaje kolejny samochod recznie */
    printf("\n=== Dodawanie nowego samochodu ===\n");
    dodajSamochod(flota, &liczbaAut, MAX_AUT);

    printf("\n=== Wszystkie samochody po dodaniu ===\n");
    drukujWszystkieSamochody(flota, liczbaAut);

    /* zapis do pliku binarnego */
    zapiszDoPliku(flota, liczbaAut, "samochody.bin");

    /* odczyt do nowej, pustej tablicy - zeby sprawdzic, czy zapis sie udal */
    wczytajZPliku(wczytaneAuta, &wczytanaLiczba, "samochody.bin");

    printf("\n=== Samochody odczytane z pliku ===\n");
    drukujWszystkieSamochody(wczytaneAuta, wczytanaLiczba);

    return EXIT_SUCCESS;
}
