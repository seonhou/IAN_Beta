// Transfer Function of Artificial Neural Network //

/*
[rev_-] First Release
[rev_A] relu updated (21.06.08)
*/

#pragma once

#define e 2.718281828459

inline int hardlim(double x)
{
	int y;
	if(x<0)
		y=0;
	else
		y=1;

	return y;
}

inline int hardlims(double x)
{
	int y;
	if(x<0)
		y=-1;
	else
		y=1;

	return y;
}

inline double purelin(double x)
{
	double y;
	y=x;

	return y;
}

inline double dpurelin(double x)
{
	double y;

	y=1;

	return y;
}

inline double satlin(double x)
{
	double y;
	if(x<0)
		y=0;
	else if(x>1)
		y=1;
	else
		y=x;

	return y;
}

inline double satlins(double x)
{
	double y;
	if(x<-1)
		y=-1;
	else if(x>1)
		y=1;
	else
		y=x;

	return y;
}

inline double logsig(double x)
{
	double y;
	y = 1/(1+pow(e,-x));

	return y;
}

inline double dlogsig(double x)
{
	double y;
	y = pow(e,-x)/((1+pow(e,-x))*(1+pow(e,-x)));

	return y;
}

inline double tansig(double x)
{
	double y;
	y = (pow(e,x)-pow(e,-x))/(pow(e,x)+pow(e,-x));

	return y;
}

inline double dtansig(double x)
{
	double y;
	y = 4/((pow(e,x)+pow(e,-x))*(pow(e,x)+pow(e,-x)));

	return y;
}

inline double relu(double x)
{
	double y;
	if(x<0)
		y = 0;
	else
		y = x;

	return y;
}

inline double drelu(double x)
{
	double y;
	if (x <= 0)
		y = 0;
	else
		y = 1;

	return y;
}

inline double softmax(RealVector x)
{

}