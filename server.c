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
    socklen_t size;
    char buf[1024];
    struct sockaddr_in broadcast;

    size = sizeof(struct sockaddr_in);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        fprintf(stderr, "Incorrect server socket\n");
        exit(1);
    }

    broadcast.sin_family = AF_INET;
    broadcast.sin_port = htons(0xAABB);
    broadcast.sin_addr.s_addr = inet_addr("192.168.1.100");
    
    if (bind(sock, (struct sockaddr*) &broadcast, size) == -1)
    {
        fprintf(stderr, "Incorrect server bind\n");
        exit(1);
    }

    while (1)
    {
        if(recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*) &broadcast, &size) == -1)
        {
            fprintf(stderr, "Incorrect server recv\n");
            exit(1);
        }

        printf("%s", buf);
    }
    shutdown(sock, SHUT_RDWR);

    return 0;
}
