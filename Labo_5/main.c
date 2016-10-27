#include "dft.h"
#include "lib_labo1.h"

#define N 8

int main(int argc, char **argv)
{
	double * X_Re =(double*) calloc(N , sizeof(double));
	double * X_Im = (double*)calloc(N, sizeof(double));
	double * X_Mag = (double*)calloc(N, sizeof(double));
	double * X_Phase = (double*)calloc(N, sizeof(double));
	double *x1 = (double*)calloc(N, sizeof(double));
	double *x2 = (double*)calloc(N, sizeof(double));
	double *x = (double*)calloc(N, sizeof(double));

	generate_sinewave(1, 1000, 8000, 0, N, x1);
	generate_sinewave(0.5, 2000, 8000, (3 * pi / 4), N, x2);

	addwaves(x1, x2, N, x);

	dft(x, X_Re, X_Im, X_Mag, X_Phase, N);

	for (int i = 0; i < N; i++)
	{
		printf("%d: -Mag:%lf -Phase:%lf \n", i, X_Mag[i], X_Phase[i]);
	}

	system("pause");
}