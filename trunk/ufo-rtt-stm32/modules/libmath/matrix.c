#include <stdio.h>
#include <assert.h>

#include "matrix.h"


void matrix_add(matrix_t *l, matrix_t *r, matrix_t *out)
{
    int i, j;
    
    assert(l->rows == r->rows);
    assert(l->cols == r->cols);
    
    for (i = 0; i < l->rows; i++)
        for (j = 0; j < r->cols; j++)
            (int *)out->data + out->cols * i + j =
            ((int *)l->data + l->cols * i + j) + ((int *)r->data + r->cols * i + j);
}

void matrix_sub(matrix_t *l, matrix_t *r, matrix_t *out)
{
    int i, j;
    
    assert(l->rows == r->rows);
    assert(l->cols == r->cols);
    
    for (i = 0; i < l->rows; i++)
        for (j = 0; j < r->cols; j++)
            (int *)out->data + out->cols * i + j =
            ((int *)l->data + l->cols * i + j) - ((int *)r->data + r->cols * i + j);
}

void matrix_mul(matrix_t *l, matrix_t *r, matrix_t *out)
{
    int i = 0;
    int j = 0;
    int k = 0;
    
    assert(l->cols == r->rows);

    for (i = 0; i < l->rows; i++)
        for (j = 0; j < r->cols; j++)
            for (k = 0; k < l->cols; k++)
                *((int *)out->data + out->cols * i + j) += *((int *)l->data + l->cols * i + k) * (*((int *)r->data + r->cols * k + j));
        
}

void matrix_mul_at(matrix_t *l, matrix_t *r, int row, int col)
{
    printf("%s not implemented\n", __func__);
}

void matrix_div(matrix_t *l, matrix_t *r, matrix_t *out)
{
    printf("%s not implemented\n", __func__);
}

void matrix_print(struct matrix_t *matrix)
{
    int i;
    int j;
    
    for (i = 0; i < matrix->rows; i++) {
        for (j = 0; j < matrix->cols; j++)
            printf("%4d", *((int *)matrix->data + matrix->cols * i + j));
        putchar('\n');
    }
    putchar('\n');
}
