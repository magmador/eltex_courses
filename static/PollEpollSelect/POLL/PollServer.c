#include "PollHeader.h"

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, udpfd = 0;
    struct sockaddr_in servAddrTcp, cliaddrTcp, cliaddrUdp, servAddrUdp;
    char recvBuff[MSG_MAX_LEN];

    struct pollfd poll_set[MAX_NUMBER_OF_CLIENTS];
    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
    {
       poll_set[i].fd = -1;
       poll_set[i].events = POLLIN;
       poll_set[i].revents = 0;
    }

    /*TCP socket*/
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servAddrTcp, sizeof(servAddrTcp));
    bzero(&cliaddrTcp, sizeof(cliaddrTcp));

    servAddrTcp.sin_family = AF_INET;
    servAddrTcp.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddrTcp.sin_port = htons(SOCK_PORT_TCP);

    if(bind(listenfd, (struct sockaddr*)&servAddrTcp, sizeof(servAddrTcp)) < 0)
    {
      perror("tcp bind\n");
      exit(EXIT_FAILURE);
    }
    listen(listenfd, 10);

    poll_set[0].fd = listenfd;

    /*UDP socket*/
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servAddrUdp, sizeof(servAddrUdp));
    bzero(&cliaddrUdp, sizeof(cliaddrUdp));

    servAddrUdp.sin_family = AF_INET;
    servAddrUdp.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddrUdp.sin_port = htons(SOCK_PORT_UDP);
    if(bind(udpfd, (struct sockaddr*)&servAddrUdp, sizeof(servAddrUdp)) < 0)
    {
      perror("udp bind\n");
      exit(EXIT_FAILURE);
    }

    poll_set[1].fd = udpfd;

    int clilenTcp, clilenUdp, nready;
    for(;;)
    {
      nready = poll(&poll_set, MAX_NUMBER_OF_CLIENTS, 2000); //на чтение, кол-во готовых сокетов, проверяем в теч.  2 секунд

      if(poll_set[0].revents & POLLIN)
      {
        clilenTcp = sizeof(cliaddrTcp);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddrTcp, &clilenTcp);
        if(connfd == -1)
        {
          perror("accept\n");
          exit(EXIT_FAILURE);
        }
        time_echo(connfd);
        }
      else if(poll_set[1].revents & POLLIN)
      {
        clilenUdp = sizeof(cliaddrUdp);
        if(recvfrom(udpfd, recvBuff, MSG_MAX_LEN, 0, (struct sockaddr *) &cliaddrUdp, &clilenUdp) != -1)
        {
          printf("server got '%s' \n", recvBuff);
        }
        else
        {
          perror("recvfrom\n");
          exit(EXIT_FAILURE);
        }
      }
    }
    close(connfd);
    return 0;
}
