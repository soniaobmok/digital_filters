#pragma once
#pragma once
#ifndef fir_h
#define fir_h

#include <iostream>
#define M_PI 3.1415926

void fir(double in[], double out[], int sizeIn)
{
	const int N = 4; //Длина фильтра
	double Fd = 2000; //Частота дискретизации входных данных
	double Fs = 2; //Частота полосы пропускания
	double Fx = 3; //Частота полосы затухания

	long double H[N] = { 0 }; //Импульсная характеристика фильтра
	long double H_id[N] = { 0 }; //Идеальная импульсная характеристика
	long double W[N] = { 0 }; //Весовая функция

							  //Расчет импульсной характеристики фильтра
	double Fc = (Fs + Fx) / (2 * Fd);

	for (int i = 0; i < N; i++) {
		if (i == 0) H_id[i] = 2 * M_PI*Fc;
		else H_id[i] = sinl(2 * M_PI*Fc*i) / (M_PI*i);
		// весовая функция Блекмена
		//W[i] = 0.42 - 0.5 * cosl((2 * M_PI*i) / (N - 1)) + 0.08 * cosl((4 * M_PI*i) / (N - 1));
		// Hanna
		W[i] = 0.5 - 0.5 * cos((2 * M_PI * i) / (N - 1));
		H[i] = H_id[i] * W[i];
	}

	//Нормировка импульсной характеристики
	double SUM = 0;
	for (int i = 0; i < N; i++)
		SUM += H[i];

	for (int i = 0; i < N; i++)
		H[i] /= SUM;            //сумма коэффициентов равна 1 

								//Фильтрация входных данных
	for (int i = 0; i < sizeIn + 1; i++) {
		out[i] = 0.;
		for (int j = 0; j < N - 1; j++)// та самая формула фильтра
			if (i - j > 0)
				out[i] += H[j] * in[i - j];
	}
}

#endif // !fir_h
