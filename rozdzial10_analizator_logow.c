#include <stdio.h>
#include <string.h>

#define MAX_LINIA 256

int main() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  📁 ANALIZATOR LOGÓW SYSTEMOWYCH 📁     ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    /* KROK 1: tworzymy przykładowy log (symulacja ataku) */
    FILE *log = fopen("system.log", "w");
    if (!log) { printf("Błąd tworzenia pliku logu!\n"); return 1; }

    fprintf(log, "10:01:02 LOGIN OK      user=admin ip=192.168.1.5\n");
    fprintf(log, "10:01:15 FAILED LOGIN  user=admin ip=45.33.12.9\n");
    fprintf(log, "10:01:16 FAILED LOGIN  user=admin ip=45.33.12.9\n");
    fprintf(log, "10:01:17 FAILED LOGIN  user=root  ip=45.33.12.9\n");
    fprintf(log, "10:01:20 LOGIN OK      user=biuro ip=192.168.1.9\n");
    fprintf(log, "10:01:44 FAILED LOGIN  user=admin ip=91.203.5.1\n");
    fclose(log);

    printf("[+] Utworzono system.log (symulowany log serwera)\n\n");

    /* KROK 2: analizujemy log linia po linii */
    FILE *odczyt = fopen("system.log", "r");
    FILE *raport = fopen("raport_ataku.txt", "w");
    if (!odczyt || !raport) { printf("Błąd otwierania plików!\n"); return 1; }

    char linia[MAX_LINIA];
    int nieudane_logowania = 0;
    int linia_nr = 0;

    fprintf(raport, "RAPORT ANALIZY LOGOW\n");
    fprintf(raport, "=====================\n\n");

    while (fgets(linia, sizeof(linia), odczyt)) {
        linia_nr++;
        if (strstr(linia, "FAILED LOGIN") != NULL) {
            nieudane_logowania++;
            fprintf(raport, "[PODEJRZANE] linia %d: %s", linia_nr, linia);
            printf("🚨 Wykryto nieudane logowanie (linia %d)\n", linia_nr);
        }
    }

    fprintf(raport, "\nPodsumowanie: %d nieudanych prob logowania.\n", nieudane_logowania);
    fclose(odczyt);
    fclose(raport);

    printf("\n[+] Zapisano raport do: raport_ataku.txt\n");
    printf("[+] Wykryto łącznie %d nieudanych prób logowania.\n\n", nieudane_logowania);

    if (nieudane_logowania >= 3) {
        printf("⚠️  UWAGA: liczba nieudanych prób sugeruje możliwy atak brute force!\n\n");
    }

    return 0;
}
