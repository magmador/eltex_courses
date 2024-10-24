#include "../Headers/noteEditor.h"

void keyDownTreat(int* y, int* x, int strCount)
{
  if(*y<=strCount+1)
  {
    (*y)++;
    *x=5;
  }
}
