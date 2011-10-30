#include <stdio.h>

#include "matrix.h"
/*
int func(int **array, int m, int n)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
	printf("%d\n", *((int*)array + n*i + j));
}*/
int main(void)
{
	int A[2][3] = {
		{1, 3, 4}, {2,0,1}
	};
	int B[3][4] = {
		{1, 2, 3, 1},
		{2, 2, 2, 2},
		{3, 2, 1, 4}
	};
    int C[2][4] = { 
		{0,0,0,0},{0,0,0,0} };
	//printf("row: %d, col: %d\n", rowsof(A), colsof(A));

	struct matrix_t ma = matrix_get(A);//{ rowsof(A), colsof(A), (int **)A };//
	struct matrix_t mb = matrix_get(B);//{ 3, 4, B };
	struct matrix_t mc = matrix_get(C);//{ 2, 4, C };
	matrix_print(&ma);matrix_print(&mb);
	matrix_mul(&ma, &mb, &mc);
	matrix_print(&mc);
	matrix_add(&ma, &mb, &mc);
	//printf("%d\n", ma.data[0][0]);
//func((int **)B, 3, 4);
   return 0;
}
