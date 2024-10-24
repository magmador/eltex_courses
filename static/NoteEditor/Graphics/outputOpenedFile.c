#include "../Headers/noteEditor.h"

char** outputOpenedFile(int strCount, char** textBuffer, size_t strSize, WINDOW* wnd, FILE* textFile)
{
  textBuffer = (char**)realloc(textBuffer,(strCount)*(sizeof(*textBuffer)+1));
  for(int i = 0; i<strCount; i++)
  {
    textBuffer[i]=(char*)malloc(strSize*sizeof(char));
    getline(&textBuffer[i], &strSize, textFile);
    mvwprintw(wnd,i+3,5,"%s", textBuffer[i]);
    wattron(wnd, A_BOLD);
    mvwprintw(wnd,i+3,0,"%-3d|", i+1);
    wattroff(wnd, A_BOLD);
    wrefresh(wnd);
  }
  return textBuffer;
}
