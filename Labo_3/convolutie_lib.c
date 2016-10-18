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

int convolution_2D(double **input, double **KERNEL, int size, int rows_input, int colums_input, double **output)
{
	int offsetX, offsetY;
	int sizeX = colums_input + 1;
	int sizeY = rows_input + 1;
	double **inputAdj = (double **)calloc(sizeY, sizeof(double*));
	for (int i = 0; i < sizeY; i++)
	{
		inputAdj[i] = (double*)calloc(sizeX, sizeof(double));
	}
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (j - 1 <= 0 && i - 1 <= 0)
			{
				inputAdj[j][i] = input[0][0];
			}
			else if(j - 1 >= colums_input && i -1 >= rows_input)
			{
				inputAdj[j][i] = input[colums_input][rows_input];
			}
		}
	}

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
			output[i][j] = sum;
		}
	}

	return 0;

}