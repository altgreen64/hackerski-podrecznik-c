#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

#define MAX_HOSTS 254
#define TIMEOUT_SEC 1

typedef struct {
    int fd;
    int host_octet;
    int done;
    int open;
} probe_t;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uzycie: %s <podsiec np. 192.168.1> [port]\n", argv[0]);
        return 1;
    }
    const char *subnet = argv[1];
    int port = argc >= 3 ? atoi(argv[2]) : 22;

    probe_t probes[MAX_HOSTS];
    int active = 0;

    for (int i = 1; i <= MAX_HOSTS; i++) {
        char ip[32];
        snprintf(ip, sizeof(ip), "%s.%d", subnet, i);

        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd < 0) continue;

        int flags = fcntl(fd, F_GETFL, 0);
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, ip, &addr.sin_addr);

        connect(fd, (struct sockaddr *)&addr, sizeof(addr));

        probes[active].fd = fd;
        probes[active].host_octet = i;
        probes[active].done = 0;
        probes[active].open = 0;
        active++;
    }

    struct timeval deadline;
    gettimeofday(&deadline, NULL);
    deadline.tv_sec += TIMEOUT_SEC;

    int remaining = active;
    while (remaining > 0) {
        fd_set wfds;
        FD_ZERO(&wfds);
        int maxfd = -1;
        for (int i = 0; i < active; i++) {
            if (!probes[i].done) {
                FD_SET(probes[i].fd, &wfds);
                if (probes[i].fd > maxfd) maxfd = probes[i].fd;
            }
        }
        if (maxfd == -1) break;

        struct timeval now, tv;
        gettimeofday(&now, NULL);
        long usec_left = (deadline.tv_sec - now.tv_sec) * 1000000L + (deadline.tv_usec - now.tv_usec);
        if (usec_left <= 0) break;
        tv.tv_sec = usec_left / 1000000L;
        tv.tv_usec = usec_left % 1000000L;

        int ready = select(maxfd + 1, NULL, &wfds, NULL, &tv);
        if (ready <= 0) break;

        for (int i = 0; i < active; i++) {
            if (!probes[i].done && FD_ISSET(probes[i].fd, &wfds)) {
                int err = 0;
                socklen_t len = sizeof(err);
                getsockopt(probes[i].fd, SOL_SOCKET, SO_ERROR, &err, &len);
                probes[i].open = (err == 0);
                probes[i].done = 1;
                remaining--;
            }
        }
    }

    printf("Skanowanie %s.0/24 port %d:\n", subnet, port);
    int found = 0;
    for (int i = 0; i < active; i++) {
        if (probes[i].open) {
            printf("  %s.%d -> port %d OTWARTY\n", subnet, probes[i].host_octet, port);
            found++;
        }
        close(probes[i].fd);
    }
    if (!found) printf("  Brak hostow z otwartym portem %d.\n", port);

    return 0;
}
