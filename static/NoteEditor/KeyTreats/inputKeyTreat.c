#include "../Headers/noteEditor.h"

char** inputKeyTreat(int* y, int* x, char** textBuffer, int* strCount, size_t strSize, WINDOW* wnd, int inputChar)
{
  if((inputChar >= (int)' ' && inputChar <= (int)'}')) //любой допустимый сивол ввода
  {
    char* restOfLine = (char*)malloc(strSize*sizeof(char));
    for(int i=0; i<strlen(textBuffer[(*y)-3]);i++)
    {
      restOfLine[i]=textBuffer[(*y)-3][i+(*x)-5];
    }
    textBuffer[(*y)-3][(*x)-5] = inputChar;
    for (int i = 0; i < strlen(textBuffer[(*y)-3]); i++)
    {
      textBuffer[(*y)-3][i+(*x)-4]=restOfLine[i];
    }
    drawWnd(wnd, *strCount, textBuffer);
    (*x)++;
  }
  return textBuffer;
}
