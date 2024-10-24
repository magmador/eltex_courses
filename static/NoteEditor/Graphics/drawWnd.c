#include "../Headers/noteEditor.h"

void drawWnd(WINDOW* wnd, int strCount, char** textBuffer)
{
  werase(wnd);
  for(int i = 0; i<strCount; i++)
  {
    wattron(wnd, A_BOLD);
    mvwprintw(wnd,i+3,0,"%-3d|", i+1);
    wattroff(wnd, A_BOLD);
    mvwprintw(wnd,i+3,5,"%s", textBuffer[i]);
  }
}
