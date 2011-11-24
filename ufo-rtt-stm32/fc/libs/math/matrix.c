/**
 * @file matrix.c
 * @brief matrix implementation
 */
#include <stdio.h>
#include <assert.h>

#include "matrix.h"

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup math
 * @{
 */

void matrix_add(matrix_t *l, matrix_t *r, matrix_t *out)
{
    int i, j;
    
    assert(l->rows == r->rows);
    assert(l->cols == r->cols);
    
    for (i = 0; i < l->rows; i++)
        for (j = 0; j < r->cols; j++)
            *((int *)out->data + out->cols * i + j) =
            *((int *)l->data + l->cols * i + j) + *((int *)r->data + r->cols * i + j);
}

void matrix_sub(matrix_t *l, matrix_t *r, matrix_t *out)
{
    int i, j;
    
    assert(l->rows == r->rows);
    assert(l->cols == r->cols);
    
    for (i = 0; i < l->rows; i++)
        for (j = 0; j < r->cols; j++)
            *((int *)out->data + out->cols * i + j) =
            *((int *)l->data + l->cols * i + j) - *((int *)r->data + r->cols * i + j);
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

void matrix_scalar(matrix_t *matrix, int c)
{
    int i, j;
    int rows = matrix->rows;
    int cols = matrix->cols;
    int *data = matrix->data;
    
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            *(data + cols * i + j) = *(data + cols * i + j) * c;
}

void matrix_mul_at(matrix_t *l, matrix_t *r, int row, int col)
{
    printf("%s not implemented\n", __func__);
}

void matrix_div(matrix_t *l, matrix_t *r, matrix_t *out)
{
    printf("%s not implemented\n", __func__);
}

void matrix_transpose(matrix_t *input, matrix_t *o)
{
    int i, j;
    
    assert(o->rows == input->cols);
    assert(o->cols == input->rows);
    
    for (i = 0; i < input->cols; i++)
        for (j = 0; j < input->rows; j++)
            *((int *)o->data + o->cols * i + j) = *((int *)input->data + input->cols * j + i);
}

int matrix_det(matrix_t *matrix)
{
    int i;
    int det;
    int rows = matrix->rows;
    int cols = matrix->cols;
    int *data = matrix->data;
    
    //if ()
    return ((*(data + cols * 0 + 0)) * (*(data + cols * 1 + 1)) * (*(data + cols * 2 + 2)) + 
            (*(data + cols * 0 + 1)) * (*(data + cols * 1 + 2)) * (*(data + cols * 2 + 0)) + 
            (*(data + cols * 0 + 2)) * (*(data + cols * 1 + 0)) * (*(data + cols * 2 + 1))) -
           ((*(data + cols * 0 + 2)) * (*(data + cols * 1 + 1)) * (*(data + cols * 2 + 0)) + 
            (*(data + cols * 0 + 1)) * (*(data + cols * 1 + 0)) * (*(data + cols * 3 + 3)) + 
            (*(data + cols * 0 + 0)) * (*(data + cols * 1 + 2)) * (*(data + cols * 2 + 1)));
            
            
}

int matrix_inverse(matrix_t *in, matrix_t *out)
{
    int retval = 0;
    int det;
    int rows = in->rows;
    int cols = in->cols;
    int *data = in->data;

    /* matrix of cofactors */
    int cofactor[8][8];

    /* adjugate matrix */
    int adjoint[8][8];
    
    assert(in->rows == in->cols);
    assert(out->rows == out->cols);
    assert(in->rows == out->rows);

    det = matrix_det(in);
    printf("det:%d\n", det);    
    matrix_scalar(out, (1 / det));

    return retval;
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

/** @} */

/** @} */
