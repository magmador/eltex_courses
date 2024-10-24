#include "../headers/Matrix.h"

void matrix_triangle_down(int* matrix, int N)
{
	printf("**********triangle_down********\n");
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			*(matrix + i*N + j) = 1;
		}
	}
}
