#include "../headers/Matrix.h"

int main()
{
	int i, j, N;
	N = dimention_read();
	int *matrix = (int*)calloc(N*N, sizeof(int));
	matrix_init(matrix, N, 1); //первичное опеределение матрицы
	matrix_output(matrix, N);

	matrix_snake(matrix, N); //данная функция не переопределяет матрицу, лишь печатает в другом порядке

	matrix_init(matrix, N, 0); //зануление матрицы
	matrix_curl(matrix, N);
	matrix_output(matrix, N);

	matrix_init(matrix, N, 0);
	matrix_triangle_up(matrix, N);
	matrix_output(matrix, N);

	matrix_init(matrix, N, 0);
	matrix_triangle_down(matrix, N);
	matrix_output(matrix, N);

	free(matrix);
	return 0;
}
