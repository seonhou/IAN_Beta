// Write ANN output and target of TEST dataset START
#pragma once

#include "mapminmax.h"
#include "standardscaler.h"

void SaveANNoutput(string datatype, RealMatrix& __Tmap, RealMatrix& __A, int __sM, int __Q, RealVector& __Tdata1, RealVector& __Tdata2, RealVector& __yminmax, string __FileDir, int __normalization)
{
	string outputname;
	string targetname;

	ofstream fout;
	RealMatrix outmap(__sM,__Q);
	RealMatrix out(__sM,__Q);

	for (int i = 0; i < __sM; i++) {
		for (int j = 0; j < __Q; j++) {
			outmap(i, j) = __A(i, j);
		}
	}

	if (__normalization == 0) {
		mapreverse(outmap, out, __Tdata1, __Tdata2, __yminmax);
	}
	else {
		standardreverse(outmap, out, __Tdata1, __Tdata2);
	}

	outputname = __FileDir + "\\" + datatype + "_output.txt";
	targetname = __FileDir + "\\" + datatype + "_target.txt";

	fout.open(outputname.c_str());
	for (int i = 0; i < __Q; i++) {
		for (int j = 0; j < __sM; j++) {
			fout << out(j, i) << "\t";
		}
		fout << endl;
	}
	fout.close();

	RealMatrix __T(__sM,__Q);
	if (__normalization == 0) {
		mapreverse(__Tmap, __T, __Tdata1, __Tdata2, __yminmax);
	}
	else {
		standardreverse(__Tmap, __T, __Tdata1, __Tdata2);
	}

	fout.open(targetname.c_str());
	for (int i = 0; i < __Q; i++) {
		for (int j = 0; j < __sM; j++) {
			fout << __T(j, i) << "\t";
		}
		fout << endl;
	}
	fout.close();
}