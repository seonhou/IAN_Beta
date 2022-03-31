#include "linalg/Vector.h"
#include "linalg/Matrix.h"

void standardscaler(const RealMatrix& X, RealMatrix& Y, RealVector& mu, RealVector& sigma)
{
	int r = X.rows();		// # of parameters
	int c = X.columns();	// # of samples

	// mu(mean) calculation
	for (int i = 0; i < r; i++) {
		mu(i) = 0;
		for (int j = 0; j < c; j++) {
			mu(i) += X(i, j);
		}
		mu(i) = mu(i) / c;
	}

	// sigma(standard deviation) calculation
	for (int i = 0; i < r; i++) {
		sigma(i) = 0;
		for (int j = 0; j < c; j++) {
			sigma(i) += (X(i, j) - mu(i)) * (X(i, j) - mu(i));
		}
		sigma(i) = sqrt(sigma(i) / c);
	}

	// Scaling
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			Y(i, j) = (X(i, j) - mu(i)) / sigma(i);
		}
	}
}

void standardreverse(const RealMatrix& Y, RealMatrix& Xrev, RealVector& mu, RealVector& sigma)
{
	int r = Y.rows();		// # of parameters
	int c = Y.columns();	// # of samples

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			Xrev(i, j) = sigma(i) * Y(i, j) + mu(i);
		}
	}

}

void standardapply(const RealMatrix& X, RealMatrix& Y, RealVector& mu, RealVector& sigma)
{
	int r = X.rows();		// # of parameters
	int c = X.columns();	// # of samples

	// Scaling
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			Y(i, j) = (X(i, j) - mu(i)) / sigma(i);
		}
	}
}