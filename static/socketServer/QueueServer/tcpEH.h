#ifndef TCP_EH
#define TCP_EH

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#define SERV_PORT 5555
#define MAX_LEN 50
#define LISTEN_Q 10
#define NO_FLAGS 0

int idQueue;
int listenfd;

void time_echo(int sockfd);
void time_cli(int sockfd);
void sig_int(int signo);

#endif
