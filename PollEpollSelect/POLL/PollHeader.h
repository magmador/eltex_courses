#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>


#define MAX_NUMBER_OF_CLIENTS 2
#define EPOLL_QUEUE_LEN 10
#define SOCK_PORT_TCP 5555
#define SOCK_PORT_UDP 5556
#define MSG_MAX_LEN 1024
#define MAX_EVENTS 10

void time_echo(int sockfd);
