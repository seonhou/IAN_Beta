// Calculate Mean Square Error
// V1은 del_x 계산시 사용되므로 업데이트 되어야 한다.
double getMSE_RG(double& _MSE1, double& _MSE2, int __sM, int __Q, int __size_v, int __size_x, double _alpha, double _beta, RealMatrix& __Tmap, RealMatrix& __A, RealVector& __V, RealVector& __X)
{	
	double _MSE = 0;

	RealMatrix E(__sM,__Q);

	int count_v = 0;
	for(int i=0; i<__sM; i++){
		for(int q=0; q<__Q; q++){
			E(i,q) = __Tmap(i,q) - __A(i,q);
		}
	}

	for(int i=0; i<__Q; i++){
		for(int j=0; j<__sM; j++){
			__V[count_v] = E(j,i);
			count_v = count_v + 1;
		}
	}

	for(int i=0; i<__size_v; i++){
		_MSE1 = _MSE1 + __V[i] * __V[i];
	}

	_MSE1 = _beta * _MSE1;
	//_MSE1 = _MSE1 / __size_v / 2;

	for (int i = 0; i < __size_x; i++) {
		_MSE2 = _MSE2 + (__X(i) * __X(i));
	}
	_MSE2 = _alpha * _MSE2;
	//_MSE2 = __lamda * _MSE2 / 2;

	_MSE = _MSE1 + _MSE2;

	return _MSE;
}

double getMSE1_RG(int __sM, int __Q, int __size_v, RealMatrix& __Tmap, RealMatrix& __A, RealVector& __V)
{
	double _MSE1 = 0;

	RealMatrix E(__sM, __Q);

	int count_v = 0;
	for (int i = 0; i < __sM; i++) {
		for (int q = 0; q < __Q; q++) {
			E(i, q) = __Tmap(i, q) - __A(i, q);
		}
	}

	for (int i = 0; i < __Q; i++) {
		for (int j = 0; j < __sM; j++) {
			__V[count_v] = E(j, i);
			count_v = count_v + 1;
		}
	}

	for (int i = 0; i < __size_v; i++) {
		_MSE1 = _MSE1 + __V[i] * __V[i];
	}

	return _MSE1;
}

double getMSE2_RG(int __size_x, RealVector& __X)
{
	double _MSE2 = 0;

	for (int i = 0; i < __size_x; i++) {
		_MSE2 += (__X(i) * __X(i));
	}

	return _MSE2;
}