
#pragma once

#include "get_activated_value.h"

// Neural Network Calculation for TEST or VALIDATION dataset
RealMatrix ANN(int __Q, int __R, int __M, const IntVector& __S, IntVector& __Trans, RealMatrix& __Pmap, vector<RealMatrix>& __W, vector<RealVector>& __b)
{
	vector<RealMatrix> N(__M);
	vector<RealMatrix> A(__M);

	for(int i=0; i<__M; i++){
		N[i].resize(__S[i],__Q);
		A[i].resize(__S[i],__Q);
	}

	double temp = 0;
	for(int i=0; i<__S[0]; i++){
		for(int q=0; q<__Q; q++){
			for(int r=0; r<__R; r++){
				temp += __W[0](i,r) * __Pmap(r,q);
			}
			N[0](i,q) = temp;
			temp = 0;
		}
	}

	for(int i=0; i<__S[0]; i++){
		for(int q=0; q<__Q; q++){
			temp = N[0](i,q) + __b[0](i);
			N[0](i,q) = temp;
		}
	}

	for(int i=0; i<__S[0]; i++){
		for(int q=0; q<__Q; q++){
			temp = get_activated_value(__Trans(0), N[0](i, q));
			A[0](i,q) = temp;
		}
	}

	for(int m=1; m<__M; m++){
		temp = 0;
		for(int i=0; i<__S[m]; i++){
			for(int q=0; q<__Q; q++){
				for(int k=0; k<__S[m-1]; k++){
					temp += __W[m](i,k) * A[m-1](k,q);
				}
				N[m](i,q) = temp;
				temp = 0;
			}
		}

		for(int i=0; i<__S[m]; i++){
			for(int q=0; q<__Q; q++){
				temp = N[m](i,q) + __b[m](i);
				N[m](i,q) = temp;
			}
		}

		for(int i=0; i<__S[m]; i++){
			for(int q=0; q<__Q; q++){
				temp = get_activated_value(__Trans(m), N[m](i, q));
				A[m](i,q) = temp;
			}
		}
	}

	return A[__M-1];
}


// Neural Network Calculation for TRAINING dataset

// Training dataset�� ��� Jacobian ����� ���� 'train_A'�� ������ �ʿ��ϰ�
// ���� Marquardt Sensitivity ����� ���� '__train_N'�� �ʿ��ϹǷ�
// ������ ANN_train �Լ��� ������

vector<RealMatrix> ANN_train(int __Q, int __R, int __M, const IntVector& __S, IntVector& __Trans, RealMatrix& __Pmap, vector<RealMatrix>& __W, vector<RealVector>& __b, vector<RealMatrix>& __train_N)
{
	vector<RealMatrix> A(__M);

	for(int i=0; i<__M; i++){
		A[i].resize(__S[i],__Q);
	}

	double temp = 0;
	for(int i=0; i<__S[0]; i++){
		for(int q=0; q<__Q; q++){
			for(int r=0; r<__R; r++){
				temp += __W[0](i,r) * __Pmap(r,q);
			}
			__train_N[0](i,q) = temp;
			temp = 0;
		}
	}

	for(int i=0; i<__S[0]; i++){
		for(int q=0; q<__Q; q++){
			temp = __train_N[0](i,q) + __b[0](i);
			__train_N[0](i,q) = temp;
		}
	}

	for(int i=0; i<__S[0]; i++){
		for(int q=0; q<__Q; q++){
			temp = get_activated_value(__Trans(0), __train_N[0](i, q));
			A[0](i,q) = temp;
		}
	}

	for(int m=1; m<__M; m++){
		temp = 0;
		for(int i=0; i<__S[m]; i++){
			for(int q=0; q<__Q; q++){
				for(int k=0; k<__S[m-1]; k++){
					temp += __W[m](i,k) * A[m-1](k,q);
				}
				__train_N[m](i,q) = temp;
				temp = 0;
			}
		}

		for(int i=0; i<__S[m]; i++){
			for(int q=0; q<__Q; q++){
				temp = __train_N[m](i,q) + __b[m](i);
				__train_N[m](i,q) = temp;
			}
		}

		for(int i=0; i<__S[m]; i++){
			for(int q=0; q<__Q; q++){
				temp = get_activated_value(__Trans(m), __train_N[m](i, q));
				A[m](i,q) = temp;
			}
		}
	}

	return A;
}