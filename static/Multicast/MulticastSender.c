#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define MULTI_ADDR "224.0.0.1"
#define MULTI_PORT 5555
#define MAX_EVENTS 1

int main(void)
{
  int udpfd;

  udpfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in cliaddrUdp;
  bzero(&cliaddrUdp, sizeof(cliaddrUdp));

  int clilenUdp;
  cliaddrUdp.sin_family = AF_INET;
  cliaddrUdp.sin_addr.s_addr = inet_addr(MULTI_ADDR);
  cliaddrUdp.sin_port = htons(MULTI_PORT);

  for(;;)
  {
    clilenUdp = sizeof(cliaddrUdp);
    if(sendto(udpfd, "MULTI_HELLO", sizeof("MULTI_HELLO"), 0, (struct sockaddr *) &cliaddrUdp, clilenUdp) == -1)
    {
    perror("sendto\n");
    exit(EXIT_FAILURE);
    }
    sleep(5);
  }
  close(udpfd);
  return 0;
}
