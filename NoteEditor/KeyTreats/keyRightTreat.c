#include "../Headers/noteEditor.h"

void keyRightTreat(int* x, int* y, int strCount, char** textBuffer)
{
  if(*x<=(strlen(textBuffer[(*y)-3])+3))
  {
    (*x)++;
  }
}
