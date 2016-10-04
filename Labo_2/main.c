#include <stdio.h>
#include "lib_labo1.h"
#include "convolutie_lib.h"

int main(int argc, char **argv[])
{
	double x[] = { 1 ,2 ,3,4,5 };
	double h[] = { 1 ,2,3};
	double *y;
	y = (double *)calloc(size(x) + size(h) - 1, sizeof(double));

	convolution_1D(x, h, y, size(x), size(h));
	for (int i = 0; i < size(x) + size(h) -1 ; i++)
	{
		printf("%d: %lf\n", i, y[i]);
	}
	system("pause");
}