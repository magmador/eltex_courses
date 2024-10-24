#include "headerlib.h"

struct complexNumber mulcompl(struct complexNumber first, struct complexNumber second) {
    first.realPart = (first.realPart * second.realPart) - (first.phantomPart * second.phantomPart);
    first.phantomPart = (second.realPart * first.phantomPart) + (first.realPart * second.phantomPart);
    return first;
}

