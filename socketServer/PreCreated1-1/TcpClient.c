#include "PreCreatedHead.h"

int main(int argc, char **argv)
{
  if(argc != 3)
  {
    printf("usage: ./TcpClient <IPaddress> <CountOfClients>\n");
  }
  pid_t pid;
  for(size_t i = 0; i < atoi(argv[2]); i++)
  {
    if((pid = fork()) == 0)
    {
      int sockfd;
      struct sockaddr_in servaddr;
      if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
        printf("socket create error\n");
        exit(0);
      }
      bzero(&servaddr, sizeof(servaddr));
      servaddr.sin_family = AF_INET;
      servaddr.sin_port = htons(SERV_PORT);
      if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
      {
        printf("inet_pton error\n");
        exit(0);
      }
      if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
      {
        printf("client connect error\n");
        exit(0);
      }
      time_cli(sockfd);
      exit(0);
    }
  }
  while(wait(NULL)>0);
  if(errno != ECHILD)
  {
    printf("wait error\n");
  }

  exit(0);
}
