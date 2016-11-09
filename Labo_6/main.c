
#include "dft.h"
#include "lib_labo1.h"

#define N 8

int main(int argc, char **argv)
{

  double *x1 = (double*)calloc(N, sizeof(double));
	double *x2 = (double*)calloc(N, sizeof(double));
	double *x = (double*)calloc(N, sizeof(double));
  double *xTemp = (double*)calloc(N, sizeof(double));
  double *xTemp2 = (double*)calloc(N, sizeof(double));
  int size;
  generate_sinewave(1, 1000, 8000, 0, N, x1);
	generate_sinewave(1, 1234, 8000, 0, N, x2);


  windowing(2, x1, xTemp, N);

  size = zeropadding(xTemp, xTemp2, N);

  double * X_Re =(double*) calloc(size, sizeof(double));
	double * X_Im = (double*)calloc(size, sizeof(double));
	double * X_Mag = (double*)calloc(size, sizeof(double));
	double * X_Phase = (double*)calloc(size, sizeof(double));

  dft(xTemp2, X_Re, X_Im, X_Mag, X_Phase, size);

  for(int i = 0; i < size; i++)
  {
    printf("%d:\t%lf\t%lf\n", i, X_Im[i], X_Phase[i]);
  }

}
