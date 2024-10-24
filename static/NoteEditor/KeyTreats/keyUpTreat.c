#include "../Headers/noteEditor.h"

void keyUpTreat(int* y, int* x, int strCount)
{
  if((*y)>3)
  {
    (*y)--;
    *x=5;
  }
}
