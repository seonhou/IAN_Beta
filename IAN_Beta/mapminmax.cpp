#include "linalg/Vector.h"
#include "linalg/Matrix.h"

void mapminmax(const RealMatrix& X, RealMatrix& Y, RealVector& xmin, RealVector& xmax, RealVector& yminmax)
{
	// int r = X.rows();
	// int c = X.columns();

	for (int i = 0; i < X.rows(); i++) {
		xmin[i] = X(i, 0);
		xmax[i] = X(i, 0);

		for (int j = 1; j < X.columns(); j++) {
			if(X(i, j) > xmax[i]){
				xmax[i] = X(i, j);
			}
		}

		for (int j = 1; j < X.columns(); j++) {
			if(X(i, j) < xmin[i]){
				xmin[i] = X(i, j);
			}
		}
	}

	for (int i = 0; i < X.rows(); i++) {
		for (int j = 0; j < X.columns(); j++) {
			Y(i, j) = (yminmax(1) - yminmax(0)) * ((X(i, j) - xmin[i]) / (xmax[i] - xmin[i])) + yminmax(0);
		}
	}
}

void mapreverse(const RealMatrix& Y, RealMatrix& Xrev, RealVector& xmin, RealVector& xmax, RealVector& yminmax)
{
	// int r = Y.rows();
	// int c = Y.columns();

	for (int i = 0; i < Y.rows(); i++) {
		for (int j = 0; j < Y.columns(); j++) {
			Xrev(i, j) = (xmax[i] - xmin[i]) * ((Y(i, j) - yminmax(0)) / (yminmax(1) - yminmax(0))) + xmin[i];
		}
	}
}

void mapapply(const RealMatrix& X, RealMatrix& Y, RealVector &xmin, RealVector& xmax, RealVector& yminmax)
{
	// int r = Y.rows();
	// int c = Y.columns();

	for (int i = 0; i < Y.rows(); i++) {
		for (int j = 0; j < Y.columns(); j++) {
			Y(i, j) = (yminmax(1) - yminmax(0)) * ((X(i, j) - xmin[i]) / (xmax[i] - xmin[i])) + yminmax(0);
		}
	}
}