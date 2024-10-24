#include "../Headers/noteEditor.h"

void keyEndTreat(int* x, int* y,char** textBuffer)
{
    *x=strlen(textBuffer[(*y)-3])+4;
}
