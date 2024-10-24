#include "../fileManager.h"
char** direcory_change( WINDOW *actualWnd, char *fileName, char **textBuffer, int *count, char *dirPath, char *pathFull, int *y, WINDOW *secWnd)
{
  wclear( actualWnd );
  fileName = textBuffer[*y - Y_OFFSET];
  if( fileName[strlen(fileName)-1] == '/' )
  {
    textBuffer = ( char ** )realloc( textBuffer, 1*sizeof( char* ) );
    *count = 0;
    textBuffer = NULL;
    *y = Y_OFFSET;
    textBuffer = process_directory( pathFull, textBuffer, count );
    output_dir( actualWnd, textBuffer, *count);
    mvwprintw( actualWnd, *y, X, ">" );
    dir_normalization( dirPath, fileName );
    change_option_wnd( actualWnd, textBuffer[*y - Y_OFFSET], dirPath, pathFull );
    return textBuffer;
  }
  else
  {
    struct stat entryInfo;
    strcat( dirPath, fileName );
    stat( dirPath, &entryInfo );
    if( entryInfo.st_mode & S_IXUSR )
    {
      if (fork() == 0)
      {
        execl(dirPath, NULL);
      }
      delwin( actualWnd );
      delwin( secWnd );
      endwin();
      wait(0);
      exit(1);
    }

  }
}
