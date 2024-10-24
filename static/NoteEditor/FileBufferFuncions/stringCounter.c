#include "../Headers/noteEditor.h"

int stringCounter(FILE* textFile, char* filename)
{
  char textSymbol;
  int strCount = 0;
  if((textFile=fopen(filename, "r"))==NULL)
  {
    //окно с сообщением о том, что файл не смог открыться. curmode=check_args
    exit(1);
  }
  else
  {
    do{
      textSymbol = fgetc(textFile);
      if(textSymbol=='\n') strCount++;
    }while(textSymbol!=EOF);
    fclose(textFile);
    return strCount;
  }
}
