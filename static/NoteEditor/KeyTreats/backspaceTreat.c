#include "../Headers/noteEditor.h"

char** backspaceTreat(int* y, int* x, char** textBuffer, int* strCount, size_t strSize, WINDOW* wnd)
{
  if((*x)>5)
  {
    for(int i = 0; i<strlen(textBuffer[(*y)-3]); i++)
    {
      textBuffer[(*y)-3][i-1+(*x)-5]=textBuffer[(*y)-3][i+(*x)-5];
    }
    --(*x);
  }
  else if((*x)==5 && (*y)>3)
  {
    textBuffer[(*y)-4][strlen(textBuffer[(*y)-4])-1]='\0';
    *x = strlen(textBuffer[(*y)-4])+5;
    strcat(textBuffer[(*y)-4], textBuffer[(*y)-3]);
    for(int i=(*y)-2; i<(*strCount);i++)
    {
      textBuffer[i-1]=textBuffer[i];
    }
    textBuffer[(*strCount)--] = NULL;
    if(textBuffer[(*strCount)]==NULL)
    {
      free(textBuffer[(*strCount)]);
    }
    --(*y);
  }
  drawWnd(wnd, *strCount, textBuffer);
  return textBuffer;
}
