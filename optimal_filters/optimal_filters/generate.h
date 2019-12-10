#pragma once
#ifndef generate_h
#define generate_h

#include <iostream>

void generate_line(double* input, int size)
{
	srand(0);
	for (int i = 0; i < size; i++)
		input[i] = 1. + ((rand() % 100 / 100. - 0.5) / sqrt(12)) / 4;
}

void generate_sin_dis(double* input, int size)
{
	srand(0);
	for (int i = 0; i < size; i++)
		input[i] = 0.3 * sin(0.1 * i) + ((rand() % 100 / 100. - 0.5) / sqrt(12)) / 4;
}

void generate_sin_err(double* input, int size)
{
	srand(0);
	for (int i = 0; i < size; i++)
		input[i] = sin(0.1 * i) + ((rand() % 100 / 100. - 0.5) / sqrt(12)) / 2;
}

#endif // !generate_h
