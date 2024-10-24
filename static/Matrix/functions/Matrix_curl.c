#include "../headers/Matrix.h"

void matrix_curl(int* matrix, int N)
{
	printf("*************curl************\n");
	int j = N/2-1;
	int i = N/2-1;       //центральная координата
	printf("i=%d, j=%d\n", i, j);
	int dir = 0;
	int visited = 1;
	for (int val = N*N; val > 0;)
	{
		if (visited)
		{
			*(matrix + i*N + j) = val;
			--val;
		}
		switch (dir)
		{
		case 0:             //право
			if (*(matrix + i*N + (j + 1)) != 0)
			{
				visited = 0;
				dir = 3;
			}
			else
			{
				visited = 1;
				++j;
				dir = 1;
			}
			break;
		case 1:             //вниз
			if (*(matrix + (i + 1)*N + j) != 0)
			{
				visited = 0;
				dir = 0;
			}
			else
			{
				visited = 1;
				++i;
				dir = 2;
			}
			break;
		case 2:             //лево
			if (*(matrix + i*N + (j - 1)) != 0)
			{
				visited = 0;
				dir = 1;
			}
			else
			{
				visited = 1;
				--j;
				dir = 3;
			}
			break;
		case 3:             //вверх
			if (*(matrix + (i - 1)*N + j) != 0)
			{
				visited = 0;
				dir = 2;
			}
			else
			{
				visited = 1;
				--i;
				dir = 0;
			}
		}
	}
}
