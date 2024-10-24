#include "Epollheader.h"

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

    struct epoll_event ev, events[MAX_EVENTS];
    int epollfd = epoll_create(EPOLL_QUEUE_LEN);
    if (epollfd == -1)
    {
      perror("epoll_create1\n");
      exit(EXIT_FAILURE);
    }
    ev.events = EPOLLIN | EPOLLET; //сервер только будет читать то, что ему отправил клиент
    ev.data.fd = listenfd;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) //добавили слушающий сокет в epoll
    {
      perror("epoll_ctl: listenfd\n");
      exit(EXIT_FAILURE);
    }

    ev.data.fd = udpfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, udpfd, &ev) == -1)
    {
      perror("epoll_ctl: udpfd\n");
      exit(EXIT_FAILURE);
    }

    int clilenTcp, clilenUdp, eventsNum;
    for(;;)
    {
      eventsNum = epoll_wait(epollfd, events, MAX_EVENTS, -1);
      if(eventsNum == -1)
      {
        perror("epoll_wait\n");
        exit(EXIT_FAILURE);
      }

      for(size_t n = 0; n < eventsNum; ++n)
      {
        if(events[n].data.fd == listenfd)
        {
          clilenTcp = sizeof(cliaddrTcp);
          connfd = accept(listenfd, (struct sockaddr *) &cliaddrTcp, &clilenTcp);
          if(connfd == -1)
          {
            perror("accept\n");
            exit(EXIT_FAILURE);
          }
          int flags=fcntl(connfd, F_GETFL); //делаем сокет не блокирующим
          fcntl(connfd, F_SETFL, flags| O_NONBLOCK);
          time_echo(connfd);
        }
        else if(events[n].data.fd == udpfd)
        {
          int flags=fcntl(udpfd, F_GETFL); //делаем сокет не блокирующим
          fcntl(udpfd, F_SETFL, flags| O_NONBLOCK);
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

    }
    close(connfd);
    return 0;
}
