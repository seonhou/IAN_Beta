#include <iostream>
#include <fstream>
#include <string>
#include <direct.h> // mkdir
#include "linalg/Vector.hpp"
#include "linalg/Matrix.hpp"
#include "LMBP_ES.h"
#include "LMBP_RG.h"
#include "getSize.h"
#include "mapminmax.h"

using namespace std;

// MKL THREAD 설정방법 : 속성 >> 구성속성 >> 디버깅 >> 환경 : MKL_NUM_THREADS=1
// MKL_NUM_THREADS = 1 로 띄워쓰면 안됨!!!!!!

/*
IAN_Beta_1.1에서 업데이트 된 사항

변경전) input 및 target 데이터는 반드시 input.txt 및 target.txt 이어야만 함
변경후) info.log 에 저장되어 있는 string 정보를 이용하여 input 및 target 데이터를 load 함

변경전) 학습에 필요한 정보는 parameters.txt에 저장되어 있음
변경후) 학습에 필요한 정보는 info.log에 저장되어 있음

변경전) MSE.txt로 MSE가 기록됨
변경후) MSE_scaled.txt로 MSE가 기록됨. 왜냐하면 이 코드에서 계산하는 MSE는 mapminmax가 적용된 test data의 MSE임
*/

/*
IAN_Beta_1.2는 수정하다가 버림
IAN_Beta_1.2는 Early Stopping 에서 반복학습 할 때 동일한 test 데이터셋이 사용될 수 있도록 수정하였음
Regularization은 아직 수정하지 않음 -> 수정하다가 적합하지 않은 방향인 것으로 판단되어 중단함
*/

/*
IAN_Beta_1.3에서 업데이트 된 사항(IAN_Beta_1.1 에서 업데이트를 진행함)
변경전) 학습데이터가 주어지면 training 및 validation 그리고 test 데이터가 무작위로 선정되어 학습이 진행됨
변경후) Datadivision은 별도의 exe 파일로 만들어서 학습 이전에 train.txt, test.txt 를 출력하고 이후 IAN에서 train.txt와 test.txt를 입력하여 학습에 사용함
		이렇게 변경한 이유는 신경망 모델을 바꿔가면서 오차를 비교할 때 동일한 test 데이터셋을 사용하고자 할 때를 대비하기 위함임
*/

/*
IAN_Beta_1.4
1) relu activation function이 추가됨
2) Regularization 일반화의 lamda 값을 자동으로 결정하기 위한 베이지안 정규화 알고리즘이 적용됨
*/

void main()
{
	string dirName = "TrainingResult";

	clock_t start, finish;
	double duration = 0;

	// Using File Parameters Setting
	int generalization = 0; // 0: Early Stopping, 1: Regularization
	int repeat_no = 5;
	int max_step = 500;
	int patience = 20;
	int M = 2;
	int all_Q1 = 0;		// sample number of train input data
	int test_Q1 = 0;	// sample number of test input data
	int R = 0;			// number of input parameters
	int all_Q2 = 0;		// sample number of train target data
	int test_Q2 = 0;	// sample number of test target data
	int sM = 0;			// number of target parameters = number of neuron of output layer

	int val_Q = 0;

	ifstream fin;
	fin.open("val_Q.txt");
	fin >> val_Q;
	fin.close();
	fin.clear();

	
	// START Training Information Import
	fin.open("info.log");

	fin >> generalization;	// 0: Early Stopping, 1: Regularization
	fin >> repeat_no;
	fin >> max_step;
	if (generalization == 0) {
		fin >> patience;
	}
	else
	{
		//fin >> lamda;
	}
	fin >> M;	//Number of LAYER

	IntVector Trans(M);
	IntVector S(M);

	for (int ii = 0; ii < M; ii++) {
		fin >> Trans(ii);	//TransferFnc, 1 = logsig, 2 = tansig, 3 = purelin, 4 = relu
	}
	for (int ii = 0; ii < M - 1; ii++) {
		fin >> S[ii];		// Number of Neuron for each layer
	}

	fin.close();
	fin.clear();
	// END Training Information Import


	// START Import hisout.txt
	int mucheck = 0;
	int alphacheck = 0;
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
	fin >> all_Q1;
	fin >> R;

	RealCMatrix all_PT(all_Q1,R);
	RealMatrix all_P(R, all_Q1);
	RealMatrix all_Pmap(R, all_Q1);

	for(int ii=0; ii<all_Q1; ii++){
		for(int jj=0; jj<R; jj++){
			fin >> all_PT[ii][jj];
		}
	}
	fin.close();
	fin.clear();

	for(int ii=0; ii<all_Q1; ii++){
		for(int jj=0; jj<R; jj++){
			all_P(jj,ii) = all_PT[ii][jj];
		}
	}
	// END Import train_input data


	// START Import train_target data
	fin.open("train_target.txt");
	fin >> all_Q2;
	fin >> sM;
	
	RealCMatrix all_TT(all_Q2,sM);
	RealMatrix all_T(sM, all_Q2);
	RealMatrix all_Tmap(sM, all_Q2);

	for(int ii=0; ii<all_Q2; ii++){
		for(int jj=0; jj<sM; jj++){
			fin >> all_TT[ii][jj];
		}
	}
	fin.close();
	fin.clear();

	for(int ii=0; ii<all_Q2; ii++){
		for(int jj=0; jj<sM; jj++){
			all_T(jj,ii) = all_TT[ii][jj];
		}
	}
	// END Import train_target data


	// START Import test_input data
	fin.open("test_input.txt");
	fin >> test_Q1;
	fin >> R;

	RealCMatrix test_PT(test_Q1, R);
	RealMatrix test_P(R, test_Q1);
	RealMatrix test_Pmap(R, test_Q1);

	for (int ii = 0; ii < test_Q1; ii++) {
		for (int jj = 0; jj < R; jj++) {
			fin >> test_PT[ii][jj];
		}
	}
	fin.close();
	fin.clear();

	for (int ii = 0; ii < test_Q1; ii++) {
		for (int jj = 0; jj < R; jj++) {
			test_P(jj, ii) = test_PT[ii][jj];
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
	
	RealVector Pmax(R);
	RealVector Pmin(R);
	RealVector Tmax(sM);
	RealVector Tmin(sM);

	mapminmax(all_P, all_Pmap, Pmax, Pmin);
	mapminmax(all_T, all_Tmap, Tmax, Tmin);

	mapapply(test_P, test_Pmap, Pmax, Pmin);
	mapapply(test_T, test_Tmap, Tmax, Tmin);

	ofstream fout;
	if(all_Q1 != all_Q2){
		fout.open("setting.log");
		fout << "Sample Data Number is not Equal!" << endl;
		fout.close();
		fout << "Sample Data Number is not Equal!" << endl;
	}
	else{
		fout.open("setting.log");

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
				fout << "Transfer Fnc. of Layer " << ii + 1 << " : logsig" << endl;
			}
			else if (Trans(ii) == 2) {
				fout << "Transfer Fnc. of Layer " << ii + 1 << " : tansig" << endl;
			}
			else if (Trans(ii) == 3) {
				fout << "Transfer Fnc. of Layer " << ii + 1 << " : purelin" << endl;
			}
			else {
				fout << "Transfer Fnc. of Layer " << ii + 1 << " : relu" << endl;
			}
		}
		fout << endl;

		for (int ii = 0; ii < M; ii++) {
			fout << "Neuron Number of Layer " << ii + 1 << " : " << S[ii] << endl;
		}
		fout << endl;

		fout << "Number of Training data: " << all_Q1 - val_Q << endl;
		fout << "Number of Validation data: " << val_Q << endl;
		fout << "Number of Test data: " << test_Q1 << endl;

		fout.close();

		int Q = all_Q1;
		int converge_check = 0;

		start = clock();

		int kk = 0;

		//#pragma omp parallel for private(kk) - DO NOT USE OPENMP NOW
		for(kk=0; kk<repeat_no; kk++){	// local minimum check를 위한 반복 학습

			// Make Folder
			string repeat = to_string(kk+1);
			string FdrName = dirName + "_" + repeat;
			int nResult = _mkdir(FdrName.c_str());

			if(nResult == 0){
				if (generalization == 0) {
					do {
						converge_check = LMBP_ES(S, Trans, Pmax, Pmin, Tmax, Tmin, all_Pmap, all_Tmap, test_Pmap, test_Tmap, max_step, patience, M, R, sM, Q, val_Q, test_Q1, FdrName, kk, mucheck);
					} while (converge_check == 1);
				}
				else
				{
					do {
						converge_check = LMBP_RG(S, Trans, Pmax, Pmin, Tmax, Tmin, all_Pmap, all_Tmap, test_Pmap, test_Tmap, max_step, M, R, sM, Q, test_Q1, FdrName, kk, mucheck, alphacheck);
					} while (converge_check == 1);
				}
			}
			else{
				cout << "The FOLDER " << FdrName.c_str() << " is already exist or inaccurate" << endl;
			}
		}

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "TIME[sec] : " << duration << endl;
	}
}