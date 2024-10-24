#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define MULTI_ADDR "224.0.0.1"
#define MULTI_PORT 5555
#define MAX_MSG 1024

int main()
{
  int sock;
  struct sockaddr_in addr;
  char recvBuff[MAX_MSG];

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock < 0)
  {
      perror("socket");
      exit(1);
  }

  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(MULTI_PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
      perror("bind error");
      exit(1);
  }
  struct ip_mreq mr; //добавляем мультикаст мембера
  mr.imr_multiaddr.s_addr = inet_addr(MULTI_ADDR);
  mr.imr_interface.s_addr = INADDR_ANY;
  setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mr, sizeof(mr));

  int addrlen;
  addrlen = sizeof(addr);
  if(recvfrom(sock, recvBuff, MAX_MSG, 0, (struct sockaddr *) &addr, &addrlen) != -1)
  {
      printf("%s\n", recvBuff);
  }
  else
  {
    perror("recv");
    exit(1);
  }
    return 0;
}
