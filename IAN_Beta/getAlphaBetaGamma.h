#pragma once

double getAlpha(double _gamma, double _MSE2)
{
	double _alpha = .0;
	
	if (_MSE2 == 0) {
		_alpha = 1;
		cout << "MSE2 is zero" << endl;
	}
	else {
		_alpha = _gamma / (2 * _MSE2);
	}
	
	return _alpha;
}

double getBeta(double _gamma, double _MSE1, int __Q, int __sM)
{
	double _beta = .0;

	int N = __Q * __sM;

	if (_MSE1 == 0) {
		_beta = 1;
		cout << "MSE1 is zero" << endl;
	}
	else {
		_beta = (N - _gamma) / (2 * _MSE1);
	}
	
	if (_beta <= 0) {
		_beta = 1;
	}
	
	return _beta;
}

double getGamma(int _size_x, double _alpha, double _beta, RealMatrix& _JTJ)
{
	double _gamma = .0;
	double tr_invH = .0;

	RealMatrix H(_size_x, _size_x);
	RealVector eigvalue(_size_x);
	
	for (int i = 0; i < _size_x; i++) {
		for (int j = 0; j < _size_x; j++) {
			H(i, j) = 2 * _beta * _JTJ(i, j);
		}
	}

	for (int i = 0; i < _size_x; i++) {
		H(i, i) += 2 * _alpha;
	}

	try {
		//BLAS::LU_solve(H, invH);
		//BLAS::LU_inverse(invH);
		BLAS::sym_eigen_solve(H, eigvalue);
	}
	catch (int info) {
		if (info) cout << "Singular_eigen_H" << endl;
	}

	for (int i = 0; i < _size_x; i++) {
		tr_invH += (1 / eigvalue(i));
	}

	_gamma = _size_x - 2 * _alpha * tr_invH;

	return _gamma;
}