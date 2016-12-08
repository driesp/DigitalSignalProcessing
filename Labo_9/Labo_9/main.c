#include "qdbmp.h"

static int calcMedian(UCHAR **input, int size, int rows_input, int colums_input, UCHAR **output);

int main(int argc, char ** argv)
{
	BMP* bmp, *bmp_out;
	bmp = BMP_ReadFile("lena_256_20%.bmp");
	UINT width = BMP_GetWidth(bmp);
	UINT height = BMP_GetHeight(bmp);
	bmp_out = BMP_Create(width, height, 8);
	UCHAR **Array = (UCHAR **)calloc(width, sizeof(UCHAR*));
	for (int i = 0; i < width; i++)
	{
		Array[i] = (UCHAR*)calloc(height, sizeof(UCHAR));
	}
	UCHAR **Out = (UCHAR **)calloc(width, sizeof(UCHAR*));
	for (int i = 0; i < width; i++)
	{
		Out[i] = (UCHAR*)calloc(height, sizeof(UCHAR));
	}
	UCHAR **Out_1 = (UCHAR **)calloc(width, sizeof(UCHAR*));
	for (int i = 0; i < width; i++)
	{
		Out_1[i] = (UCHAR*)calloc(height, sizeof(UCHAR));
	}
	UCHAR **Out_2 = (UCHAR **)calloc(width, sizeof(UCHAR*));
	for (int i = 0; i < width; i++)
	{
		Out_2[i] = (UCHAR*)calloc(height, sizeof(UCHAR));
	}
	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			UCHAR val;
			//BMP_GetPixelRGB(bmp, j, i, &r, &g, &b);
			BMP_GetPixelIndex(bmp, j, i, &val);
			//BMP_SetPixelRGB(bmp_out, j, i, r,g,b);
			//printf("val:%d \t", val);
			Array[i][j] = val;
		}
	}
	calcMedian(Array,7, height, width, Out);
	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			BMP_SetPixelIndex(bmp_out, j, i, Out[i][j]);
		}
	}

	for (int i = 0; i < 256; i++)
	{
		BMP_SetPaletteColor(bmp_out, i, i, i, i);
	}

	BMP_WriteFile(bmp_out, "pass17x7.bmp");
	calcMedian(Out, 7, height, width, Out_1);
	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			BMP_SetPixelIndex(bmp_out, j, i, Out_1[i][j]);
		}
	}
	BMP_WriteFile(bmp_out, "pass27x7.bmp");

	calcMedian(Out_1, 7, height, width, Out_2);
	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			BMP_SetPixelIndex(bmp_out, j, i, Out_2[i][j]);
		}
	}

	BMP_WriteFile(bmp_out,"pass37x7.bmp");
	system("pause");
}

static int calcMedian(UCHAR **input, int size, int rows_input, int colums_input, UCHAR **output)
{
	int offsetX, offsetY;
	UCHAR *list = (UCHAR*)calloc(size*size, sizeof(UCHAR));
	/*
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
			else if (j - 1 >= colums_input && i - 1 >= rows_input)
			{
				inputAdj[j][i] = input[colums_input][rows_input];
			}
		}
	}
	*/

	if (size % 2 != 1)
	{
		return 1;
	}
	else
	{
		offsetX = offsetY = (size - 1) / 2;
	}



	for (int i = offsetY; i < (rows_input - offsetY); i++)
	{
		for (int j = offsetX; j < (colums_input - offsetX); j++)
		{
			int d = 0;
			for (int y = 0; y < size; y++)
			{
				for (int x = 0; x < size; x++)
				{
					list[d] = input[(i-offsetY)+ y][(j-offsetX)+x]; 
					d++;
				}
			}
			/*
			for (int g = 0; g < (size*size); g++)
			{
				printf("%d:%d\t", g, list[g]);
			}
			printf("\n");
			*/
			int e, f;
			UCHAR temp;
			for (e = 0; e < ((size*size) - 1); e++)
			{
				for (f = 0; f < (size*size) - e - 1; f++)
				{
					if (list[f] > list[f + 1])
					{
						/* Swapping */

						temp = list[f];
						list[f] = list[f + 1];
						list[f + 1] = temp;
					}
				}
			}
			/*
			for (int g = 0; g < (size*size); g++)
			{
				printf("%d:%d\t", g, list[g]);
			}
			printf("\n");
			*/
			int t = (size*size - 1) / 2;
			output[i][j] = list[t+1];
		}
	}

	return 0;
}