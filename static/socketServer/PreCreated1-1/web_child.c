#include "PreCreatedHead.h"

void  web_child(int sockfd)
{
  time_t ticks;
  ssize_t n;
  char sendBuff[MAX_LEN], recvBuff[MAX_LEN];
  ticks = time(NULL);
  snprintf(sendBuff, sizeof(sendBuff), "time_offer");
  if(send(sockfd, sendBuff, strlen(sendBuff), 0) != -1)
  {
      printf("sent successfully %s...\n", sendBuff);
  }
  bzero(&sendBuff, sizeof(sendBuff));

  if(n = recv(sockfd, recvBuff, sizeof(recvBuff)-1, 0) != -1)
  {
    printf("server got %s \n", recvBuff);
  }
  if (!strcmp("time_req", recvBuff))
  {
    snprintf(sendBuff, sizeof(sendBuff), "%.24s", ctime(&ticks));
    if ((n = send(sockfd, sendBuff, strlen(sendBuff), 0)) != -1)
    {
      printf("time sent successfully... \n");
    }
  }
}
