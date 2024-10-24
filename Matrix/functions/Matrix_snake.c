#include "../headers/Matrix.h"

void matrix_snake(int *matrix, int N)
{
	printf("************snake************\n");
	for (int i = 0; i < N; ++i)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < N; ++j)
			{
				printf("%d ", *(matrix + i*N + j));
			}
		}
		else
		{
			for (int j = N-1; j >= 0; --j)
			{
				printf("%d ", *(matrix + i*N + j));
			}
		}
		printf("\n");
	}
}
