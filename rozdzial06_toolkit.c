#include <stdio.h>
#include <string.h>

/* NARZĘDZIE 1: prosty hash tekstu (algorytm djb2) */
unsigned long prosty_hash(const char *tekst) {
    unsigned long hash = 5381;
    int znak;
    while ((znak = *tekst++)) {
        hash = ((hash << 5) + hash) + znak;   /* hash * 33 + znak */
    }
    return hash;
}

/* NARZĘDZIE 2: maskowanie XOR - działa "w miejscu" na buforze */
void xor_maskuj(char *bufor, char klucz) {
    for (int i = 0; bufor[i] != '\0'; i++) {
        bufor[i] ^= klucz;
    }
}

/* NARZĘDZIE 3: suma kontrolna bajtów */
int suma_kontrolna(const char *bufor) {
    int suma = 0;
    for (int i = 0; bufor[i] != '\0'; i++) {
        suma += (unsigned char)bufor[i];
    }
    return suma;
}

int main() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  🧰 HACKERSKI TOOLKIT 🧰                ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    char wiadomosc[] = "ATAK_O_SWICIE";
    char klucz = 0x2A;

    printf("Wiadomość źródłowa: %s\n\n", wiadomosc);

    printf("[NARZĘDZIE 1] Hash (djb2):     %lu\n", prosty_hash(wiadomosc));
    printf("[NARZĘDZIE 3] Suma kontrolna:  %d\n\n", suma_kontrolna(wiadomosc));

    printf("[NARZĘDZIE 2] Maskowanie XOR (klucz 0x%02X)...\n", klucz);
    xor_maskuj(wiadomosc, klucz);
    printf("  Zamaskowane (jako liczby): ");
    for (int i = 0; wiadomosc[i] != '\0'; i++) printf("%d ", (unsigned char)wiadomosc[i]);
    printf("\n");

    xor_maskuj(wiadomosc, klucz);   /* XOR drugi raz = odszyfrowanie */
    printf("  Odzyskana wiadomość:       %s\n\n", wiadomosc);

    printf("💡 Każde narzędzie to osobna funkcja - tak buduje się prawdziwe\n");
    printf("   frameworki hakerskie: małe, wymienne moduły.\n\n");

    return 0;
}
