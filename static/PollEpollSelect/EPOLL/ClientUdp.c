#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>

#define SOCK_PORT 5556

int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0;
    struct sockaddr_in addr;

    if(argc != 2) {
        printf("\n Usage: %s <ip of server> \n", argv[0]);
        return 1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SOCK_PORT);
    if(inet_pton(AF_INET, argv[1], &(addr.sin_addr)) < 0)
    {
      perror("inet_pton\n");
      exit(EXIT_FAILURE);
    }

    if(sendto(sockfd, "helloUDP", sizeof("helloTCP"), 0, (struct sockaddr *)&addr, sizeof(addr)) != -1)
    {
      printf("sent successfully\n");
    }
    else printf("sending problem\n");

    close(sockfd);
    return 0;
}
