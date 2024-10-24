#include "../fileManager.h"
void dir_normalization( char* dirName, char* fileName )
{
  if((strcmp( fileName, "../" ) == 0 ))
  {
    int i = strlen( dirName ) - 2; //-2 чтобы пропустить /

    while( dirName[i]!='/' )
    {
      --i;
    }

    str_cut( dirName, i + 1, strlen( dirName ) );
  }
  else
  {
    strcat( dirName, fileName );
  }
}
