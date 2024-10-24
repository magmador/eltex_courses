#include "fileManager.h"

int main( int argc, char **argv )
{
    setlocale( LC_ALL, "Russian" );
    if( argc <= 1 )
    {
      argv[1] = "/";
    }
    char *dirPath = ( char * )malloc(PATH_MAX*sizeof( char * ) );
    strcpy( dirPath, argv[1] );
    char *dirPathSec = ( char * )malloc(PATH_MAX*sizeof( char * ) );
    strcpy( dirPathSec, argv[1] );

    initscr();
    cbreak();
    curs_set( FALSE );
    keypad( stdscr, TRUE );
    noecho();
    WINDOW *wnd = newwin( LINES, COLS/2, 0, 0 );
    WINDOW *secWnd = newwin( LINES, COLS/2, 0, COLS/2 );
    WINDOW *actualWnd = wnd;
    keypad( wnd, TRUE );
    keypad( secWnd, TRUE );

    unsigned count = 0;
    unsigned countSec = 0;
    char **textBuffer = ( char ** )malloc( 1*sizeof( char * ) ); //буфер пока в одну строку
    textBuffer = process_directory( dirPath, textBuffer, &count );
    char *pathFull = ( char * )malloc( 50*sizeof( char ) );
    char **textBufferSec = ( char ** )malloc( 1*sizeof( char * ) ); //буфер пока в одну строку
    textBufferSec = process_directory( dirPathSec, textBufferSec, &countSec );
    char *pathFullSec = ( char * )malloc( 50*sizeof( char ) );

    change_option_wnd( wnd, textBuffer[0], dirPath, pathFull );
    change_option_wnd( secWnd, textBufferSec[0], dirPathSec, pathFullSec );
    output_dir( wnd, textBuffer, count );
    output_dir( secWnd, textBufferSec, countSec );

    int command = '\0';
    int y = Y_OFFSET;
    int ySec = Y_OFFSET;
    char* fileName;
    char* fileNameSec;
    mvwprintw( wnd, y, X, ">" );

    do
    {
      switch ( command )
      {
        case '\t':
        {
          if( actualWnd == wnd )
          {
            actualWnd = actualWnd_change( actualWnd, secWnd, &ySec, &y );
          }
          else if( actualWnd == secWnd )
          {
            actualWnd = actualWnd_change( actualWnd, wnd, &y, &ySec );
          }
          break;
        }
        case KEY_DOWN:
        {
          if( actualWnd == wnd )
          {
            if( (y - Y_OFFSET) < (count - 1) )
            {
              KEY_DOWN_change( actualWnd, &y, textBuffer, dirPath, pathFull, count );
            }
          }
          else if( actualWnd == secWnd )
          {
            if( (ySec - Y_OFFSET) < (countSec - 1) )
            {
              KEY_DOWN_change( actualWnd, &ySec, textBufferSec, dirPathSec, pathFullSec, countSec );
            }
          }
          break;
        }
        case KEY_UP:
        {
          if( actualWnd == wnd )
          {
            if( y > Y_OFFSET )
            {
              KEY_UP_change( actualWnd, &y, textBuffer, dirPath, pathFull, count );
            }
          }
          else if( actualWnd == secWnd )
          {
            if( ySec > Y_OFFSET )
            {
              KEY_UP_change( actualWnd, &ySec, textBufferSec, dirPathSec, pathFullSec, countSec );
            }
          }
          break;
        }
        case '\n':
        {
          if( actualWnd == wnd )
          {
            textBuffer = direcory_change( actualWnd, fileName, textBuffer, &count, dirPath, pathFull, &y, secWnd );
          }
          else if( actualWnd == secWnd )
          {
            textBufferSec = direcory_change( actualWnd, fileNameSec, textBufferSec, &countSec, dirPathSec, pathFullSec, &ySec, wnd );
          }
          break;
        }
        default:
        {
          break;
        }
      }
      wrefresh( actualWnd );
      wrefresh( secWnd );
    } while( (command = wgetch( actualWnd ) ) != 'q');

    delwin( wnd );
    delwin( secWnd );
    endwin();
    exit(EXIT_SUCCESS);
}
