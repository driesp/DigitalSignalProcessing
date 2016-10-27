#include "lib_labo1.h"

void generate_sinewave(double A, double f, double fs, double phi, int N, double *returnValue)
{
	for (int i = 0; i < N; i++)
	{
		returnValue[i] = A * sin(2*pi*f*i/fs+phi);
	}

}
void addwaves(double *x1, double *x2, int L, double *returnValue)
{
	for (int i = 0; i < L; i++)
	{
		returnValue[i] = x1[i] + x2[i];
	}
}