#pragma once

#define  _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define size(a) sizeof(a)/sizeof(a[0])

void convolution_1D(double * xn, double *hn, double *y, int xlen, int hlen);
int convolution_2D(double **input, double **KERNEL, int size, int rows_input, int colums_input, double tresh, double **output);
int blockconv(double * xn, double *hn, double *y, int xlen, int hlen, int L);