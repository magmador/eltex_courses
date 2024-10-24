#include "headerlib.h"

struct complexNumber difcompl(struct complexNumber first, struct complexNumber second) {
    first.realPart = first.realPart - second.realPart;
    first.phantomPart = first.phantomPart - second.phantomPart;
    return first;
}

