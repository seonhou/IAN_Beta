#pragma once

void kernel_initializer(vector<RealMatrix>& __W, vector<RealVector>& __b, const IntVector& __S, int __R, int __M, IntVector __kernel_init)
{
	double stddev = 1.0;

	random_device rd;
	mt19937 gen(rd());

	// W0 initilization
	if (__kernel_init(0) == 0) {
		stddev = sqrt(2 / ((double)__R + (double)__S[0]));
	}
	else if (__kernel_init(0) == 1) {
		stddev = sqrt(1 / (double)__R);
	}
	else {
		stddev = sqrt(2 / (double)__R);
	}
	
	normal_distribution<> distr(0, stddev);
	
	for (int i = 0; i < __S[0]; i++) {
		for (int j = 0; j < __R; j++) {
			__W[0](i, j) = distr(gen);
		}
	}

	// Other weights initilization
	for (int m = 1; m < __M; m++) {
		if (__kernel_init(m) == 0) {
			stddev = sqrt(2 / ((double)__S[m - 1] + (double)__S[m]));
		}
		else if (__kernel_init(m) == 1) {
			stddev = sqrt((1 / (double)__S[m - 1]));
		}
		else {
			stddev = sqrt((2 / (double)__S[m - 1]));
		}

		normal_distribution<> distr(0, stddev);

		for (int i = 0; i < __S[m]; i++) {
			for (int j = 0; j < __S[m - 1]; j++) {
				__W[m](i, j) = distr(gen);
			}
		}
	}

	for (int m = 0; m < __M; m++) {
		for (int i = 0; i < __S[m]; i++) {
			__b[m](i) = 0;
		}
	}
}