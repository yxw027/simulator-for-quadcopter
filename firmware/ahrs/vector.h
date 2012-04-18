/**
 * @file vector.h
 * @brief vector interface
 */

#ifndef _VECTOR_H
#define _VECTOR_H


/* vector ops */
void vector_add(double src1[], double src2[], double dst[], int size);
void vector_copy(double *dst, double *src, int size);
void vector_scale(double *dst, double src, double scale);
void vector_crossproduct();
