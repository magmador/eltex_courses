#include "../Headers/noteEditor.h"

char** deleteTreat(int* y, int* x, char** textBuffer, int* strCount, size_t strSize, WINDOW* wnd)
{
  if((*x)>=5 && strlen(textBuffer[(*y)-3]) >= (*x)-3)
  {
    for(int i = 0; i<strlen(textBuffer[(*y)-3]); i++)
    {
      textBuffer[(*y)-3][i+(*x)-5]=textBuffer[(*y)-3][i+1+(*x)-5];
    }
  }
  else if((*x)>=5 && strlen(textBuffer[(*y)-3]) < (*x)-3 && (*strCount)>1 && ((*y)-3)<((*strCount)-1))
  {

    textBuffer[(*y)-3][strlen(textBuffer[(*y)-3])-1]='\0';
    strcat(textBuffer[(*y)-3], textBuffer[(*y)-2]);
    for(int i=(*y)-2; i<(*strCount);i++)
    {
      textBuffer[i]=textBuffer[i+1];
    }
    textBuffer[(*strCount)--] = NULL;
    if(textBuffer[(*strCount)]==NULL)
    {
      free(textBuffer[(*strCount)]);
    }
  }
  drawWnd(wnd, *strCount, textBuffer);
  return textBuffer;
}
