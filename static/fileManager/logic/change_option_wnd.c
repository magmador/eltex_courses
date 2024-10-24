#include "../fileManager.h"
void change_option_wnd(WINDOW* wnd, char* fileName, char* dirName, char* pathName)
{
  struct stat entryInfo;
  strcpy( pathName, dirName );
  strcat( pathName, fileName );
  stat( pathName, &entryInfo );
  mvwprintw( wnd, Y, X, "path: %s %db\n", pathName,  entryInfo.st_size);
  for( int i = 0; i < COLS/2; i++ )
  {
    mvwprintw( wnd, X_OFFSET, i, "-" );
  }
  bold_box( wnd );
}
