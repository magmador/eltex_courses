#include "headerlib.h"
#include <stdio.h>
#include <stdlib.h>

char* funcName;

char* funcNameReturn()
{
        funcName = (char*)malloc(10*sizeof(char));
        char* funcName = "divcompl";
        return funcName;
}

void funcFinish(){
        if(funcName!=NULL) free(funcName);
}

struct complexNumber divcompl(struct complexNumber first, struct complexNumber second) {
    first.realPart = ((first.realPart * second.realPart) + (first.phantomPart * second.phantomPart))/((second.realPart * second.realPart) + (second.phantomPart*second.phantomPart));
    first.phantomPart = ((second.realPart * first.phantomPart) - (first.realPart * second.phantomPart))/((second.realPart * second.realPart) + (second.phantomPart*second.phantomPart));
    return first;
}

