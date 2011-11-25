/**
 * @file matrix.h
 * @brief matrix interface
 */

#ifndef MATRIX_H
#define MATRIX_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup math
 * @{
 */ 

#define rowsof(m)	(sizeof(m) / sizeof(*m))
#define colsof(m)	(sizeof(*m) / sizeof(**m))
#define matrix_get(array)   { rowsof(array), colsof(array), (int *)array }
/**
 * @struct matrix_t matrix.h
 * @brief Describe a matrix
 */
typedef struct matrix_t {
    int rows;       /**< hom many rows of matrix */
    int cols;       /**< how many columns of matrix */
    void *data;     /**< pointer to data */
} matrix_t;

/**
 * Matrix constructor
 *
 * @param rows The number of the matrix rows
 * @param cols The number of the matrix columns
 * @return The pointer to the new matrix
 */
matrix_t *matrix_new(int rows, int cols);

/**
 * Matrix Destructor
 * 
 * @param matrix The matrix to be free
 * @return None
 */
void matrix_delete(matrix_t *matrix);

/**
 * Setup the data field by malloc()
 *
 * @param matrix The pointer to the matrix
 * @return 0 success, negative otherwise
 */
int matrix_create(matrix_t *matrix);

/**
 * Cleanup the data field by free()
 *
 * @param The pointer to the matrix
 * @return None
 */
void matrix_destroy(matrix_t *matrix);

/**
 * Copy the matrix from src to dst
 *
 * @param dst The target matrix copy to
 * @param src The source matrix take from
 * @return None
 */
void matrix_copy(matrix_t *dst, matrix_t *src);

/**
 * Addition of two matrixes
 * out = l + r
 * @param l the left matrix
 * @param r the right matrix
 * @param out the answer matrix
 * @return none
 */
void matrix_add(matrix_t *l, matrix_t *r, matrix_t *out);

/**
 * Subduction of two matrixes
 * out = l - r
 * @param l the left matrix
 * @param r the right matrix
 * @param out the answer matrix
 * @return none
 */
void matrix_sub(matrix_t *l, matrix_t *r, matrix_t *out);

/**
 * multiplies a m x n matrix by a n x m matrix
 * out = l x r
 * @param l the left matrix
 * @param r the right matrix
 * @param out the answer matrix
 * @return none
 * @note you should give correct parameter of matrix, otherwise errror occured
 */
void matrix_mul(matrix_t *l, matrix_t *r, matrix_t *out);

/**
 * Matrix scalar multiplication
 *
 * @param matrix The pointer to the matrix
 * @param c The scalar
 * @return None
 */
void matrix_scalar(matrix_t *matrix, int c);
/**
 * the dot product
 */
void matrix_mul_at(matrix_t *l, matrix_t *r, int row, int col);
void matrix_div(matrix_t *l, matrix_t *r, matrix_t *out);
/**
 * Transpose a matrix
 *
 * @param in The input matrix
 * @param out The output matrix
 * @return None
 */
void matrix_transpose(matrix_t *in, matrix_t *out);

/**
 * Find the determinant of the matrix
 * @param matrix The pointer to the matrix
 * @return The determinant of the matrix
 */
int matrix_det(matrix_t *matrix);

/**
 * Inverse of a square matrix
 *
 * @param in The input matrix
 * @param out The output matrix
 * @return 0 success, negative otherwise
 * @note The function can be an efficient way to calculate the inverse of small matrices,
 * but the recursive method is inefficient for large matrices.
 */
int matrix_inverse(matrix_t *in, matrix_t *out);

/**
 * print out a matrix
 *
 * @param matrix the matrix printed out
 * @return none
 */
void matrix_print(struct matrix_t *matrix);

/** @} */

/** @} */

#endif  /* MATRIX_H */
