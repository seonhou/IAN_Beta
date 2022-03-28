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

// MKL THREAD ������� : �Ӽ� >> �����Ӽ� >> ����� >> ȯ�� : MKL_NUM_THREADS=1
// MKL_NUM_THREADS = 1 �� ������� �ȵ�!!!!!!

/*
IAN_Beta_1.1���� ������Ʈ �� ����

������) input �� target �����ʹ� �ݵ�� input.txt �� target.txt �̾�߸� ��
������) info.log �� ����Ǿ� �ִ� string ������ �̿��Ͽ� input �� target �����͸� load ��

������) �н��� �ʿ��� ������ parameters.txt�� ����Ǿ� ����
������) �н��� �ʿ��� ������ info.log�� ����Ǿ� ����

������) MSE.txt�� MSE�� ��ϵ�
������) MSE_scaled.txt�� MSE�� ��ϵ�. �ֳ��ϸ� �� �ڵ忡�� ����ϴ� MSE�� mapminmax�� ����� test data�� MSE��
*/

/*
IAN_Beta_1.2�� �����ϴٰ� ����
IAN_Beta_1.2�� Early Stopping ���� �ݺ��н� �� �� ������ test �����ͼ��� ���� �� �ֵ��� �����Ͽ���
Regularization�� ���� �������� ���� -> �����ϴٰ� �������� ���� ������ ������ �ǴܵǾ� �ߴ���
*/

/*
IAN_Beta_1.3���� ������Ʈ �� ����(IAN_Beta_1.1 ���� ������Ʈ�� ������)
������) �н������Ͱ� �־����� training �� validation �׸��� test �����Ͱ� �������� �����Ǿ� �н��� �����
������) Datadivision�� ������ exe ���Ϸ� ���� �н� ������ train.txt, test.txt �� ����ϰ� ���� IAN���� train.txt�� test.txt�� �Է��Ͽ� �н��� �����
		�̷��� ������ ������ �Ű�� ���� �ٲ㰡�鼭 ������ ���� �� ������ test �����ͼ��� ����ϰ��� �� ���� ����ϱ� ������
*/

/*
IAN_Beta_1.4
1) relu activation function�� �߰���
2) Regularization �Ϲ�ȭ�� lamda ���� �ڵ����� �����ϱ� ���� �������� ����ȭ �˰����� �����
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
		for(kk=0; kk<repeat_no; kk++){	// local minimum check�� ���� �ݺ� �н�

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