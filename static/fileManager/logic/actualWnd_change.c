#include "../fileManager.h"
WINDOW *actualWnd_change( WINDOW *actualWnd, WINDOW *secWnd, int *ySec, int *y )
{
  mvwprintw( actualWnd, *y, X, " " );
  wrefresh( actualWnd) ;
  actualWnd = secWnd;
  *ySec = Y_OFFSET;
  mvwprintw( actualWnd, *ySec, X, ">" );
  return actualWnd;
}
