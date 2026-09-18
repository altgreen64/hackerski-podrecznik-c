#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>

/* Sprawdza pojedynczy port w trybie nieblokującym + select(),
   żeby zamknięte/filtrowane porty nie blokowały skanera na sekundy */
int czy_port_otwarty(const char *ip, int port, int timeout_sek) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return 0;

    int flagi = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flagi | O_NONBLOCK);

    struct sockaddr_in adres;
    memset(&adres, 0, sizeof(adres));
    adres.sin_family = AF_INET;
    adres.sin_port = htons(port);
    inet_pton(AF_INET, ip, &adres.sin_addr);

    connect(sock, (struct sockaddr *)&adres, sizeof(adres));

    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(sock, &fdset);

    struct timeval tv;
    tv.tv_sec = timeout_sek;
    tv.tv_usec = 0;

    int otwarty = 0;
    if (select(sock + 1, NULL, &fdset, NULL, &tv) > 0) {
        int blad = 0;
        socklen_t len = sizeof(blad);
        getsockopt(sock, SOL_SOCKET, SO_ERROR, &blad, &len);
        if (blad == 0) otwarty = 1;
    }

    close(sock);
    return otwarty;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Użycie: %s <IP> <port_start> <port_end>\n", argv[0]);
        printf("Przykład: %s 127.0.0.1 1 1024\n", argv[0]);
        printf("\n⚠️  Skanuj TYLKO systemy, do których masz uprawnienia!\n");
        return 1;
    }

    const char *ip = argv[1];
    int start = atoi(argv[2]);
    int koniec = atoi(argv[3]);

    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  🎯 SKANER PORTÓW TCP 🎯                ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    printf("Cel: %s | Zakres portów: %d-%d\n\n", ip, start, koniec);

    int otwarte = 0;
    for (int port = start; port <= koniec; port++) {
        if (czy_port_otwarty(ip, port, 1)) {
            printf("[✓] Port %-5d OTWARTY\n", port);
            otwarte++;
        }
    }

    printf("\nSkanowanie zakończone. Znaleziono %d otwartych portów.\n\n", otwarte);
    return 0;
}
