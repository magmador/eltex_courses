#include "../headers/Matrix.h"

void matrix_output(int* matrix, int N)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			printf("%d ", *(matrix + i*N + j));
		}
		printf("\n");
	}
}
