#pragma once

#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>

template <typename T>
string to_string(T value)
{
	ostringstream os;
	os << value;
	return os.str();
}

// Random Generator Function:
int myrandom(int i) { return std::rand() % i; }

int dataDivision(const RealMatrix& _P, RealMatrix& _T, int _Q, int _R, int _sM, int _P1_Q, int _P2_Q, RealMatrix& _P1, RealMatrix& _T1, RealMatrix& _P2, RealMatrix& _T2)
{
	int _valuecheck = 0;

	srand(unsigned(time(0)));
	vector<int> myvector;

	int* value;
	value = new int[_Q];
	for (int i = 0; i < _Q; i++) {
		value[i] = 0;
	}

	// set some values:
	for (int i = 0; i < _Q; ++i) myvector.push_back(i); // 0 ~ (__Q-1)

	// using built-in random generator:
	random_shuffle(myvector.begin(), myvector.end());

	// using myrandom:
	random_shuffle(myvector.begin(), myvector.end(), myrandom);

	// print out content:
	int check = 0;
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
		value[check] = *it;
		check = check + 1;
	}

	int num = 0;

	for (int j = 0; j < _P1_Q; j++) {
		for (int i = 0; i < _R; i++) {
			_P1(i, j) = _P(i, value[num]);
		}
		for (int i = 0; i < _sM; i++) {
			_T1(i, j) = _T(i, value[num]);
		}
		num = num + 1;
	}

	double temp = 0;
	double min_value = 0;
	double max_value = 0;

	for (int i = 0; i < _R; i++) {
		min_value = 0;
		max_value = 0;
		for (int j = 0; j < _P1_Q; j++) {
			temp = _P1(i, j);
			if (temp > max_value) {
				max_value = temp;
			}
			else if (temp < min_value) {
				min_value = temp;
			}
		}
		if (max_value == min_value) {
			_valuecheck = 1;
		}
	}


	for (int j = 0; j < _P2_Q; j++) {
		for (int i = 0; i < _R; i++) {
			_P2(i, j) = _P(i, value[num]);
		}
		for (int i = 0; i < _sM; i++) {
			_T2(i, j) = _T(i, value[num]);
		}
		num = num + 1;
	}

	return _valuecheck;
}