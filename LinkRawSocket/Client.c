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
#include <linux/if_packet.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <net/if.h>

#define DATAGRAM_LEN 256
#define SERVER_PORT 5555
#define CLIENT_PORT 5556
#define SERVER_ADDR "192.168.0.10"
#define CLIENT_ADDR "192.168.0.8"
#define DEVICE_NAME "eth0"

unsigned short csum(unsigned short *iph);

int main()
{
  struct sockaddr_ll server_addr, client_addr;
  char recv_buff[DATAGRAM_LEN];
  char datagram[DATAGRAM_LEN];
  bzero(datagram, DATAGRAM_LEN);

  struct ether_header *eth_header = (struct ether_header *) datagram; //ethernet header ставим на начало datagram
  struct iphdr *ip_header = (struct iphdr *) (datagram + sizeof(struct ether_header)); //сразу за ним ip header
  struct udphdr *udp_header = (struct udphdr *) (datagram + sizeof(struct ether_header) + sizeof(struct iphdr)); //за ip идёт udp header
  //заполняем заголовки нулями
  bzero(eth_header, sizeof(struct ether_header));
  bzero(ip_header, sizeof(struct iphdr));
  bzero(udp_header, sizeof(struct udphdr));

  char msg[] = "Hello there!";
  memcpy(datagram + sizeof(*eth_header) + sizeof(*ip_header) + sizeof(*udp_header), msg, sizeof(msg)); //копируем сообщение со смещением

  //создаем сокет
  int sock;
  if ((sock=socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)))<0)
  {
      perror("socket");
      exit(1);
  }

  unsigned char mac_source[6] = {0x08, 0x00, 0x27, 0x35, 0x68, 0x18}; //мак клиента
  unsigned char mac_dest[6]   = {0x08, 0x00, 0x27, 0xad, 0x73, 0x97}; //мак сервера

	server_addr.sll_family = AF_PACKET;
	server_addr.sll_protocol = htons(ETH_P_ALL);
	server_addr.sll_ifindex = if_nametoindex(DEVICE_NAME);
	server_addr.sll_halen = ETH_ALEN;
	memmove((void *) (server_addr.sll_addr), (void *) mac_dest, ETH_ALEN);

  for(int i = 0; i < 6; i++)
    eth_header->ether_shost[i] = mac_source[i];

  for(int i = 0; i < 6; i++)
    eth_header->ether_dhost[i] = mac_dest[i];

  eth_header->ether_type = htons(ETHERTYPE_IP);

  ip_header->version  = 4;
  ip_header->ihl      = 5; //умноженное на 4 - размер (20)
  ip_header->tot_len  = htons((ip_header->ihl * 4) + sizeof(struct udphdr) + strlen(msg) + 1);
  ip_header->tos      = 0; //routine
  ip_header->ttl      = 64; // hops
  ip_header->frag_off = 0;
  ip_header->id       = htons(11111);
  ip_header->protocol =  IPPROTO_UDP; // UDP
  ip_header->daddr    = inet_addr(SERVER_ADDR);
  ip_header->saddr    = inet_addr(CLIENT_ADDR);
  ip_header->check    = csum((unsigned short *) ip_header); //htons(0xcdfa);

  udp_header->source  = htons(CLIENT_PORT); //порт клиента
  udp_header->dest    = htons(SERVER_PORT);
  udp_header->len     = htons(sizeof(struct udphdr) + sizeof(msg));
  // ignore checksum

  int bytes_read = 0;
  socklen_t server_addr_len = sizeof(server_addr);

  if((bytes_read = sendto(sock, datagram, (sizeof(*eth_header) + sizeof(*ip_header) + sizeof(*udp_header) + sizeof(msg)), 0, (struct sockaddr *)&server_addr, server_addr_len)) == -1)
  {
    perror("sendto()");
    exit(2);
  }
  else if(bytes_read == 0)
  {
    printf("Sendto zero bytes!\n");
    exit(3);
  }
  printf("Sent message: '%s'\n", datagram + sizeof(*eth_header) + sizeof(*ip_header) + sizeof(*udp_header));

  char str_ip[INET_ADDRSTRLEN];
  bzero(recv_buff, DATAGRAM_LEN);
  for(;;)
  {
    if((bytes_read = recvfrom(sock, recv_buff, DATAGRAM_LEN, 0, NULL, NULL)) == -1)
    {
      perror("recvfrom()");
      exit(3);
    }
    else if(bytes_read == 0)
    {
      continue;
    }
    struct ether_header *eth_header = (struct ether_header *)recv_buff;
    struct iphdr *ip_header_recv = (struct iphdr *)(recv_buff + sizeof(struct ether_header));
    struct udphdr *udp_header_recv = (struct udphdr *)(recv_buff + sizeof(struct ether_header) + sizeof(struct iphdr));

    inet_ntop(AF_INET, &ip_header_recv->saddr, str_ip, INET_ADDRSTRLEN);

    if ((strcmp(str_ip, SERVER_ADDR) == 0) && (ntohs(udp_header_recv->dest) == CLIENT_PORT))
    {
        printf("Message received: '%s' \n", (char *)(recv_buff + sizeof (struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr)));
        break;
    }
    memset(recv_buff, 0, DATAGRAM_LEN);
  }
  return 0;
}

unsigned short csum(unsigned short *iph)
{
  int sum = 0;
  unsigned short *tmp = iph;

  for(int i = 0; i< 10; i++)
  {
    sum += *tmp++;
  }
  int tmp_sum = sum >> 16;
  sum += tmp_sum;
  return ~sum;
}
