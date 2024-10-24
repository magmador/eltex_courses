#include <stdio.h>
#include "headerlib.h"
int main()
{
    struct complexNumber first; 
    struct complexNumber second;
    readcompl(&first);  
    readcompl(&second); 
    struct complexNumber answer;
    answer = addcompl(first, second);
    printf("answer add: ");
    outcompl(&answer); 
    answer = difcompl(first, second);
    printf("answer dif: ");
    outcompl(&answer);
    answer = mulcompl(first, second);
    printf("answer mul: ");
    outcompl(&answer);
    answer = divcompl(first, second);
    printf("answer div: ");
    outcompl(&answer); 
    return 0;
}
