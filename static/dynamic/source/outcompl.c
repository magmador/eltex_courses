#include "headerlib.h"
#include <stdio.h>

void outcompl(struct complexNumber* num) {
    printf("%d+i(%d)\n", num->realPart, num->phantomPart);

}

