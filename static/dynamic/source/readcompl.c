#include "headerlib.h"
#include <stdio.h>
void readcompl(struct complexNumber* num)
{
    int result = 0;
    printf("enter complex number real part: ");
    scanf("%d", &result);
    num->realPart = result;
    printf("enter complex number plantom part: ");
    scanf("%d", &result);
    num->phantomPart = result;
}
