#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    int n;

    char sendBuff[1024];
    char recvBuff[1024];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5005);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 2);

    while(1) {
      snprintf(sendBuff, sizeof(sendBuff), "Hello\n");
      connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
      printf("sending Hello to client...\n");
      if(send(connfd, sendBuff, strlen(sendBuff), 0) != -1)
      {
        printf("sent successfully...\n");
      }
      if ( (n = recv(listenfd, recvBuff, sizeof(recvBuff)-1, 0)) != -1)
      {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
      }
      if(strcmp(recvBuff, "hi"))
      {
        printf("hi got successfully\n");
      }

      close(connfd);
      sleep(1);
    }
}
