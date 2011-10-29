#include <stdio.h>
//#include <assert.h>

#include "matrix.h"


void matrix_add(matrix_t *l, matrix *r, matrix_t *out)
{
    printf("%s not implemented\n", __func__);
}

void matrix_sub(matrix_t *l, matrix *r, matrix_t *out)
{
    printf("%s not implemented\n", __func__);
}

void matrix_mul(matrix_t *l, matrix_t *r, matrix_t *out)
{
    int i = 0;
    int j = 0;
    int k = 0;
    
    if (l->cols != r->rows)
        return;// assert()

    for (i = 0; i < l->rows; i++)
        for (j = 0; j < r->cols; j++)
            for (k = 0; k < l->cols; k++)
                out[i][j] = l->data[i][k] * r->data[k][j];
        
}

void matrix_mul_at(matrix_t *l, matrix_t *r, int row, int col)
{
    printf("%s not implemented\n", __func__);
}

void matrix_div(matrix_t *l, matrix *r, matrix_t *out)
{
    printf("%s not implemented\n", __func__);
}

void matrix_print(struct matrix_t *matrix)
{
    int i;
    int j;
    
    for (i = 0; i < matrix->rows; i++) {
        for (j = 0; j < matrix->cols; j++)
            printf("%4d", matrix->data[i][j]);
        putchar('\n');
    }
    putchar('\n');
}
