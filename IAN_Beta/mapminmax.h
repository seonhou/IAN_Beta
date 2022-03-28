#pragma once

void mapminmax(const RealMatrix& X, RealMatrix& Y, RealVector& xmax, RealVector& xmin);

void mapreverse(const RealMatrix& Y, RealMatrix& Xrev, RealVector& xmax, RealVector& xmin);

void mapapply(const RealMatrix& X, RealMatrix& Y, RealVector &xmax, RealVector& xmin);