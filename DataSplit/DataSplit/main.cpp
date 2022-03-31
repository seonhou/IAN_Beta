#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "linalg/Vector.hpp"
#include "linalg/Matrix.hpp"
#include "dataDivision.h"
#include "getSize.h"

using namespace std;

void main()
{
	string inputroute;
	string targetroute;

	double val_ratio = 0;
	double test_ratio = 0;
	int all_Q1 = 0;
	int all_Q2 = 0;

	int R = 0;
	int sM = 0;

	int valuecheck = 0;

	ifstream fin;
	fin.open("splitinfo.log");
	getline(fin, inputroute);
	getline(fin, targetroute);
	fin >> val_ratio;
	fin >> test_ratio;
	fin.close();
	fin.clear();

	fin.open(inputroute);
	all_Q1 = getRow(fin);
	R = getColumn(fin);

	fin.clear();
	fin.seekg(0, ios::beg);

	RealMatrix all_PT(all_Q1, R);
	RealMatrix all_P(R, all_Q1);

	for (int i = 0; i < all_Q1; i++) {
		for (int j = 0; j < R; j++) {
			fin >> all_PT(i,j);
		}
	}
	fin.close();
	fin.clear();

	for (int i = 0; i < all_Q1; i++) {
		for (int j = 0; j < R; j++) {
			all_P(j, i) = all_PT(i,j);
		}
	}

	fin.open(targetroute);
	all_Q2 = getRow(fin);
	sM = getColumn(fin);

	fin.clear();
	fin.seekg(0, ios::beg);

	RealMatrix all_TT(all_Q2, sM);
	RealMatrix all_T(sM, all_Q2);

	for (int i = 0; i < all_Q2; i++) {
		for (int j = 0; j < sM; j++) {
			fin >> all_TT(i, j);
		}
	}
	fin.close();
	fin.clear();

	for (int i = 0; i < all_Q2; i++) {
		for (int j = 0; j < sM; j++) {
			all_T(j, i) = all_TT(i,j);
		}
	}

	int train_Q = 0;
	int val_Q = 0;
	int test_Q  = 0;

	if (all_Q1 != all_Q2) {
		cout << "Number of Data is NOT EQUAL between input and target" << endl;
	}
	else {
		val_Q = all_Q1 * val_ratio;
		test_Q = all_Q1 * test_ratio;
		train_Q = all_Q1 - val_Q - test_Q;

		RealMatrix train_P(R, train_Q);
		RealMatrix train_T(sM, train_Q);
		RealMatrix val_P(R, val_Q);
		RealMatrix val_T(sM, val_Q);
		RealMatrix test_P(R, test_Q);
		RealMatrix test_T(sM, test_Q);

		RealMatrix train_val_P(R, train_Q + val_Q);
		RealMatrix train_val_T(sM, train_Q + val_Q);

		// Test Data Division
		do {
			valuecheck = dataDivision(all_P, all_T, all_Q1, R, sM, train_Q + val_Q, test_Q, train_val_P, train_val_T, test_P, test_T);
		} while (valuecheck == 1);

		do {
			valuecheck = dataDivision(train_val_P, train_val_T, train_Q + val_Q, R, sM, train_Q, val_Q, train_P, train_T, val_P, val_T);
		}while(valuecheck == 1);

		ofstream fout;

		// Write training data
		fout.open("train_input.txt");
		fout << train_Q << "\t" << R << endl;
		for (int i = 0; i < train_Q; i++) {
			for (int j = 0; j < R; j++) {
				fout << setprecision(15) << train_P(j, i) << "\t";
			}
			fout << endl;
		}
		fout.close();

		fout.open("train_target.txt");
		fout << train_Q << "\t" << sM << endl;
		for (int i = 0; i < train_Q; i++) {
			for (int j = 0; j < sM; j++) {
				fout << setprecision(15) << train_T(j, i) << "\t";
			}
			fout << endl;
		}
		fout.close();

		// Write validation data
		fout.open("val_input.txt");
		fout << val_Q << "\t" << R << endl;
		for (int i = 0; i < val_Q; i++) {
			for (int j = 0; j < R; j++) {
				fout << setprecision(15) << val_P(j, i) << "\t";
			}
			fout << endl;
		}
		fout.close();

		fout.open("val_target.txt");
		fout << val_Q << "\t" << sM << endl;
		for (int i = 0; i < val_Q; i++) {
			for (int j = 0; j < sM; j++) {
				fout << setprecision(15) << val_T(j, i) << "\t";
			}
			fout << endl;
		}
		fout.close();

		// Write test data
		fout.open("test_input.txt");
		fout << test_Q << "\t" << R << endl;
		for (int i = 0; i < test_Q; i++) {
			for (int j = 0; j < R; j++) {
				fout << setprecision(15) << test_P(j, i) << "\t";
			}
			fout << endl;
		}
		fout.close();

		fout.open("test_target.txt");
		fout << test_Q << "\t" << sM << endl;
		for (int i = 0; i < test_Q; i++) {
			for (int j = 0; j < sM; j++) {
				fout << setprecision(15) << test_T(j, i) << "\t";
			}
			fout << endl;
		}
		fout.close();

		// fout.open("val_Q.txt");
		// fout << val_Q;
		// fout.close();

	}
}