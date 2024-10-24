#include "SelectHeader.h"

int max2(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, udpfd = 0;
    struct sockaddr_in servAddrTcp, cliaddrTcp, cliaddrUdp, servAddrUdp;
    char recvBuff[MSG_MAX_LEN];

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

    fd_set rset;
    FD_ZERO(&rset);
    int maxfdp1 = max2(listenfd, udpfd) + 1;

    int clilenTcp, clilenUdp, nready;
    for(;;)
    {
      FD_SET(listenfd, &rset);
      FD_SET(udpfd, &rset);
      nready = select(maxfdp1, &rset, NULL, NULL, NULL); //на чтение, кол-во готовых сокетов

      if(FD_ISSET(listenfd, &rset))
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
      else if(FD_ISSET(udpfd, &rset))
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
