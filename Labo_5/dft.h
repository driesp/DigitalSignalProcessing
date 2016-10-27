

#define  _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef M_PI
#define pi M_PI
#else
#define pi 4*atan(1.0)
#endif

void dft(double *x, double *X_Re, double *X_Im, double *X_Mag, double *X_Phase, int N);