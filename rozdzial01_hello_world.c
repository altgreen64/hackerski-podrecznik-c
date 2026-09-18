#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    printf("\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║    🎩 TRYB HAKERA AKTYWNY 🎩     ║\n");
    printf("╚════════════════════════════════════╝\n\n");

    printf("████████░░ 50%%  Inicjalizacja...\n");
    sleep(1);
    printf("██████████ 100%% Ukończone!\n\n");

    printf("Cześć Świecie!\n");
    printf("Status: [✓] ONLINE\n");
    printf("Użytkownik: Anonimowy\n");
    printf("IP: 127.0.0.1\n");
    printf("Uprzywilejowanie: ROOT\n\n");

    /* Tajemnica - ukryta wiadomość */
    char tajna[] = "Znalazles_tajne_info!";
    printf("[DEBUG] Odkryłeś tajną wiadomość: %s\n\n", tajna);

    printf("════════════════════════════════════\n");
    printf("System uruchomiony. Wpisz komendy:\n");
    printf("════════════════════════════════════\n");

    return 0;
}