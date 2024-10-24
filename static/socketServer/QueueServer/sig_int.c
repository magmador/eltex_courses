#include "tcpEH.h"

void sig_int(int signo)
{
  printf("\ninvoked %s\n", __FUNCTION__);
  extern int idQueue;
  msgctl(idQueue, IPC_RMID, NULL);
  close(listenfd);
  exit(0);
}
