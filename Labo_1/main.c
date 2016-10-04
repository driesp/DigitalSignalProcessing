#include <stdio.h>
#include <stdlib.h>
#include "lib_labo1.h"

#define samples 1000000

int main(int argc, char **argv[])
{
	double *x1,*x2, *sum;
	x1 = (double*)calloc(samples, sizeof(double));
	x2 = (double*)calloc(samples, sizeof(double));
	sum = (double*)calloc(samples, sizeof(double));
	generate_sinewave(1, 1000, 8000, 0, samples, x1);
	generate_sinewave(1, 2000, 8000,(3 * pi / 4), samples, x2);
	addwaves(x1, x2, samples, sum);

	for (int i = 0; i < samples; i++)
	{
		printf("%d: x1 = %lf, x2 = %lf, sum = %lf \n", i, x1[i], x2[i], sum[i]);
	}
	free(x1);
	free(x2);
	free(sum);
	system("pause");
}

