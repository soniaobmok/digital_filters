#pragma once
#ifndef lms_h
#define lms_h

#include <iostream>
#include <fstream>
using namespace std;

#define mu 0.2f				//convergence rate
#define M 2					//order of filter
//
////double H[M] = { 1, 0.5, 0.25, 0.125, 0.0625 };	//the main system
double H[M] = { /*0.0625, 0.125, 0.25,*/ 0.25, 1 };		//we need inverse of main system to convolution

void lms(double* input, double * output, int size)
{

	double D, Y, E;
	double W[M] = { 0.0 };
	double X[M] = { 0.0 };
	double* Desired = new double[size];
	for (int i = 0; i < size; i++)
		Desired[i] = { 0.0 };

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < M; j++) {
			if (i - j >= 0)
				Desired[i] += input[i - j] * H[j];
		}
	}

	for (int T = 0; T < size; T++) {
		for (int m = T; m > T - M; m--) {
			if (m >= 0)
				X[M + (m - T) - 1] = input[m];	//X new input sample for
												//LMS filter
			else break;
		}

		D = Desired[T];					//desired signal
		Y = 0;						//filter’output set to zero

		for (int i = 0; i < M; i++)
			Y += (W[i] * X[i]);			//calculate filter output

		E = D - Y;					//calculate error signal

		for (int i = 0; i < M; i++)
			W[i] = W[i] + (mu * E * X[i]);		//update filter coefficients

		output[T] = Y;
	}
}

#endif // !lms_h
