#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MSG_MAX_LEN 1024
#define EPOLL_QUEUE_LEN 10
#define SOCK_PORT_TCP 5555
#define SOCK_PORT_UDP 5556
#define MAX_EVENTS 10

void time_echo(int sockfd);
