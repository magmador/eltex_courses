#include "headerlib.h"
#include <stdio.h>
#include <stdlib.h>

char* funcName;

char* funcNameReturn()
{
        funcName = (char*)malloc(10*sizeof(char));
        char* funcName = "Rreadcompl";
        return funcName;
}

void funcFinish(){
        if(funcName!=NULL) free(funcName);
}

struct complexNumber Rreadcompl()
{
    int result = 0;
    struct complexNumber num;
    printf("enter complex number real part: ");
    scanf("%d", &result);
    num.realPart = result;
    printf("enter complex number plantom part: ");
    scanf("%d", &result);
    num.phantomPart = result;
    return num;
}
