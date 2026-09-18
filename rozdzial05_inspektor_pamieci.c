#include <stdio.h>
#include <string.h>

int main() {
    printf("\n╔═══════════════════════════════════╗\n");
    printf("║  🧠 INSPEKTOR PAMIĘCI 🧠           ║\n");
    printf("╚═══════════════════════════════════╝\n\n");

    int x = 42;
    int y = 1337;
    int *wskaznik = &x;
    int *wskaznik2 = &y;

    printf("📍 ANALIZA PAMIĘCI:\n\n");

    printf("Zmienna X:\n");
    printf("  Nazwa:      x\n");
    printf("  Wartość:    %d\n", x);
    printf("  Adres:      %p\n", (void*)&x);
    printf("  Rozmiar:    %ld bajtów\n\n", sizeof(x));

    printf("Wskaźnik na X:\n");
    printf("  Zmienna:    wskaznik\n");
    printf("  Wskazuje:   %p (adres x)\n", (void*)wskaznik);
    printf("  Zawartość:  %d (wartość x)\n", *wskaznik);
    printf("  Adres wskaznika: %p\n\n", (void*)&wskaznik);

    /* Zmiana zmiennej przez wskaźnik */
    printf("⚡ MODYFIKACJA PRZEZ WSKAŹNIK:\n");
    printf("  Zmiana: *wskaznik = 99\n");
    *wskaznik = 99;
    printf("  Rezultat: x = %d (zmieniliśmy przez wskaźnik!)\n", x);
    printf("  Dowód: wskaznik wskazuje na x!\n\n");

    return 0;
}
