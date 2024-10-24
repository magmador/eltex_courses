#include "headerlib.h"
#include <stdio.h>
#include <stdlib.h>

char* funcName;

char* funcNameReturn()
{
        funcName = (char*)malloc(10*sizeof(char));
        char* funcName = "Ooutcompl";
        return funcName;
}

void funcFinish(){
        if(funcName!=NULL) free(funcName);
}

void Ooutcompl(struct complexNumber num) {
    printf("%d+i(%d)\n", num.realPart, num.phantomPart);

}

