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
		X_Phase[m] = atan2(round(X_Im[m]), round(X_Re[m])) * (180.0 / pi);

	}
}

void windowing(int mode, double * input, double * output, int N )
{
	printf("%d\n",(int) sizeof(double) );
	switch(mode)
	{
		case 0:
		default:
			for(int i = 0; i < N; i++)
			{
				output[i] = input[i];
			}
			break;
		case 1:
			for(int i = 0; i <= N/2; i++)
			{
				output[i] = input[i] * i/(N/2);
			}
			for(int i = N/2; i <= N-1; i++)
			{
				output[i] = input[i] * (2 - i/(N/2));
			}
			break;
		case 2:
			for(int i = 0; i < N; i++)
			{
				output[i] =  input[i] * (0,5 - 0,5 *cos(2* pi * (i/N - 1)));
			}
			break;
		case 3:
			for(int i = 0; i < N; i++)
			{
				output[i] =  input[i] * (0,54 - 0,46 *cos(2* pi * (i/N - 1)));
			}
			break;
	}
}

int zeropadding(double *input, double *output, int N)
{
	int next = (int) pow(2,(log10(N)/log10(2)) + 1);
	output = (double * ) realloc(input, next*sizeof(double));
	for(int i = N; i < next; i++)
	{
		output[i] = 0;
	}
	return next;
}
