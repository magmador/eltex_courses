#include "tcpEH.h"

void time_echo(int sockfd)
{
  time_t ticks;
  ssize_t n;
  char sendBuff[MAX_LEN], recvBuff[MAX_LEN];
  ticks = time(NULL);
  snprintf(sendBuff, sizeof(sendBuff), "time_offer");
  pid_t mypid = getpid();
  if(send(sockfd, sendBuff, strlen(sendBuff), 0) != -1)
  {
      printf("[%d] sent successfully '%s'...\n", mypid, sendBuff);
  }
  else
  {
    printf("[%d] sent error '%s'\n", mypid, strerror(errno));
  }
  bzero(&sendBuff, sizeof(sendBuff));

  if(n = recv(sockfd, recvBuff, sizeof(recvBuff)-1, 0) != -1)
  {
    if(strlen(recvBuff) == 0)
    {
      printf("\n\033[1;31m");
    }
    printf("[%d] server got '%s' \n", mypid, recvBuff);
    if(strlen(recvBuff) == 0)
    {
      printf("\033[0m\n");
    }
  }
  else
  {
    printf("[%d] sent error '%s'\n", mypid, strerror(errno));
  }
  if (!strcmp("time_req", recvBuff))
  {
    snprintf(sendBuff, sizeof(sendBuff), "%.24s", ctime(&ticks));
    if ((n = send(sockfd, sendBuff, strlen(sendBuff), 0)) != -1)
    {
      printf("[%d] time sent...\n", mypid);
    }
    else
    {
      printf("[%d] sent error '%s'\n", mypid, strerror(errno));
    }
  }
}
