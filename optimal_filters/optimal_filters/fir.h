#pragma once
#pragma once
#ifndef fir_h
#define fir_h

#include <iostream>
#define M_PI 3.1415926

void fir(double in[], double out[], int sizeIn)
{
	const int N = 4;
	double Fd = 2000; 
	double Fs = 2; 
	double Fx = 3; 

	long double H[N] = { 0 };
	long double H_id[N] = { 0 }; 
	long double W[N] = { 0 };

						
	double Fc = (Fs + Fx) / (2 * Fd);

	for (int i = 0; i < N; i++) {
		if (i == 0) H_id[i] = 2 * M_PI*Fc;
		else H_id[i] = sinl(2 * M_PI*Fc*i) / (M_PI*i);

		W[i] = 0.5 - 0.5 * cos((2 * M_PI * i) / (N - 1));
		H[i] = H_id[i] * W[i];
	}

	double SUM = 0;
	for (int i = 0; i < N; i++)
		SUM += H[i];

	for (int i = 0; i < N; i++)
		H[i] /= SUM;

	for (int i = 0; i < sizeIn + 1; i++) {
		out[i] = 0.;
		for (int j = 0; j < N - 1; j++)
			if (i - j > 0)
				out[i] += H[j] * in[i - j];
	}
}

#endif // !fir_h
