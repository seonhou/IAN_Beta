// Set Weight and Bias from X to W, b START

#pragma once

void X2Wb(RealVector& __X, const IntVector& __S, int __R, int __M, vector<RealMatrix>& __W, vector<RealVector>& __b)
{
	int count_x = 0;
	for(int i=0; i<__S[0]; i++){
		for(int j=0; j<__R; j++){
			__W[0](i,j) = __X[count_x];
			count_x = count_x + 1;
		}
	}
	for(int i=0; i<__S[0]; i++){
		__b[0](i) = __X[count_x];
		count_x = count_x + 1;
	}

	for(int m=1; m<__M; m++){
		for(int i=0; i<__S[m]; i++){
			for(int j=0; j<__S[m-1]; j++){
				__W[m](i,j) = __X[count_x];
				count_x = count_x + 1;
			}
		}
		for(int i=0; i<__S[m]; i++){
			__b[m](i) = __X[count_x];
			count_x = count_x + 1;
		}
	}
}