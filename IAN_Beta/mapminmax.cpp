#include "linalg/Vector.h"
#include "linalg/Matrix.h"

#define ymax 1
#define ymin -1

void mapminmax(const RealMatrix& X, RealMatrix& Y, RealVector& xmax, RealVector& xmin)
{
	int r=X.rows();
	int c=X.columns();
	for(int i=0; i<r; i++){
		xmax[i] = X(i,0);
		xmin[i] = X(i,0);

		for(int j=1; j<c; j++){
			if(X(i,j) > xmax[i]){
				xmax[i] = X(i,j);
			}
		}

		for(int j=1; j<c; j++){
			if(X(i,j) < xmin[i]){
				xmin[i] = X(i,j);
			}
		}
	}

	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			Y(i,j) = (ymax-ymin)*((X(i,j)-xmin[i])/(xmax[i]-xmin[i])) + ymin;
		}
	}
}


void mapreverse(const RealMatrix& Y, RealMatrix& Xrev, RealVector& xmax, RealVector& xmin)
{
	int r=Y.rows();
	int c=Y.columns();
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			Xrev(i,j) = (xmax[i]-xmin[i])*((Y(i,j)-ymin)/(ymax-ymin)) + xmin[i];
		}
	}
}


void mapapply(const RealMatrix& X, RealMatrix& Y, RealVector &xmax, RealVector& xmin)
{
	int r=Y.rows();
	int c=Y.columns();
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			Y(i,j) = (ymax-ymin)*((X(i,j)-xmin[i])/(xmax[i]-xmin[i])) + ymin;
		}
	}
}