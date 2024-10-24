#include "Epollheader.h"

void time_echo(int sockfd)
{
  time_t ticks;
  ssize_t n;
  char recvBuff[MSG_MAX_LEN];

  if(n = recv(sockfd, recvBuff, sizeof(recvBuff)-1, 0) != -1)
  {
    printf("server got '%s' \n", recvBuff);
  }
  if(n > MSG_MAX_LEN)
  {
    perror("something left in socket");
  }
}
