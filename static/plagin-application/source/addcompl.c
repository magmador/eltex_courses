#include "headerlib.h"
#include <stdlib.h>
#include <stdio.h>

char* funcName;

char* funcNameReturn()
{
	funcName = (char*)malloc(10*sizeof(char));
	char* funcName = "addcompl";
	return funcName;
}

void funcFinish(){
	if(funcName!=NULL) free(funcName);
}

struct complexNumber addcompl(struct complexNumber first, struct complexNumber second)
{
    first.realPart = first.realPart + second.realPart;
    first.phantomPart = first.phantomPart + second.phantomPart;
    return first;
}
