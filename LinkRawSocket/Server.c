#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define DATAGRAM_LEN 256
#define RAW_PORT 5555

int main()
{
  int sock;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  struct in_addr addr;
  char buff[DATAGRAM_LEN];
  int bytes_read;
  int client_addr_len = sizeof(struct sockaddr_in);
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sock < 0)
  {
    perror("socket");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(RAW_PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("bind");
    exit(2);
  }

  if((bytes_read = recvfrom(sock, buff, DATAGRAM_LEN, 0, (struct sockaddr *)&client_addr, &client_addr_len)) == -1)
  {
    perror("recvfrom");
    exit(3);
  }
  else if (bytes_read == 0)
  {
    printf("Got zero bytes!\n");
  }
  /*else
  {
    printf("Message received: %s", buff);
    buff[2] = 'a';
    if (sendto(sock, buff, bytes_read, 0, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        perror("sendto");
        exit(3);
    }
    printf("Sent message: %s", buff);
  }*/

  bzero(buff, sizeof(buff));
  bzero(&client_addr, sizeof(client_addr));
  client_addr_len = sizeof(struct sockaddr_in);
  close(sock);
  return 0;
}
