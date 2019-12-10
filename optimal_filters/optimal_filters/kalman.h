#pragma once
#pragma once
#ifndef kalman_h
#define kalman_h

#include <iostream>

class Kalman_filter
{
public:
	double X0; //predicted state
	double P0; //predicted covariance
	double F; //factor of real value to previous real value
	double Q; // measurement noise
	double H; // factor of measured value to real value
	double R; // environment noise

	double state;
	double covariance;

	Kalman_filter(double q, double r, double f = 1, double h = 1) {
		Q = q;
		R = r;
		F = f;
		H = h;
	}

	void set_state(double state, double covariance) {
		state = state;
		covariance = covariance;
	}

	void correct(double data) {
		//time update - prediction
		X0 = F * state;
		P0 = F * covariance * F + Q;

		//measurement update - correction
		double K = H * P0 / (H * P0 * H + R);
		state = X0 + K * (data - H * X0);
		covariance = (1 - K * H) * P0;
	}
};

#endif // !kalman_h

