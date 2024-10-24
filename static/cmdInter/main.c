#include <sys/wait.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define CMD_SIZE 50

int main(int argc, char** argv) {
  char cmd[CMD_SIZE];
  FILE* f;
  char c;
  while(1)
  {
    printf("> ");
    fgets(cmd, CMD_SIZE, stdin);

    if (!strncmp(cmd, "quit", 4))
    {
      break;
    }

    f = popen(cmd, "r");

    if (f == NULL)
    {
      perror("popen");
      return 1;
    }

    while((c = fgetc(f)) != EOF )
    {
      printf("%c", c );
    }
    pclose(f);
  }

  return 0;
}
