#pragma once

void standardscaler(const RealMatrix& X, RealMatrix& Y, RealVector& mu, RealVector& sigma);

void standardreverse(const RealMatrix& Y, RealMatrix& Xrev, RealVector& mu, RealVector& sigma);

void standardapply(const RealMatrix& X, RealMatrix& Y, RealVector& mu, RealVector& sigma);