// Write ANN output and target of TEST dataset START
#pragma once

void SaveANNoutput(string datatype, RealMatrix& __Tmap, RealMatrix& __A, int __sM, int __Q, RealVector& __Tmax, RealVector& __Tmin, string __FileDir)
{
	string outputname;
	string targetname;

	ofstream fout;
	RealMatrix outmap(__sM,__Q);
	RealMatrix out(__sM,__Q);

	for(int i=0; i<__sM; i++){
		for(int j=0; j<__Q; j++){
			outmap(i,j) = __A(i,j);
		}
	}

	mapreverse(outmap, out, __Tmax, __Tmin);

	outputname = __FileDir + "\\" + datatype + "_output.txt";
	targetname = __FileDir + "\\" + datatype + "_target.txt";

	fout.open(outputname.c_str());
	for(int i=0; i<__Q; i++){
		for(int j=0; j<__sM; j++){
			fout << out(j,i) << "\t";
		}
		fout << endl;
	}
	fout.close();

	RealMatrix __T(__sM,__Q);
	mapreverse(__Tmap, __T, __Tmax, __Tmin);

	fout.open(targetname.c_str());
	for(int i=0; i<__Q; i++){
		for(int j=0; j<__sM; j++){
			fout << __T(j,i) << "\t";
		}
		fout << endl;
	}
	fout.close();
}