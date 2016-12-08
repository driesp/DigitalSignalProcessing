#include "convolutie_lib.h"

void convolution_1D(double * xn, double *hn, double *y, int xlen, int hlen)
{
	for (int n = 0; n < xlen + hlen - 1; n++)
	{
		int kmin, kmax, k;
		if (n < hlen - 1) 
		{
			kmin = 0;
		}
		else
		{
			kmin = n - (hlen - 1);
			
		}
		if (n >= xlen - 1)
		{
			kmax = xlen - 1;
		}
		else
		{
			
			kmax = n;
		}

		for (k = kmin; k <= kmax; k++)
		{
			y[n] += xn[k] * hn[n - k];
		}
	}
}
void fir(double * xn, double *hn, double *y, int xlen, int hlen)
{
	for (int n = 0; n < xlen + hlen - 1; n++)
	{
		int kmin, kmax, k;
		if (n < hlen - 1)
		{
			kmin = 0;
		}
		else
		{
			kmin = n - (hlen - 1);

		}
		if (n >= xlen - 1)
		{
			kmax = xlen - 1;
		}
		else
		{

			kmax = n;
		}

		for (k = kmin; k <= kmax; k++)
		{
			y[n] += xn[n-k] * hn[k];
		}
	}
}