#ifndef PRECREATED
#define PRECREATED

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <malloc.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#define SERV_PORT 5555
#define MAX_LEN 50
#define LISTEN_Q 10

int nchildren;
pid_t *childpid;

pid_t child_make(int i, int listenfd, int addrlen);
void  child_main(int i, int listenfd, int addrlen);
void  web_child(int sockfd);
void time_cli(int sockfd);
void  sig_int(int signo);

#endif
