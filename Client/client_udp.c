#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int n;

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }

    /* Create UDP socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(atoi(argv[2]));

    printf("Please enter the message: ");
    memset(buffer, 0, 1024);
    fgets(buffer, 1023, stdin);

    /* Send message */
    n = sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0)
        error("ERROR on sendto");

    /* Receive reply */
    memset(buffer, 0, 1024);
    n = recvfrom(sockfd, buffer, 1023, 0, NULL, NULL);
    if (n < 0)
        error("ERROR on recvfrom");

    printf("Reply from server: %s\n", buffer);

    close(sockfd);
    return 0;
}