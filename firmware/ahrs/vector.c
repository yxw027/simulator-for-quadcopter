#include "vector.h"

void vector_add(double *src1, double *src2, double *dst, int size)
{
    int i;
    for (i = 0; i < size; i++)
        dst[i] = src1[i] + src2[i];
}

void vector_copy(double *dst, double *src, int size)
{
    int i;

    for (i = 0; i < size; i++)
        dst[i] = src[i];
}

void vector_scale(double dst[], double src[], double scale)
{
    int i;

    for (i = 0; i < size; i++)
        dst[i] = src[i] * scale;
}