#include "headerlib.h"
#include <stdlib.h>
#include <stdio.h>

char* funcName;

char* funcNameReturn()
{
        funcName = (char*)malloc(10*sizeof(char));
        char* funcName = "mulcompl";
        return funcName;
}

void funcFinish(){
        if(funcName!=NULL) free(funcName);
}

struct complexNumber mulcompl(struct complexNumber first, struct complexNumber second) {
    first.realPart = (first.realPart * second.realPart) - (first.phantomPart * second.phantomPart);
    first.phantomPart = (second.realPart * first.phantomPart) + (first.realPart * second.phantomPart);
    return first;
}

