#include "../fileManager.h"
void output_dir( WINDOW* wnd, char** textBuffer, unsigned count )
{
  for ( size_t i = 0; i < count; i++ )
  {
    mvwprintw( wnd, i + Y_OFFSET, X_OFFSET, "|%s\n", textBuffer[i] );
  }
  bold_box( wnd );
}
