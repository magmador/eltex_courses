#include "tcpEH.h"

void time_echo(int sockfd, struct sockaddr_in cliaddr)
{
  time_t ticks;
  ssize_t n;
  char sendBuff[MAX_LEN], recvBuff[MAX_LEN];
  ticks = time(NULL);
  snprintf(sendBuff, sizeof(sendBuff), "time_offer");
  if(send(sockfd, sendBuff, strlen(sendBuff), 0) != -1)
  {
      printf("sent successfully %s to %s...\n", sendBuff, inet_ntoa(cliaddr.sin_addr));
  }
  bzero(&sendBuff, sizeof(sendBuff));

  if(n = recv(sockfd, recvBuff, sizeof(recvBuff)-1, 0) != -1)
  {
    printf("server got %s from %s \n", recvBuff, inet_ntoa(cliaddr.sin_addr));
  }
  if (!strcmp("time_req", recvBuff))
  {
    snprintf(sendBuff, sizeof(sendBuff), "%.24s", ctime(&ticks));
    if ((n = send(sockfd, sendBuff, strlen(sendBuff), 0)) != -1)
    {
      printf("time sent successfully to %s...\n", inet_ntoa(cliaddr.sin_addr));
    }
  }
}
