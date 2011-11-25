/**
 * @file matrix.c
 * @brief matrix implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

matrix_t *matrix_new(int rows, int cols)
{
    int size = rows * cols;

    matrix_t *new = (matrix_t *)malloc(sizeof(matrix_t));
    void *data = (void *)malloc(size*sizeof(int));

    new->rows = rows;
    new->cols = cols;
    new->data = data;

    memset(data, 0, size * sizeof(int));

    return new;
}

void matrix_delete(matrix_t *matrix)
{
    if (matrix->data)
        free(matrix->data);
    if (matrix);
        free(matrix);
}

int matrix_create(matrix_t *matrix)
{
    int size = matrix->rows * matrix->cols;

    void *data = (void *)malloc(size*sizeof(int));
    if (!data)
        return -1;

    memset(data, 0, size * sizeof(int));
    matrix->data = data;

    return 0;    
}

void matrix_destroy(matrix_t *matrix)
{
    if (matrix->data)
        free(matrix->data);
}

void matrix_copy(matrix_t *dst, matrix_t *src)
{
    int size = src->rows * src->cols * sizeof(int);

    dst->rows = src->rows;
    dst->cols = src->cols;
    memcpy(dst->data, src->data, size);
}

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
/**
 * @internal
 */
static int matrix_minor(matrix_t *m, matrix_t *minor, int row, int col)
{

    int order;
    int i, j;
    int x, y;
    int retval;
    assert(m->rows == m->cols);
    order = m->rows;
    
    if (order <= 1)
        return -1;
    minor->rows = order - 1;
    minor->cols = order - 1;
    retval = matrix_create(minor);
    if (retval)
        return -1;

    x = y = 0;
    for (i = 0; i < order; i++) {
        if (i != row) {
            y = 0;
            for (j = 0; j < order; j++) {
                if (j != col) {
                    *((int *)minor->data + minor->cols * x + y) = *((int *)m->data + order * i + j);
                    y++;
                }    
            }
            x++;
        }
    }    

    return 0;
}

int matrix_det(matrix_t *matrix)
{
    int i;
    int det = 0;
    int order;
    int cols;
    int *data;
    matrix_t minor;
    
    assert(matrix->rows == matrix->cols);
    
    order = matrix->rows;
    cols = matrix->cols;
    data = matrix->data;

    /* The stopping condition */
    if (order == 1)
        return *((int *)data + cols * 0 + 0);

    for (i = 0; i < order; i++) {
    
        if (matrix_minor(matrix, &minor, 0, i)) {
            printf("%s error\n", __func__);
            return -1;
        }
//        printf("%2d %2d\n", pow(-1, i), *((int *)matrix->data + matrix->cols * 0 + i)); 
//        matrix_print(&minor);
        det += (pow(-1, i) * (*(data + cols * 0 + i)) * matrix_det(&minor));
        matrix_destroy(&minor);
    }
    
    return det;
}

int matrix_inverse(matrix_t *in, matrix_t *out)
{
    int retval = 0;
    int det;
    int i, j;
    
    int rows = in->rows;
    int cols = in->cols;
    int *data = in->data;
    
    matrix_t minor;
    
    /* matrix of cofactors */
    matrix_t *cofactor;

    /* adjugate matrix */
    matrix_t *adjoint;
    
    assert(in->rows == in->cols);
    assert(out->rows == out->cols);
    assert(in->rows == out->rows);
    cofactor = matrix_new(rows, cols);
    adjoint = matrix_new(cols, rows);

    det = matrix_det(in);
//    printf("det:%d\n", det);
    if (det == 0)
        return -1;
    /*Forming Cofactor Matrix */
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++) {
            matrix_minor(in, &minor, i, j);
            int p = pow(-1, i + j);
            *((int *)cofactor->data + cofactor->cols * i + j) = matrix_det(&minor) * p;
            matrix_destroy(&minor);
        }
    matrix_print(cofactor);

    matrix_transpose(cofactor, adjoint);
    matrix_print(adjoint);
   
    matrix_scalar(adjoint, (1 / det));

    matrix_copy(out, adjoint);
    matrix_print(out);
    
    matrix_delete(cofactor);
    matrix_delete(adjoint);

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
