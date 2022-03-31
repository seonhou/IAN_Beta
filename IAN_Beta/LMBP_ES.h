/*
[rev_-] First Release
[rev_A] relu updated (21.06.08)
*/

#pragma once

#include "mapminmax.h"
#include "TransferFnc.h"
#include "dataDivision.h"
#include "ANN.h"
#include "X2Wb.h"
#include "SaveANNoutput.h"
#include "getMSE_ES.h"
#include "isnan.h"

int LMBP_ES(const IntVector& _S, IntVector& _Trans, RealVector& _Pdata1, RealVector& _Pdata2, RealVector& _Tdata1, RealVector& _Tdata2, RealMatrix& _all_Pmap, RealMatrix& _all_Tmap, RealMatrix& _test_Pmap, RealMatrix& _test_Tmap, RealVector& _yminmax, int _max_step, int _patience, int _M, int _R, int _sM, int _train_Q, int _val_Q, int _test_Q, string _FileDir, int _kk, int _mucheck, int _normalization)
{
	clock_t LM_start, LM_finish;
	double LM_duration = 0;

	LM_start = clock();	

	int count = 1;
	int check = 0;
	int LMBP_converge = 0;

	// _all_Pmap, _all_Tmap: training + validation data
	RealMatrix train_Pmap(_R, _train_Q);
	RealMatrix train_Tmap(_sM, _train_Q);
	RealMatrix val_Pmap(_R, _val_Q);
	RealMatrix val_Tmap(_sM, _val_Q);
	RealMatrix SenAna(_R, _sM); // BackPropagation Sensitivity

	dataDivision(_all_Pmap, _all_Tmap, _R, _sM, _train_Q, _val_Q, train_Pmap, train_Tmap, val_Pmap, val_Tmap);

	// 아래는 MATLAB trainlm.m 에 나와있는 초기값을 활용함
	double mu = 0.001;
	double mu_max = 1e10;
	int nu = 10;

	int size_x = _S[0] * (_R + 1);
	for (int i = 1; i < _M; i++) {
		size_x = size_x + _S[i] * (_S[i - 1] + 1);
	}

	int train_size_v = _sM * _train_Q; // Size of Error Vector
	int val_size_v = _sM * _val_Q; // Size of Validation Error Vector
	int test_size_v = _sM * _test_Q; // Size of Test Error Vector

	string stepout = _FileDir + "\\step.log";
	string dataout = _FileDir + "\\data.log";
	string MSEout  = _FileDir + "\\MSE_scaled.txt";
	string muout   = _FileDir + "\\mu.txt";

	ofstream fout;
	fout.open(stepout.c_str(), ios_base::out | ios_base::app);
	fout << "size_x = " << size_x << endl; // Number of Parameter (Weight and Bias)
	fout << "size_v = " << train_size_v << endl; // Number of Output (to calculate Error)
	fout << "size_Jacobian = " << size_x * train_size_v << endl; // Size of Jacobian
	fout << endl;
	fout.close();

	RealVector X1(size_x);
	RealVector X2(size_x);
	RealVector X3(size_x);

	// SET INITIAL VALUES OF PARAMETER X
	srand((unsigned int)time(NULL));

	for (int i = 0; i < size_x; i++) {
		X1[i] = (rand() % 1000) - 500;
		X1[i] = X1[i] / 1000;	// -0.5 < X1 < 0.5
	}

	/* This Code was maded for OPENMP
	RealVector X4(size_x);
	for (int i = 0; i < size_x; i++) {
		X4[i] = (rand() % 1000) - 500;	// X4를 이용하지 않으면 OpenMP사용 시 모두 같은 초기값으로 학습을 시작함 -> 병렬처리의 의미가 없음
		X4[i] = (X4[i] / 10000) * _kk;	// X4 = (-0.05 ~ 0.05) * kk의 범위를 가짐 --> kk가 커질수록 W1이 커짐 --> SenAna도 같이 커짐..
		X1[i] = X1[i] + X4[i];
	}
	*/

	for (int i = 0; i < size_x; i++) {
		X2[i] = 0;
		X3[i] = 0;
	}

	double FF1, FF2, FF3, FF4, MSE;

	FF3 = 1e10;

	// Allocate START
	vector<RealVector> b(_M);
	vector<RealMatrix> W(_M);
	vector<RealMatrix> train_N(_M);
	vector<RealMatrix> train_A(_M);
	vector<RealMatrix> MS(_M);
	vector<RealMatrix> MS_temp(_M - 1);
	vector<RealMatrix> MSWT(_M - 1);
	RealMatrix val_A(_S[_M - 1], _val_Q);
	RealMatrix test_A(_S[_M - 1], _test_Q);

	W[0].resize(_S[0], _R);

	for (int i = 1; i < _M; i++) {
		W[i].resize(_S[i], _S[i - 1]);
	}

	for (int i = 0; i < _M; i++) {
		b[i].resize(_S[i]);
		MS[i].resize(_S[i], _sM);
		train_N[i].resize(_S[i], _train_Q);
		train_A[i].resize(_S[i], _train_Q);
	}

	for (int i = 0; i < _M - 1; i++) {
		MS_temp[i].resize(_S[i], _S[i]);
		MSWT[i].resize(_S[i], _S[i + 1]);
	}
	// Allocate END
	RealVector V1(train_size_v);
	RealVector V2(train_size_v);
	RealVector val_V(val_size_v);
	RealVector test_V(test_size_v);

	RealVector del_x(size_x);
	RealMatrix J(train_size_v, size_x);
	RealMatrix JT(size_x, train_size_v);
	RealMatrix invJT(size_x, train_size_v);
	RealMatrix JTJmu(size_x, size_x);

	double temp = 0;

	do {
		fout.open(stepout.c_str(), ios_base::out | ios_base::app);
		fout << "Epoch : " << count << endl;
		fout.close();

		X2Wb(X1, _S, _R, _M, W, b);
		train_A = ANN_train(_train_Q, _R, _M, _S, _Trans, train_Pmap, W, b, train_N);
		FF1 = getMSE_ES(_sM, _train_Q, train_size_v, train_Tmap, train_A[_M - 1], V1);

		// Set Jacobian Matrix START
		int jrow = 0;
		int jcol = 0;

		for (int q = 0; q < _train_Q; q++) {

			// Set Marquardt Sensitivity START
			for (int i = 0; i < _sM; i++) {
				for (int j = 0; j < _sM; j++) {
					MS[_M - 1](i, j) = 0;
				}
			}

			for (int i = 0; i < _sM; i++) {
				temp = get_dactivated_value(_Trans(_M - 1), train_N[_M - 1](i, q));
				MS[_M - 1](i, i) = -temp;
			}

			for (int m = 0; m < _M - 1; m++) {
				for (int i = 0; i < _S[m]; i++) {
					temp = get_dactivated_value(_Trans(m), train_N[m](i, q));
					MS_temp[m](i, i) = temp;
				}
			}

			for (int m = 0; m < _M - 1; m++) {
				for (int i = 0; i < _S[m]; i++) {
					for (int j = 0; j < _S[m + 1]; j++) {
						MSWT[m](i, j) = 0;
					}
					for (int j = 0; j < _sM; j++) {
						MS[m](i, j) = 0;
					}
				}
			}

			// MSWT START	(MS는 Marquardt Sensitivity를 위미, WT는 W matrix의 transpose를 의미)
			temp = 0;
			for (int m = 0; m < _M - 1; m++) {
				for (int i = 0; i < _S[m]; i++) {
					for (int j = 0; j < _S[m + 1]; j++) {
						for (int k = 0; k < _S[m]; k++) {
							temp += MS_temp[m](i, k) * W[m + 1](j, k); //원래 WT[m+1](k,j) 인데 이건 W[m+1](j,k)와 같음 -> WT가 필요 없음
						}
						MSWT[m](i, j) = temp;
						temp = 0;
					}
				}
			}
			// MSWT END

			// MS START
			for (int m = 2; m <= _M; m++) {
				temp = 0;
				for (int i = 0; i < _S[_M - m]; i++) {
					for (int j = 0; j < _sM; j++) {
						for (int k = 0; k < _S[_M - m + 1]; k++) {
							temp += MSWT[_M - m](i, k) * MS[_M - m + 1](k, j);
						}
						MS[_M - m](i, j) = temp;
						temp = 0;
					}
				}
			}
			// MS END
			// Set Marquardt Sensitivity END

			// Construct Jacobian Matrix START
			for (int j = 0; j < _sM; j++) {
				for (int m = 0; m < _M; m++) {
					for (int i = 0; i < _S[m]; i++) {
						if (m == 0) {
							for (int r = 0; r < _R; r++) {
								J(jrow, jcol) = MS[m](i, j) * train_Pmap(r, q);
								jcol = jcol + 1;
							}
						}
						else {
							for (int r = 0; r < _S[m - 1]; r++) {
								J(jrow, jcol) = MS[m](i, j)*train_A[m - 1](r, q);
								jcol = jcol + 1;
							}
						}
					}
					for (int i = 0; i < _S[m]; i++) {
						J(jrow, jcol) = MS[m](i, j);
						jcol = jcol + 1;
					}
				}
				jrow = jrow + 1;
				jcol = 0;
			}
			// Construct Jacobian Matrix END
		}
		// Set Jacobian Matrix END			

		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < train_size_v; j++) {
				JT(i, j) = J(j, i);
			}
		}

		JTJmu = JT ^ J; // JT matrix * J matrix를 의미하는듯

		for (int i = 0; i < size_x; i++) {
			JTJmu(i, i) += mu;
		}
		// Calculate Delta X END

		invJT = JT;
		try {
			BLAS::LU_solve(JTJmu, invJT);
		}
		catch (int info) {
			if (info) cout << "Singular1" << endl;
		}

		del_x = invJT * V1;
		X2 = X1 - del_x;

		X2Wb(X2, _S, _R, _M, W, b);
		train_A = ANN_train(_train_Q, _R, _M, _S, _Trans, train_Pmap, W, b, train_N);
		FF2 = getMSE_ES(_sM, _train_Q, train_size_v, train_Tmap, train_A[_M - 1], V2);

		count = count + 1;

		fout.open(stepout.c_str(), ios_base::out | ios_base::app);
		fout << "Epoch : " << count << endl;
		fout << "FF1 = " << FF1 << endl;
		fout << "FF2 = " << FF2 << endl;
		fout.close();

		if (count > _max_step) break;

		if (is_nan(FF1) == 1) {
			LMBP_converge = 1;
			break;
		}
		if (is_nan(FF2) == 1) {
			LMBP_converge = 1;
			break;
		}

		if (FF2 >= FF1) {
			do {
				mu = mu * nu;

				if (mu > mu_max) {
					mu = mu_max;
				}

				// muout
				if (_mucheck == 1) {
					fout.open(muout.c_str(), ios_base::out | ios_base::app);
					fout << mu << endl;
					fout.close();
				}

				// Calculate Delta X START

				JTJmu = JT ^ J;

				for (int i = 0; i < size_x; i++) {
					JTJmu(i, i) += mu;
				}
				// Calculate Delta X END

				// Get Inverse Matrix START
				invJT = JT;

				try {
					BLAS::LU_solve(JTJmu, invJT);
				}
				catch (int info) {
					if (info) cout << "Singular2" << endl;
				}

				del_x = invJT * V1;
				X2 = X1 - del_x;

				X2Wb(X2, _S, _R, _M, W, b);
				train_A = ANN_train(_train_Q, _R, _M, _S, _Trans, train_Pmap, W, b, train_N);
				FF2 = getMSE_ES(_sM, _train_Q, train_size_v, train_Tmap, train_A[_M - 1], V2);

				count = count + 1;

				fout.open(stepout.c_str(), ios_base::out | ios_base::app);
				fout << "Epoch : " << count << endl;
				fout << "FF2 = " << FF2 << endl;
				fout.close();

				if (count > _max_step) break;

				if (fabs(FF1 - FF2) < 1e-10) {
					break;
				}

				if (is_nan(FF1) == 1) {
					LMBP_converge = 1;
					break;
				}
				if (is_nan(FF2) == 1) {
					LMBP_converge = 1;
					break;
				}
			} while (FF2 > FF1); // 이 부분 탈출할 수 있는 조건이 필요하지 않을까?
		}
		else {
			mu = mu / nu;

			if (mu < 1e-20) {
				mu = 1e-20;		// MATLAB trainlm.m code에 따름
			}

			if (_mucheck == 1) {
				fout.open(muout.c_str(), ios_base::out | ios_base::app);
				fout << mu << endl;
				fout.close();
			}

			count = count + 1;
			fout.open(stepout.c_str(), ios_base::out | ios_base::app);
			fout << "Epoch : " << count << endl;
			fout.close();

			if (count > _max_step) break;
		}

		for (int i = 0; i < size_x; i++) {
			X1[i] = X2[i];
		}

		// Neural Network using VALIDATION dataset
		val_A = ANN(_val_Q, _R, _M, _S, _Trans, val_Pmap, W, b);
		FF4 = getMSE_ES(_sM, _val_Q, val_size_v, val_Tmap, val_A, val_V);

		if (FF4 >= FF3) {
			check = check + 1;
		}
		else {
			for (int i = 0; i < size_x; i++) {
				X3[i] = X2[i];
			}
			check = 0;
			FF3 = FF4;
		}
		fout.open(stepout.c_str(), ios_base::out | ios_base::app);
		fout << "FF3 = " << FF3 << endl;
		fout << "FF4 = " << FF4 << endl;
		fout.close();

		if (is_nan(FF3) == 1) {
			LMBP_converge = 1;
			break;
		}
		if (is_nan(FF4) == 1) {
			LMBP_converge = 1;
			break;
		}

		// FF4 >= FF3 이면 X3에 X2를 저장 check = check + 1;
		// FF4 < FF3 이면 계속 continue check = 0;
		// check 수가 초기 설정 값보다 커지면 break!! -> END
		// X3를 출력

		// Early Stopping Exit criteria
		if (check > _patience) {
			break;
		}
	} while (count < _max_step);

	// Early Stopping에 의해 끝난 경우(count > 0) 이전에 저장했던 X3를 W와 b에 입력해줘야 한다.
	// max_step에 의해 끝났을 경우 X3이 W, b에 들어가면 안됨.
	if (check > 0) {
		X2Wb(X3, _S, _R, _M, W, b);
	}

	train_A[_M - 1] = ANN(_train_Q, _R, _M, _S, _Trans, train_Pmap, W, b);
	SaveANNoutput("train", train_Tmap, train_A[_M - 1], _sM, _train_Q, _Tdata1, _Tdata2, _yminmax, _FileDir, _normalization);

	val_A = ANN(_val_Q, _R, _M, _S, _Trans, val_Pmap, W, b);
	SaveANNoutput("val", val_Tmap, val_A, _sM, _val_Q, _Tdata1, _Tdata2, _yminmax, _FileDir, _normalization);

	test_A = ANN(_test_Q, _R, _M, _S, _Trans, _test_Pmap, W, b);
	SaveANNoutput("test", _test_Tmap, test_A, _sM, _test_Q, _Tdata1, _Tdata2, _yminmax, _FileDir, _normalization);

	// Performance Evaluation using TEST dataset
	MSE = getMSE_ES(_sM, _test_Q, test_size_v, _test_Tmap, test_A, test_V);

	LM_finish = clock();
	LM_duration = (double)(LM_finish - LM_start) / CLOCKS_PER_SEC;

	fout.open(stepout.c_str(), ios_base::out | ios_base::app);
	fout << endl;
	fout << "MSE = " << MSE << endl;
	fout << "CPU Time[sec] = " << LM_duration << endl;
	fout.close();
	// MSE Calculation by using Test dataset END

	fout.open(MSEout.c_str());
	fout << MSE << endl;
	fout.close();

	// Sensitivity Analysis START
	for (int i = 0; i < _R; i++) {
		for (int j = 0; j < _sM; j++) {
			SenAna(i, j) = 0;	// Initialization for Sensitivity Analysis
		}
	}

	for (int i = 0; i < _R; i++) {
		for (int j = 0; j < _sM; j++) {
			for (int k = 0; k < _S[0]; k++) {
				SenAna(i, j) = SenAna(i, j) + W[0](k, i)*MS[0](k, j);
			}
		}
	}

	string SAout = _FileDir + "\\SenAna.txt";

	fout.open(SAout.c_str());
	for (int i = 0; i < _R; i++) {
		for (int j = 0; j < _sM; j++) {
			fout << SenAna(i, j) << "\t";
		}
		fout << endl;
	}
	fout << endl;
	fout.close();
	// Sensitivity Analysis END

	// Write Weight and Bias START
	string W1out = _FileDir + "\\W1.txt";

	fout.open(W1out.c_str());
	for(int i=0; i<_S[0]; i++){
		for(int j=0; j<_R; j++){
			fout << W[0](i,j) << "\t";
		}
		fout << endl;
	}
	fout << endl;
	fout.close();

	for(int m=1; m<_M; m++){
		string W_count = to_string(m+1);
		string W_name = _FileDir + "\\W" + W_count + ".txt";
		fout.open(W_name.c_str());
		for(int i=0; i<_S[m]; i++){
			for(int j=0; j<_S[m-1]; j++){
				fout << W[m](i,j) << "\t";
			}
			fout << endl;
		}
		fout.close();
	}

	for(int m=0; m<_M; m++){
		string b_count = to_string(m+1);
		string b_name = _FileDir + "\\b" + b_count + ".txt";
		fout.open(b_name.c_str());
		for(int i=0; i<_S[m]; i++){
			fout << b[m](i) << endl;
		}
		fout.close();
	}
	//Write Weight and Bias END

	fout.open(dataout.c_str());
	// WRITE NUMBER of LAYER
	fout << _M << endl; 

	// WRITE TRANSFER FUNCTION INFO
	for(int i=0; i<_M; i++){
		fout << _Trans(i) << "\t";
	}
	fout << endl;

	// WRITE NUMBER of NEURAN of EACH LAYER
	for(int i=0; i<_M; i++){
		fout << _S[i] << "\t";
	}
	fout << endl;

	// WRITE NUMBER of INPUT & TARGET VARIABLES
	fout << _R << "\t" << _sM << endl;

	// WRITE MAX & MIN DATA for MAPMINMAX
	for(int i=0; i<_R; i++){
		fout << _Pdata1[i] << "\t";
	}
	fout << endl;
	for(int i=0; i<_R; i++){
		fout << _Pdata2[i] << "\t";
	}
	fout << endl;
	for(int i=0; i<_sM; i++){
		fout << _Tdata1[i] << "\t";
	}
	fout << endl;
	for(int i=0; i<_sM; i++){
		fout << _Tdata2[i] << "\t";
	}
	fout.close();

	return LMBP_converge;
}