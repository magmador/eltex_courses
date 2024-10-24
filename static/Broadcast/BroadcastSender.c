#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BROAD_ADDR "10.0.2.255"
#define EPOLL_QUEUE_LEN 2
#define BROAD_PORT 5555
#define MAX_EVENTS 1

int main(void)
{
    int udpfd;
    char buf[1024];
    int bytes_read;

    udpfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in cliaddrUdp;
    bzero(&cliaddrUdp, sizeof(cliaddrUdp));

    struct epoll_event ev, events[MAX_EVENTS];
    int epollfd = epoll_create(EPOLL_QUEUE_LEN);
    if (epollfd == -1)
    {
      perror("epoll_create1\n");
      exit(EXIT_FAILURE);
    }
    ev.events = EPOLLOUT | EPOLLET; //сервер только будет отправлять
    ev.data.fd = udpfd;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, udpfd, &ev) == -1) //добавили сокет в epoll
    {
      perror("epoll_ctl: listenfd\n");
      exit(EXIT_FAILURE);
    }

    int clilenUdp, eventsNum;
    int trueBroad = 1;
    setsockopt(udpfd, SOL_SOCKET, SO_BROADCAST, &trueBroad, sizeof(trueBroad));

    cliaddrUdp.sin_family = AF_INET;
    cliaddrUdp.sin_addr.s_addr = inet_addr(BROAD_ADDR);
    cliaddrUdp.sin_port = htons(BROAD_PORT);

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
        if(events[n].data.fd == udpfd)
        {
          int flags=fcntl(udpfd, F_GETFL); //делаем сокет не блокирующим
          fcntl(udpfd, F_SETFL, flags| O_NONBLOCK);
          clilenUdp = sizeof(cliaddrUdp);
          if(sendto(udpfd, "BROAD_HELLO", sizeof("BROAD_HELLO"), 0, (struct sockaddr *) &cliaddrUdp, clilenUdp) == -1)
          {
            perror("sendto\n");
            exit(EXIT_FAILURE);
          }
        }
        sleep(5);
      }
    }

    close(udpfd);
    return 0;
}
