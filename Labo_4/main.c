#include "convolutie_lib.h"
#include "lib_labo1.h"

int main(int argc, char ** argv)
{
	double x[] = { 1 ,2 ,3, 4, 5, 6, 7,8,9};
	double h[] = { 1 ,2 ,3 };
	double *y;
	y = (double *)calloc(size(x) + size(h) - 1, sizeof(double));
	blockconv(x, h, y, size(x), size(h), 3);

	for (int i = 0; i < size(x) + size(h) - 1; i++)
	{
		printf("%d: %lf\n", i, y[i]);
	}

	system("pause");
}