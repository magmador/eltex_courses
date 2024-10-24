#include "../headers/Matrix.h"

void matrix_triangle_up(int* matrix, int N)
{
	printf("*********triangle_up*******\n");
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			*(matrix + j*N + i) = 1;
		}
	}
}
