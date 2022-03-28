// Calculate Mean Square Error
// V1은 del_x 계산시 사용되므로 업데이트 되어야 한다.
double getMSE_ES(int __sM, int __Q, int __size_v, RealMatrix& __Tmap, RealMatrix& __A, RealVector& __V)
{	
	double MSE = 0;
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
		MSE = MSE + __V[i] * __V[i];
	}

	MSE = MSE / __size_v / 2;

	return MSE;
}