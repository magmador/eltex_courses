#include "PreCreatedHead.h"

pid_t child_make(int i, int listenfd, int addrlen)
{
  pid_t pid;
  if(pid = fork() != 0) /*родительский процесс*/
  {
    return pid;
  }
  child_main(i, listenfd, addrlen);
}
