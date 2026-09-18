#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define MAX_ZNAKOW 100

int main() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  ⌨️  MINI KEYLOGGER (DEMO LOKALNE) ⌨️    ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    printf("Pisz co chcesz. Naciśnij ESC aby zakończyć.\n\n");

    char przechwycone[MAX_ZNAKOW];
    int licznik = 0;

    struct termios stare_ustawienia, nowe_ustawienia;
    int tryb_terminala = isatty(STDIN_FILENO);

    if (tryb_terminala) {
        tcgetattr(STDIN_FILENO, &stare_ustawienia);
        nowe_ustawienia = stare_ustawienia;
        nowe_ustawienia.c_lflag &= ~(ICANON | ECHO);   /* wyłącz bufor linii i echo */
        tcsetattr(STDIN_FILENO, TCSANOW, &nowe_ustawienia);
    }

    int znak;
    while (licznik < MAX_ZNAKOW - 1 && (znak = getchar()) != EOF) {
        if (znak == 27) break;   /* ESC */

        przechwycone[licznik++] = (char)znak;
        printf("[PRZECHWYCONO] kod=%d znak='%c'\n", znak, (znak >= 32 && znak < 127) ? znak : '?');
    }
    przechwycone[licznik] = '\0';

    if (tryb_terminala) {
        tcsetattr(STDIN_FILENO, TCSANOW, &stare_ustawienia);
    }

    printf("\n════════════════════════════════════\n");
    printf("Przechwycono %d znaków: %s\n", licznik, przechwycone);
    printf("════════════════════════════════════\n\n");

    return 0;
}
