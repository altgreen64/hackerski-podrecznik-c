#include <stdio.h>

int main() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  🔑 GENERATOR KLUCZY DOSTĘPU 🔑         ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    /* Podstawowe typy i arytmetyka */
    unsigned int seed = 1337;
    unsigned char klucz_xor = 0xA5;
    int id_agenta = 7;

    printf("SEED (unsigned int): %u\n", seed);
    printf("ID_AGENTA (int):     %d\n\n", id_agenta);

    /* Prosty generator "losowego" kodu dostępu - czysta arytmetyka modularna */
    unsigned int kod = (seed * 1103515245u + 12345u) % 10000u;
    printf("Wygenerowany kod dostępu (4 cyfry): %04u\n\n", kod);

    /* Operacje bitowe - fundament szyfrowania XOR */
    unsigned char tajny_bajt = 'H';
    unsigned char zaszyfrowany = tajny_bajt ^ klucz_xor;
    unsigned char odszyfrowany = zaszyfrowany ^ klucz_xor;

    printf("⚙️  OPERACJE BITOWE (XOR):\n");
    printf("  Oryginalny bajt:     '%c' (%d)\n", tajny_bajt, tajny_bajt);
    printf("  Klucz XOR:           0x%02X\n", klucz_xor);
    printf("  Zaszyfrowany:        %d\n", zaszyfrowany);
    printf("  Odszyfrowany:        '%c' (%d)\n\n", odszyfrowany, odszyfrowany);

    /* Przesunięcia bitowe */
    printf("⚙️  PRZESUNIĘCIA BITOWE:\n");
    printf("  1 << 4   = %d  (mnożenie przez 16)\n", 1 << 4);
    printf("  256 >> 3 = %d  (dzielenie przez 8)\n\n", 256 >> 3);

    return 0;
}
