#include <stdio.h>

int main() {
    int pin_docelowy = 4269;
    int znaleziony = 0;

    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  🔓 BRUTE FORCE - PIN 4-CYFROWY 🔓      ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    printf("Cel: znaleźć PIN metodą pełnego przeglądu (0000-9999)\n\n");

    for (int proba = 0; proba <= 9999; proba++) {
        if (proba % 1000 == 0) {
            printf("[...] Sprawdzam zakres %04d - %04d\n", proba, proba + 999);
        }

        if (proba == pin_docelowy) {
            printf("\n✅ PIN ZNALEZIONY: %04d\n", proba);
            printf("Liczba prób: %d\n", proba + 1);
            znaleziony = 1;
            break;
        }
    }

    if (!znaleziony) {
        printf("\n❌ Nie znaleziono PIN-u w podanym zakresie.\n");
    }

    printf("\nMaksymalna liczba możliwych kombinacji: 10000\n");
    printf("Wniosek: 4-cyfrowy PIN można złamać w ułamku sekundy!\n\n");

    return 0;
}
