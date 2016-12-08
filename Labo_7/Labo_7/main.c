#include "convolutie_lib.h"
#include "dft.h"
#include "lib_labo1.h"

#define COUNT 16

int main(int argc, char **argv)
{

	double coeffs[20] = { 
		0.0024299026793099168,
		-0.0036194227325605918,
		-0.0045823837540180812,
		0.023830888614483733,
		-0.034411729138247721,
		0.0059983453227902619,
		0.060983749757701378,
		-0.10332269715906811,
		0.0083691782273127985,
		0.54469607713356805,
		0.54469607713356805,
		0.0083691782273127985,
		-0.10332269715906811,
		0.060983749757701378,
		0.0059983453227902619,
		-0.034411729138247721,
		0.023830888614483733,
		-0.0045823837540180812,
		-0.0036194227325605918,
		0.0024299026793099168 
	};
	int aantal = COUNT + size(coeffs) - 1;
	double * wave1 = (double*)calloc(COUNT, sizeof(double));
	double * wave2 = (double*)calloc(COUNT, sizeof(double));
	double * SOM = (double*)calloc(COUNT, sizeof(double));
	double * RESULT = (double*)calloc(aantal, sizeof(double));
	double * X_Re= (double*)calloc(COUNT, sizeof(double));
	double * X_Im = (double*)calloc(COUNT, sizeof(double));
	double * X_Mag = (double*)calloc(COUNT, sizeof(double));
	double * X_Phase = (double*)calloc(COUNT, sizeof(double));
	double * X_Re1 = (double*)calloc(aantal, sizeof(double));
	double * X_Im1 = (double*)calloc(aantal, sizeof(double));
	double * X_Mag1 = (double*)calloc(aantal, sizeof(double));
	double * X_Phase1 = (double*)calloc(aantal, sizeof(double));

	generate_sinewave(1, 2000, 16000, 0, COUNT, wave1);
	generate_sinewave(1, 6000, 16000, 0, COUNT, wave2);

	addwaves(wave1, wave2, COUNT, SOM);

	dft(SOM, X_Re, X_Im, X_Mag, X_Phase, COUNT);
	printf("DFT Before FIR:\n");
	for (int i = 0; i < COUNT; i++)
	{
		printf("%lf,",X_Mag[i]);
	}
	printf("\n");

	fir(SOM, &coeffs, RESULT, COUNT, 20);
	printf("FIR:\n");
	for (int i = 0; i < aantal; i++)
	{
		printf("%d: -> %lf\n", i, RESULT[i]);
	}

	dft(RESULT, X_Re1, X_Im1, X_Mag1, X_Phase1, aantal);
	printf("DFT After FIR:\n");
	for (int i = 0; i < aantal; i++)
	{
		printf("%lf,", X_Mag1[i]);
	}
	printf("\n");

	system("pause");



	return 1;
}