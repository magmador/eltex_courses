#include "PreCreatedHead.h"

void sig_int(int signo)
{
  for(int i = 0; i < nchildren; i++)
  {
    kill(childpid[i], SIGTERM);
  }
  while(wait(NULL) > 0);
  if(errno != ECHILD)
  {
    printf("wait error\n");
  }
  exit(0);
}
