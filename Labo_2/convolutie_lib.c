#include "convolutie_lib.h"

void convolution_1D(double * xn, double *hn, double *y, int xlen, int hlen)
{
	for (int i = 0; i < xlen + hlen - 1; i++)
	{
		int kmin, kmax, k;
		if (i >= hlen - 1) 
		{
			kmin = i - (hlen - 1);
		}
		else
		{
			kmin = 0;
		}
		if (i < xlen - 1)
		{
			kmax = i;
		}
		else
		{
			kmax = xlen - 1;
		}

		for (k = kmin; k <= kmax; k++)
		{
			y[i] += xn[k] * hn[i - k];
		}
	}
}