#include "PreCreatedHead.h"

void  child_main(int i, int listenfd, int addrlen)
{
  int connfd;
  socklen_t clilen;
  struct sockaddr *cliaddr;
  cliaddr = (struct sockaddr *)malloc(addrlen);
  printf("child %ld starting\n", (long) getpid());

  for(;;)
  {
    clilen = addrlen;
    connfd = accept(listenfd, cliaddr, &clilen);
    web_child(connfd); //сама обработка чайлдом запроса
    close(connfd);
  }
}
