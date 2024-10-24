#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/udp.h>
#include <linux/ip.h>

#define DATAGRAM_LEN 128
#define RAW_PORT 5555
#define UDP_PORT 5556
#define SERVER_ADDR "127.0.0.1"


int main()
{
  int sock;
  struct sockaddr_in server_addr;
  char recv_buff[DATAGRAM_LEN];
  char datagram[DATAGRAM_LEN];

  bzero(datagram, DATAGRAM_LEN);

  struct udphdr *udp_header = (struct udphdr *) datagram; //сразу ставим хедер на начало datagram
  char msg[] = "Hello there!\n";
  memcpy(datagram + sizeof(*udp_header), msg, sizeof(msg)); //копируем сообщение со смещением

  sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
  if (sock < 0)
  {
      perror("socket");
      exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(RAW_PORT); //порт сервера
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  udp_header->source = htons(UDP_PORT); //порт клиента
  udp_header->dest = server_addr.sin_port;
  udp_header->len = htons(sizeof(struct udphdr) + sizeof(msg));
  // ignore checksum

  int bytes_read = 0;
  int server_addr_len = sizeof(server_addr);

  if((bytes_read = sendto(sock, datagram, (sizeof(struct udphdr) + sizeof(msg)), 0, (struct sockaddr *)&server_addr, server_addr_len)) == -1)
  {
    perror("sendto");
    exit(2);
  }
  else if(bytes_read == 0)
  {
    printf("Sendto zero bytes!\n");
  }

  printf("Sent message: %s", datagram + sizeof(*udp_header));
  char str_ip[INET_ADDRSTRLEN];
  bzero(recv_buff, DATAGRAM_LEN);
  for(;;)
  {
    if((bytes_read = recvfrom(sock, recv_buff, DATAGRAM_LEN, 0, NULL, NULL)) == -1)
    {
      perror("recvfrom");
      exit(3);
    }
    else if(bytes_read == 0)
    {
      continue;
    }
    struct iphdr *ip_header_recv = (struct iphdr *)recv_buff;
    struct udphdr *udp_header_recv = (struct udphdr *)(recv_buff + sizeof(struct iphdr));

    inet_ntop(AF_INET, &ip_header_recv->saddr, str_ip, INET_ADDRSTRLEN);

    if ((strcmp(str_ip, SERVER_ADDR) == 0) && (ntohs(udp_header_recv->dest) == UDP_PORT))
    {
        printf("Message received: %s", (char *)(recv_buff + sizeof(struct iphdr) + sizeof(struct udphdr))); //+28
        break;
    }
    memset(recv_buff, 0, DATAGRAM_LEN);
  }
  return 0;
}
