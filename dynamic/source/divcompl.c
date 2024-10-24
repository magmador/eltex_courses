#include "headerlib.h"

struct complexNumber divcompl(struct complexNumber first, struct complexNumber second) {
    first.realPart = ((first.realPart * second.realPart) + (first.phantomPart * second.phantomPart))/((second.realPart * second.realPart) + (second.phantomPart*second.phantomPart));
    first.phantomPart = ((second.realPart * first.phantomPart) - (first.realPart * second.phantomPart))/((second.realPart * second.realPart) + (second.phantomPart*second.phantomPart));
    return first;
}

