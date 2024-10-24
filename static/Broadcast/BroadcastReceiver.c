#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define BROAD_ADDR "10.0.2.255"
#define EPOLL_QUEUE_LEN 2
#define BROAD_PORT 5555
#define MAX_MSG 1024

int main()
{
  int sock;
  struct sockaddr_in addr;
  char buf[MAX_MSG];
  int bytes_read;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock < 0)
  {
      perror("socket");
      exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(BROAD_PORT);
  addr.sin_addr.s_addr = inet_addr(BROAD_ADDR);

  if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
      perror("bind error");
      exit(1);
  }

  if(bytes_read = recvfrom(sock, buf, MAX_MSG, 0, NULL, NULL) != -1 )
  {
      printf("%s\n", buf);
  }
  else
  {
    perror("recv");
    exit(1);
  }
    return 0;
}
