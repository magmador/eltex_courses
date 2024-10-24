#include "PreCreatedHead.h"

void time_cli(int sockfd)
{
  ssize_t n;
  char sendBuff[MAX_LEN], recvBuff[MAX_LEN];
  if(n = recv(sockfd, recvBuff, sizeof(recvBuff)-1, 0) == -1)
  {
    printf("recv error\n");
    exit(0);
  }
  if(strcmp(recvBuff, "time_offer"))
  {
    printf("got wrong message from server: %s end\n", sendBuff);
    exit(0);
  }
  bzero(&sendBuff, sizeof(sendBuff));

  snprintf(sendBuff, sizeof(sendBuff), "time_req");
  if ((n = send(sockfd, sendBuff, strlen(sendBuff), 0)) == -1)
  {
    printf("write error\n");
    exit(0);
  }
  if(n = recv(sockfd, recvBuff, sizeof(recvBuff)-1, 0) == -1)
  {
    printf("recv error\n");
    exit(0);
  }
  printf("%s \n", recvBuff);
}
