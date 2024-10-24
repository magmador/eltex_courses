#include "../headers/Matrix.h"

int dimention_read()
{
	int N;
	do
	{
		printf("enter odd matrix dimension: ");
		scanf("%d", &N);
	} while(N % 2);
	return N;
}
