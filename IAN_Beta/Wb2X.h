#pragma once

void Wb2X(vector<RealMatrix>& __W, vector<RealVector>& __b, RealVector& __X, const IntVector& __S, int __R, int __M)
{
	int count_x = 0;
	for (int i = 0; i < __S[0]; i++) {
		for (int j = 0; j < __R; j++) {
			__X[count_x] = __W[0](i, j);
			count_x += 1;
		}
	}
	for (int i = 0; i < __S[0]; i++) {
		__X[count_x] = __b[0](i);
		count_x += 1;
	}

	for (int m = 1; m < __M; m++) {
		for (int i = 0; i < __S[m]; i++) {
			for (int j = 0; j < __S[m - 1]; j++) {
				__X[count_x] = __W[m](i, j);
				count_x += 1;
			}
		}
		for (int i = 0; i < __S[m]; i++) {
			__X[count_x] = __b[m](i);
			count_x += 1;
		}
	}
}