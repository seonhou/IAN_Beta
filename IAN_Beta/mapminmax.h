#pragma once

void mapminmax(const RealMatrix& X, RealMatrix& Y, RealVector& xmin, RealVector& xmax, RealVector& yminmax);

void mapreverse(const RealMatrix& Y, RealMatrix& Xrev, RealVector& xmin, RealVector& xmax, RealVector& yminmax);

void mapapply(const RealMatrix& X, RealMatrix& Y, RealVector &xmin, RealVector& xmax, RealVector& yminmax);