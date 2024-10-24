#include "../Headers/noteEditor.h"

char** enterTreat(int* y, int* x, char** textBuffer, int* strCount, size_t strSize, WINDOW* wnd)
{
  char* restOfLine = (char*)malloc(strSize*sizeof(char));
  for(int i=0; i<strlen(textBuffer[(*y)-3]);i++)
  {
    restOfLine[i]=textBuffer[(*y)-3][i+(*x)-5];
  }
  textBuffer[(*y)-3][(*x)-5] = '\n';
  textBuffer[(*y)-3][(*x)-4] = '\0';
  textBuffer = (char**)realloc(textBuffer,((*strCount)++)*(sizeof(*textBuffer)+1));
  textBuffer[(*strCount)-1]=(char*)malloc(strSize*sizeof(char));
  char* temp = (char*)malloc(strSize*sizeof(char));
  temp = textBuffer[(*y)-2]; //значение строки ниже начальной
  for(int i = (*(strCount)-1); i>((*y)-2);i--)
  {
    textBuffer[i]=textBuffer[i-1];
  }
  textBuffer[(*y)-2] = NULL;
  textBuffer[(*y)-2] = restOfLine;
  textBuffer[(*y)-1] = temp;
  drawWnd(wnd, *strCount, textBuffer);
  (*y)++;
  *x=5;
  temp=NULL;
  restOfLine=NULL;
  wrefresh(wnd);
  if(restOfLine==NULL)
  {
    free(restOfLine);
  }
  if(temp==NULL)
  {
    free(temp);
  }
  return textBuffer;
}
