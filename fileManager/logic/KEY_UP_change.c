#include "../fileManager.h"
void KEY_UP_change( WINDOW *actualWnd, int *y, char **textBuffer, char *dirPath, char *pathFull, int count )
{
  mvwprintw( actualWnd, *y, X, " " );
  mvwprintw( actualWnd, --(*y), X, ">" );
  change_option_wnd( actualWnd, textBuffer[*y - Y_OFFSET], dirPath, pathFull );
}
