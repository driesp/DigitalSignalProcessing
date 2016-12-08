#include "convolutie_lib.h"
#include "qdbmp.h"

#define kernel 3

#define LAP 25
#define SOBEL 50
#define PREWITT 100

int main(int argc, char ** argv)
{
	BMP * bmp;
	bmp = BMP_ReadFile("test.bmp");

	UINT width = BMP_GetWidth(bmp);
	UINT height = BMP_GetHeight(bmp);

	double **output = (double **)calloc(height, sizeof(double*));
	for (int i = 0; i < height; i++)
	{
		output[i] = (double*)calloc(width, sizeof(double));
	}
	double **output_2 = (double **)calloc(height, sizeof(double*));
	for (int i = 0; i < height; i++)
	{
		output_2[i] = (double*)calloc(width, sizeof(double));
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

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			UCHAR val;
			BMP_GetPixelIndex(bmp, j, i, &val);
			input[j][i] = (double) val;
		}
	}
	KERNEL[0][0] = 0; KERNEL[0][1] = -1; KERNEL[0][2] = 0;
	KERNEL[1][0] = -1; KERNEL[1][1] = 4; KERNEL[1][2] = -1;
	KERNEL[2][0] = 0; KERNEL[2][1] = -1; KERNEL[2][2] = 0;

	convolution_2D(input, KERNEL, kernel, height, width,LAP, output);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			UCHAR val = output[i][j] ;
			BMP_SetPixelIndex(bmp, j, i, val);
		}
	}

	BMP_WriteFile(bmp, "LAPLACIAAN.bmp");

	/*
	* Sobel kernel
	*/

	KERNEL[0][0] = -1; KERNEL[0][1] = 0; KERNEL[0][2] = 1;
	KERNEL[1][0] = -2; KERNEL[1][1] = 0; KERNEL[1][2] = 2;
	KERNEL[2][0] = -1; KERNEL[2][1] = 0; KERNEL[2][2] = 1;

	convolution_2D(input, KERNEL, kernel, height, width, SOBEL, output);

	KERNEL[0][0] = -1; KERNEL[0][1] = -2; KERNEL[0][2] = -1;
	KERNEL[1][0] = 0; KERNEL[1][1] = 0; KERNEL[1][2] = 0;
	KERNEL[2][0] = 1; KERNEL[2][1] = 2; KERNEL[2][2] = 1;

	convolution_2D(input, KERNEL, kernel, height, width, SOBEL ,output_2);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			UCHAR val = sqrt( pow(output[i][j],2)+pow(output_2[i][j],2));
			BMP_SetPixelIndex(bmp, j, i, val);
		}
	}
	BMP_WriteFile(bmp, "SOBEL.bmp");


	/*
	* PREWITT kernel
	*/
	

	KERNEL[0][0] = -1; KERNEL[0][1] = -1; KERNEL[0][2] =-1;
	KERNEL[1][0] = 0; KERNEL[1][1] = 0; KERNEL[1][2] = 0;
	KERNEL[2][0] = 1; KERNEL[2][1] = 1; KERNEL[2][2] = 1;

	convolution_2D(input, KERNEL, kernel, height, width, PREWITT ,output);

	KERNEL[0][0] = -1; KERNEL[0][1] = 0; KERNEL[0][2] = 1;
	KERNEL[1][0] = -1; KERNEL[1][1] = 0; KERNEL[1][2] = 1;
	KERNEL[2][0] = -1; KERNEL[2][1] = 0; KERNEL[2][2] = 1;

	convolution_2D(input, KERNEL, kernel, height, width, PREWITT ,output_2);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			UCHAR val = sqrt(pow(output[i][j], 2) + pow(output_2[i][j], 2));
			BMP_SetPixelIndex(bmp, j, i, val);
		}
	}

	BMP_WriteFile(bmp, "PREWITT.bmp");

}