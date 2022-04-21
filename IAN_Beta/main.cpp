#include <iostream>
#include <fstream>
#include <string>
#include <direct.h> // mkdir
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>

#include "linalg/Vector.hpp"
#include "linalg/Matrix.hpp"
#include "LMBP_ES.h"
#include "LMBP_RG.h"
#include "getSize.h"
#include "mapminmax.h"
#include "standardscaler.h"

using namespace std;

// MKL THREAD 설정방법 : 속성 >> 구성속성 >> 디버깅 >> 환경 : MKL_NUM_THREADS=1
// MKL_NUM_THREADS = 1 로 띄워쓰면 안됨!!!!!!

void main()
{
	string dirName = "TrainingResult";

	clock_t start, finish;
	double duration = 0;

	// Using File Parameters Setting
	int generalization = 0; // 0: Early Stopping, 1: Regularization
	int normalization = 0;	// 0: minmax_scaler, 1: StandardScaler
	int repeat_no = 5;
	int max_step = 500;
	int patience = 20;
	int M = 2;
	int R = 0;			// number of input parameters
	int sM = 0;			// number of target parameters = number of neuron of output layer

	int train_Q1 = 0;	// sample number of train input data
	int val_Q1 = 0;		// sample number of validation input data
	int test_Q1 = 0;	// sample number of test input data
	
	int train_Q2 = 0;	// sample number of train target data
	int val_Q2 = 0;		// sample number of validation target data
	int test_Q2 = 0;	// sample number of test target data

	int alpha_auto = 0;			// 0: use fixed alpha, beta value
								// 1: automatically determine the alpha and beta value								
	double alpha_init = 0.1;	// hyperparameter of L2 regularization
	double beta_init = 0.9;		// hyperparameter of L2 regularization

	RealVector yminmax(2);
	yminmax(0) = 0;		// min value
	yminmax(1) = 1;		// max value

	ifstream fin;
	
	// START Training Information Import
	fin.open("info.log");

	fin >> generalization;	// 0: Early Stopping, 1: L2 Regularization
	fin >> normalization;	// 0: minmax_scaler, 1: StandardScaler

	if (normalization == 0) {
		fin >> yminmax(0);
		fin >> yminmax(1);
	}
	fin >> repeat_no;
	fin >> max_step;
	if (generalization == 0) {
		fin >> patience;
	}
	else
	{
		fin >> alpha_auto;
		fin >> alpha_init;
		fin >> beta_init;
	}
	fin >> M;	//Number of LAYER

	IntVector Trans(M);
	IntVector S(M);
	IntVector kernel_init(M);

	/*
	Trans(i) == 1 : logsig(sigmoid)
	Trans(i) == 2 : tansig(tanh)
	Trans(i) == 3 : purelin(linear, identity)
	Trans(i) == 4 : ReLU
	Trans(i) == 5 : LeakyReLU (alpha = 1)
	Trans(i) == 6 : ELU (alpha = 1)
	Trans(i) == 7 : SELU (alpha=1.67326324, scale=1.05070098)

	kernel_init(i) == 0 : Glorot
	kernel_init(i) == 1 : LuCun
	kernel_init(i) == 2 : He
	*/

	for (int i = 0; i < M; i++) {
		fin >> Trans(i);
	}

	for (int i = 0; i < M; i++) {
		fin >> kernel_init[i];
	}

	for (int i = 0; i < M - 1; i++) {
		fin >> S[i];		// Number of Neuron for each layer
	}

	fin.close();
	fin.clear();
	// END Training Information Import


	// START Import hisout.txt
	int mucheck = 0;
	int alphacheck = 0;			// alpha, beta를 기록할 것인지 여부 확인
	fin.open("hisout.txt");
	fin >> mucheck;
	if (generalization == 1) {
		fin >> alphacheck;
	}
	fin.close();
	fin.clear();
	// END import hisout.txt


	// START Import train_input data
	fin.open("train_input.txt");
	fin >> train_Q1;
	fin >> R;

	RealCMatrix train_PT(train_Q1,R);
	RealMatrix train_P(R, train_Q1);
	RealMatrix train_Pmap(R, train_Q1);

	for (int i = 0; i < train_Q1; i++) {
		for (int j = 0; j < R; j++) {
			fin >> train_PT[i][j];
		}
	}
	fin.close();
	fin.clear();

	for (int i = 0; i < train_Q1; i++) {
		for (int j = 0; j < R; j++) {
			train_P(j, i) = train_PT[i][j];
		}
	}
	// END Import train_input data

	// START Import train_target data
	fin.open("train_target.txt");
	fin >> train_Q2;
	fin >> sM;
	
	RealCMatrix train_TT(train_Q2,sM);
	RealMatrix train_T(sM, train_Q2);
	RealMatrix train_Tmap(sM, train_Q2);

	for (int i = 0; i < train_Q2; i++) {
		for (int j = 0; j < sM; j++) {
			fin >> train_TT[i][j];
		}
	}
	fin.close();
	fin.clear();

	for (int i = 0; i < train_Q2; i++) {
		for (int j = 0; j < sM; j++) {
			train_T(j, i) = train_TT[i][j];
		}
	}
	// END Import train_target data


	// START Import val_input data
	fin.open("val_input.txt");
	fin >> val_Q1;
	fin >> R;

	RealCMatrix val_PT(val_Q1, R);
	RealMatrix val_P(R, val_Q1);
	RealMatrix val_Pmap(R, val_Q1);

	if (val_Q1 != 0) {
		for (int i = 0; i < val_Q1; i++) {
			for (int j = 0; j < R; j++) {
				fin >> val_PT[i][j];
			}
		}
		
		for (int i = 0; i < val_Q1; i++) {
			for (int j = 0; j < R; j++) {
				val_P(j, i) = val_PT[i][j];
			}
		}
	}
	fin.close();
	fin.clear();
	// END Import val_input data

	// START Import val_target data
	fin.open("val_target.txt");
	fin >> val_Q2;
	fin >> sM;

	RealCMatrix val_TT(val_Q2, sM);
	RealMatrix val_T(sM, val_Q2);
	RealMatrix val_Tmap(sM, val_Q2);

	if (val_Q2 != 0) {
		for (int i = 0; i < val_Q2; i++) {
			for (int j = 0; j < sM; j++) {
				fin >> val_TT[i][j];
			}
		}

		for (int i = 0; i < val_Q2; i++) {
			for (int j = 0; j < sM; j++) {
				val_T(j, i) = val_TT[i][j];
			}
		}
	}
	fin.close();
	fin.clear();
	// END Import val_target data


	// START Import test_input data
	fin.open("test_input.txt");
	fin >> test_Q1;
	fin >> R;

	RealCMatrix test_PT(test_Q1, R);
	RealMatrix test_P(R, test_Q1);
	RealMatrix test_Pmap(R, test_Q1);

	for (int i = 0; i < test_Q1; i++) {
		for (int j = 0; j < R; j++) {
			fin >> test_PT[i][j];
		}
	}
	fin.close();
	fin.clear();

	for (int i = 0; i < test_Q1; i++) {
		for (int j = 0; j < R; j++) {
			test_P(j, i) = test_PT[i][j];
		}
	}
	// END Import train_input data


	// START Import test_target data
	fin.open("test_target.txt");
	fin >> test_Q2;
	fin >> sM;

	RealCMatrix test_TT(test_Q2, sM);
	RealMatrix test_T(sM, test_Q2);
	RealMatrix test_Tmap(sM, test_Q2);

	for (int ii = 0; ii < test_Q2; ii++) {
		for (int jj = 0; jj < sM; jj++) {
			fin >> test_TT[ii][jj];
		}
	}
	fin.close();
	fin.clear();

	for (int ii = 0; ii < test_Q2; ii++) {
		for (int jj = 0; jj < sM; jj++) {
			test_T(jj, ii) = test_TT[ii][jj];
		}
	}
	// END Import train_target data


	S[M - 1] = sM;

	RealVector Pdata1(R);	// Pmin or Pmu
	RealVector Pdata2(R);	// Pmax or Psigma
	RealVector Tdata1(sM);	// Tmin or Tmu
	RealVector Tdata2(sM);	// Tmax of Tsigma
	
	if (normalization == 0){

		mapminmax(train_P, train_Pmap, Pdata1, Pdata2, yminmax);
		mapminmax(train_T, train_Tmap, Tdata1, Tdata2, yminmax);

		mapapply(val_P, val_Pmap, Pdata1, Pdata2, yminmax);
		mapapply(val_T, val_Tmap, Tdata1, Tdata2, yminmax);

		mapapply(test_P, test_Pmap, Pdata1, Pdata2, yminmax);
		mapapply(test_T, test_Tmap, Tdata1, Tdata2, yminmax);
	}
	else {

		standardscaler(train_P, train_Pmap, Pdata1, Pdata2);
		standardscaler(train_T, train_Tmap, Tdata1, Tdata2);

		standardapply(val_P, val_Pmap, Pdata1, Pdata2);
		standardapply(val_T, val_Tmap, Tdata1, Tdata2);

		standardapply(test_P, test_Pmap, Pdata1, Pdata2);
		standardapply(test_T, test_Tmap, Tdata1, Tdata2);
	}
	

	ofstream fout;
	if(train_Q1 != train_Q2){
		fout.open("setting.log");
		fout << "Number of Training Sample Data is not Equal!" << endl;
		fout.close();
	}
	else if(val_Q1 != val_Q2){
		fout.open("setting.log");
		fout << "Number of Validation Sample Data is not Equal!" << endl;
		fout.close();
	}
	else if (test_Q1 != test_Q2) {
		fout.open("setting.log");
		fout << "Number of Test Sample Data is not Equal!" << endl;
		fout.close();
	}
	else{
		fout.open("setting.log");

		if (normalization == 0) {
			fout << "Data normalization : minmaxscaler" << endl;
			fout << "Min. value : " << yminmax(0) << endl;
			fout << "Max. value : " << yminmax(1) << endl;
			fout << endl;
		}
		else {
			fout << "Data normalization : StandardScaler" << endl;
			fout << endl;
		}
		fout << "Maximum Epoch : " << max_step << endl;

		if(generalization == 0){
			fout << "Patience : " << patience << endl;
		}
		else {
			//fout << "Lamda : " << lamda << endl;
		}
		
		fout << "Number of Layer : " << M << endl;
		fout << endl;

		for (int ii = 0; ii < M; ii++) {
			if (Trans(ii) == 1) {
				fout << "Activation Fnc. of Layer " << ii + 1 << " : logsig" << endl;
			}
			else if (Trans(ii) == 2) {
				fout << "Activation Fnc. of Layer " << ii + 1 << " : tanh" << endl;
			}
			else if (Trans(ii) == 3) {
				fout << "Activation Fnc. of Layer " << ii + 1 << " : purelin" << endl;
			}
			else if (Trans(ii) == 4) {
				fout << "Activation Fnc. of Layer " << ii + 1 << " : ReLU" << endl;
			}
			else if (Trans(ii) == 5) {
				fout << "Activation Fnc. of Layer " << ii + 1 << " : LeakyReLU" << endl;
			}
			else if (Trans(ii) == 6) {
				fout << "Activation Fnc. of Layer " << ii + 1 << " : ELU" << endl;
			}
			else {
				fout << "Activation Fnc. of Layer " << ii + 1 << " : SELU" << endl;
			}
		}
		fout << endl;

		for (int ii = 0; ii < M; ii++) {
			fout << "Neuron Number of Layer " << ii + 1 << " : " << S[ii] << endl;
		}
		fout << endl;

		fout << "Number of Training data: " << train_Q1 << endl;
		fout << "Number of Validation data: " << val_Q1 << endl;
		fout << "Number of Test data: " << test_Q1 << endl;

		fout.close();
		
		int converge_check = 0;

		start = clock();

		int kk = 0;

		//#pragma omp parallel for private(kk) - DO NOT USE OPENMP NOW
		for (kk = 0; kk < repeat_no; kk++) {	// local minimum check를 위한 반복 학습

			// Make Folder
			string repeat = to_string(kk + 1);
			string FdrName = dirName + "_" + repeat;
			int nResult = _mkdir(FdrName.c_str());

			if (nResult == 0) {
				if (generalization == 0) {
					do {
						converge_check = LMBP_ES(S, Trans, Pdata1, Pdata2, Tdata1, Tdata2, train_Pmap, train_Tmap, val_Pmap, val_Tmap, test_Pmap, test_Tmap, yminmax, max_step, patience, M, R, sM, train_Q1, val_Q1, test_Q1, FdrName, kk, mucheck, normalization, kernel_init);
					} while (converge_check == 1);
				}
				else
				{
					do {
						// all_Pmap, all_Tmap: input and output of training data
						converge_check = LMBP_RG(S, Trans, Pdata1, Pdata2, Tdata1, Tdata2, train_Pmap, train_Tmap, test_Pmap, test_Tmap, yminmax, max_step, M, R, sM, train_Q1, test_Q1, FdrName, kk, mucheck, alphacheck, normalization, kernel_init, alpha_auto, alpha_init, beta_init);
					} while (converge_check == 1);
				}
			}
			else {
				cout << "The FOLDER " << FdrName.c_str() << " is already exist or inaccurate" << endl;
			}
		}

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "TIME[sec] : " << duration << endl;
	}
}