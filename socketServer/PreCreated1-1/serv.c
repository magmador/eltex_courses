#include "PreCreatedHead.h"

int main(int argc, char **argv)
{
  int listenfd;
  socklen_t addrlen;
  struct sockaddr_in servaddr;
  if(argc < 1)
  {
    printf("usage: serv <Number of children>\n");
    exit(0);
  }

  nchildren = atoi(argv[1]);
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  listen(listenfd, LISTEN_Q);
  childpid = calloc(nchildren, sizeof(pid_t));

  for(size_t i = 0; i < nchildren; i++)
  {
    childpid[i] = child_make(i, listenfd, addrlen);
  }
  signal(SIGINT, sig_int);
  for(;;)
  {
    pause();
  }
}
