#include "../fileManager.h"
char** process_directory( char *theDir, char** textBuffer, unsigned* count )
{
  DIR *dir = NULL;
  struct dirent* entry = NULL;
  char pathName[PATH_MAX + 1];

  dir = opendir( theDir );
  if( dir == NULL ) {
      printf( "Error opening %s: %s", theDir, strerror( errno ) );
      return 0;
  }

  while( (entry = readdir( dir )) != NULL )
  {
    struct stat entryInfo;
    if( ( strncmp( entry->d_name, ".", PATH_MAX ) == 0 ) ||
      (( strncmp( entry->d_name, "..", PATH_MAX ) == 0 ) && theDir == "/" ) ||
      ( entry->d_name[0] == '.' && ( strncmp( entry->d_name, "..", PATH_MAX ) != 0) ) )
    {
      /* пропускаем ., скрытые файлы и .. в корне */
      continue;
    }
    (void)strncpy( pathName, theDir, PATH_MAX );
    (void)strncat( pathName, "/", PATH_MAX );
    (void)strncat( pathName, entry->d_name, PATH_MAX );
    if( stat( pathName, &entryInfo ) == 0 )
    {
      (*count)++;
      textBuffer = ( char ** )realloc( textBuffer,( (*count) )*( sizeof(*textBuffer) + 1 ) );
      textBuffer[(*count) - 1] = ( char * )malloc( PATH_MAX*sizeof(char) );

      // вызов stat() был успешным, так что продолжаем.
      if( S_ISDIR( entryInfo.st_mode ) )
      {
        // каталог
        (void)strncat( entry->d_name, "/", PATH_MAX );
        textBuffer[*count - 1] = entry->d_name;
      }
      else if( S_ISREG( entryInfo.st_mode ) )
      {
        //обычный файл
        textBuffer[*count - 1] = entry->d_name;
      }
    }
  }
  return textBuffer;
}
