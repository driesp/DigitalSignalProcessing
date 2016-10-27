#include "dft.h"


void dft(double *x, double *X_Re, double *X_Im, double *X_Mag, double *X_Phase, int N)
{
	for (int m = 0; m < N; m++)
	{
		for (int n = 0; n < N; n++)
		{
			X_Re[m] += x[n] * cos(2 * pi * n * m / N);
			X_Im[m] += -1 * x[n] * sin(2 * pi * n * m / N);
		}
		
		X_Mag[m] = sqrt(X_Re[m]* X_Re[m] + X_Im[m]* X_Im[m]);
		X_Phase[m] = atan2(round(X_Im[m]), round(X_Re[m])) * (180.0 / M_PI);

	}
}