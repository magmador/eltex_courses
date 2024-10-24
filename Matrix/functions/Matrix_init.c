#include "../headers/Matrix.h"

void matrix_init(int *matrix, int N, int mode)
{
	if(mode)
	{
		printf("************matrix***********\n");
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (mode)
				*(matrix + i*N + j) = (i*N + j + 1);
			else
				*(matrix + i*N + j) = 0;
		}
	}
}
