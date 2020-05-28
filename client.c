#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

int main(int argc, char *argv[]) 
{
    int sock;
    int size;
    int check;
    char buf[1024];
    struct sockaddr_in broadcast;

    size = sizeof(struct sockaddr_in);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        fprintf(stderr, "Incorrect client socket\n");
        exit(1);
    }

    broadcast.sin_family = AF_INET;
    broadcast.sin_port = htons(0xAABB);
    broadcast.sin_addr.s_addr = INADDR_BROADCAST;

    check = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &check, sizeof(check)) == -1)
    {
        fprintf(stderr, "Incorrect client setsockopt\n");
        exit(1);
    }

    puts("Enter broadcast message:");

    fgets(buf, 1024, stdin);
    if (sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*) &broadcast, size) == -1)
    {
        fprintf(stderr, "Incorrect client send\n");
        exit(1);
    }
    shutdown(sock, SHUT_RDWR);

    return 0;
}
