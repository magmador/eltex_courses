#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <curses.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <dirent.h>
#include <unistd.h>

#define Y_OFFSET 3
#define X_OFFSET 2
#define Y 1
#define X 1

char** process_directory( char *theDir, char** textBuffer, unsigned* count );
void bold_box( WINDOW* wnd );
void output_dir( WINDOW* wnd, char** textBuffer, unsigned count );
void change_option_wnd(WINDOW* wnd, char* fileName, char* dirName, char* pathName);
int str_cut( char *str, int begin, int len );
void dir_normalization( char* dirName, char* fileName );
WINDOW *actualWnd_change( WINDOW *actualWnd, WINDOW *secWnd, int *ySec, int *y );
void KEY_DOWN_change( WINDOW *actualWnd, int *y, char **textBuffer, char *dirPath, char *pathFull, int count );
void KEY_UP_change( WINDOW *actualWnd, int *y, char **textBuffer, char *dirPath, char *pathFull, int count );
char** direcory_change( WINDOW *actualWnd, char *fileName, char **textBuffer, int *count, char *dirPath, char *pathFull, int *y, WINDOW *secWnd);
