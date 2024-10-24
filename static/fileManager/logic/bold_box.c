#include "../fileManager.h"
void bold_box( WINDOW* wnd )
{
  wattron( wnd, A_BOLD );
  box( wnd, 0, 0 );
  wattroff( wnd, A_BOLD );
  wrefresh( wnd );
}
