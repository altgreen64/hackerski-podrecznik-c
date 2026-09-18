#include <stdio.h>
#include <string.h>

#define MAX_DLUGOSC 256

/* Długości podajemy jawnie, żeby bajt 0x00 powstały w trakcie szyfrowania
   nie oszukał strlen() i nie uciął wiadomości w połowie */
void xor_szyfruj(char *tekst, int dl_tekstu, const char *klucz, int dl_klucza) {
    for (int i = 0; i < dl_tekstu; i++) {
        tekst[i] ^= klucz[i % dl_klucza];
    }
}

int main() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  🔐 SZYFR XOR - TAJNA WIADOMOŚĆ 🔐       ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    char wiadomosc[MAX_DLUGOSC] = "SPOTKANIE_O_PORCE_TRZECIEJ";
    const char *klucz = "H4ck3r";

    int dl_wiad = strlen(wiadomosc);
    int dl_klucz = strlen(klucz);

    printf("Oryginał: %s\n", wiadomosc);
    printf("Klucz:    %s\n\n", klucz);

    xor_szyfruj(wiadomosc, dl_wiad, klucz, dl_klucz);

    printf("Zaszyfrowane (bajty hex): ");
    for (int i = 0; i < dl_wiad; i++) {
        printf("%02X ", (unsigned char)wiadomosc[i]);
    }
    printf("\n\n");

    xor_szyfruj(wiadomosc, dl_wiad, klucz, dl_klucz);   /* XOR jest symetryczny */
    wiadomosc[dl_wiad] = '\0';

    printf("Odszyfrowane: %s\n\n", wiadomosc);

    return 0;
}
