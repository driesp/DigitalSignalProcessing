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

int convolution_2D(double **input, double **KERNEL, int size, int rows_input, int colums_input, double tresh, double **output)
{
	int offsetX, offsetY;
	int sizeX = colums_input + 1;
	int sizeY = rows_input + 1;

	if (size % 2 != 1)
	{
		return 1;
	}
	else
	{
		offsetX = offsetY =(size - 1) / 2;
	}

	

	for (int i = offsetY; i < (rows_input - offsetY); i++)
	{
		for (int j = offsetX; j < (colums_input - offsetX); j++)
		{
			double sum = 0;
			for (int y = 0; y < size; y++)
			{
				for (int x = 0; x < size; x++)
				{
					//printf("kernel: %lf, input: %lf", KERNEL[x][y], input[j + (x - 1)][i + (y - 1)]);
					sum += KERNEL[x][y] * input[j + (x - 1)][i + (y - 1)];
				}
			}
			//printf("%lf", sum);
			if (sum > tresh)
			{
				output[i][j] = 0xFF;
			}
			else
			{
				output[i][j] = 0x00;
			}
			
		}
	}

	return 0;

}

int blockconv(double * xn, double *hn, double *y, int xlen, int hlen, int L)
{
	int overflow = (hlen - 1);
	int blockcount = 0;
	if (xlen%L < 0)
	{
		blockcount = (xlen / L) + 1;

	}
	else
	{
		blockcount = (xlen / L);
	}
	
	double *block = (double *)calloc(L, sizeof(double));
	for (int i = 0; i < blockcount; i++)
	{
		double *tempResult = (double *)calloc((L + hlen) - 1, sizeof(double));
		
		for (int j = 0; j < L; j++)
		{
			block[j] = xn[(i*L + j)];
		}
		convolution_1D(block, hn, tempResult, L, hlen);
		

		for (int j = 0; j < L+ overflow; j++)
		{
			//printf("%lf - ", tempResult[j]);
			y[(i*L) + j] = tempResult[j] + y[(i*L) + j];

		}
		//printf("\n");
		free(tempResult);
	}
	free(block);
}