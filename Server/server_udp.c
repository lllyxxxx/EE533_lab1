#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    int n;

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    /* Create UDP socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    printf("UDP server listening on port %s...\n", argv[1]);

    clilen = sizeof(cli_addr);

    while (1) {
        memset(buffer, 0, 1024);

        n = recvfrom(sockfd, buffer, 1023, 0,
                     (struct sockaddr *)&cli_addr, &clilen);
        if (n < 0)
            error("ERROR on recvfrom");

        printf("Message from client: %s\n", buffer);

        n = sendto(sockfd, "I got your message", 18, 0,
                   (struct sockaddr *)&cli_addr, clilen);
        if (n < 0)
            error("ERROR on sendto");
    }

    close(sockfd);
    return 0;
}
