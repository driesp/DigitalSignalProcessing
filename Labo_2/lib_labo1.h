#pragma once
#define  _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef M_PI
	#define pi M_PI
#else
	#define pi 4*atan(1.0)
#endif

void generate_sinewave(double A, double f, double fs, double phi, int N, double *returnValue);
void addwaves(double *x1, double *x2, int L, double *returnValue);