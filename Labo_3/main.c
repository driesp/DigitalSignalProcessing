#include <stdio.h>
#include "convolutie_lib.h"
#include "lib_labo1.h"


#define kernel 3
#define width 5
#define height 5

int main(int argc, char **argv[])
{
	double **output = (double **)calloc(height, sizeof(double*));
	for (int i = 0; i < height; i++)
	{
		output[i] = (double*)calloc(width, sizeof(double));
	}
	double **KERNEL = (double **)calloc(kernel, sizeof(double*));
	for (int i = 0; i < kernel; i++)
	{
		KERNEL[i] = (double*)calloc(kernel, sizeof(double));
	}
	double **input = (double **)calloc(height, sizeof(double*));
	for (int i = 0; i < height; i++)
	{
		input[i] = (double*)calloc(width, sizeof(double));
	}
	
	double temp1[kernel][kernel] = { {1,2,1	},
									 {0,0,0},
							         {-1,-2,-1} };
	double temp2[width][height] = { { 0,0,0,0,0 },
									{ 0,1,2,3,0 },
									{ 0,4,5,6,0 },
									{ 0,7,8,9,0 },
									{ 0,0,0,0,0 } };

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			input[j][i] = temp2[j][i];
		}
	}
	for (int i = 0; i < kernel; i++)
	{
		for (int j = 0; j < kernel; j++)
		{
			KERNEL[j][i] = temp1[j][i];
		}
	}

	

	convolution_2D(input, KERNEL, kernel, height, width, output);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%lf,\t", output[j][i]);
		}
		printf("\n");
	}

	system("pause");
}