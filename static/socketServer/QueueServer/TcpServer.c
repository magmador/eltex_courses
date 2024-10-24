#include "tcpEH.h"

typedef struct
{
  long mtype;
  int socketfd;
} msgBuf;

int main(int argc, char **argv)
{
  signal(SIGINT, sig_int);
  extern int listenfd;
  extern int idQueue;
  int connfd;
  pid_t childpid;
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  listen(listenfd, LISTEN_Q);

  if ((idQueue = msgget(ftok("TcpServer", 1), 0600 | IPC_CREAT)) != -1)
  {
      printf("Queue was created\n");
  }
  else
  {
      printf("Queue was not created\n");
  }

  int childernCount = 0;
  msgBuf msgToChild;
  for(;;)
  {
    clilen = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
    if(connfd == -1)
    {
      printf("accept error\n");
      continue;
    }
    if((childpid = fork()) == 0) // дочерний процесс
    {
      close(listenfd);
      msgBuf msgFromServer;
      msgrcv(idQueue, &msgFromServer, sizeof(msgFromServer.socketfd), getpid(), NO_FLAGS);
      time_echo(msgFromServer.socketfd);
      exit(0);
    }
    else
    {
      close(connfd);
      msgToChild.mtype = childpid;
      msgToChild.socketfd = connfd;
      msgsnd(idQueue, &msgToChild, sizeof(msgToChild.socketfd), NO_FLAGS);
    }
  }
  exit(0);
}
