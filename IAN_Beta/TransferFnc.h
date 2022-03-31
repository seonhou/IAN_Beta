// Transfer Function of Artificial Neural Network //

/*
[rev_-] First Release
[rev_A] ReLU updated (21.06.08)
[rev_B] LeakyReLU, ELU, SELU updated (22.03.29)
*/

#pragma once

#define e 2.718281828459

inline int hardlim(double x)
{
	int y;
	if (x < 0)
		y = 0;
	else
		y = 1;

	return y;
}

inline int hardlims(double x)
{
	int y;
	if (x < 0)
		y = -1;
	else
		y = 1;

	return y;
}

inline double purelin(double x)
{
	double y;
	y = x;

	return y;
}

inline double dpurelin(double x)
{
	double y;

	y = 1;

	return y;
}

inline double satlin(double x)
{
	double y;
	if (x < 0)
		y = 0;
	else if (x > 1)
		y = 1;
	else
		y = x;

	return y;
}

inline double satlins(double x)
{
	double y;
	if (x < -1)
		y = -1;
	else if (x > 1)
		y = 1;
	else
		y = x;

	return y;
}

// logsig(sigmoid)
inline double logsig(double x)
{
	double y;
	y = 1 / (1 + pow(e, -x));

	return y;
}

inline double dlogsig(double x)
{
	double y;
	y = pow(e, -x) / ((1 + pow(e, -x)) * (1 + pow(e, -x)));

	return y;
}

// tansig(tanh)
inline double tansig(double x)
{
	double y;
	y = (pow(e, x) - pow(e, -x)) / (pow(e, x) + pow(e, -x));

	return y;
}

inline double dtansig(double x)
{
	double y;
	y = 4 / ((pow(e, x) + pow(e, -x)) * (pow(e, x) + pow(e, -x)));

	return y;
}

// ReLU
inline double ReLU(double x)
{
	double y;
	if(x<0)
		y = 0;
	else
		y = x;

	return y;
}

inline double dReLU(double x)
{
	double y;
	if (x <= 0)
		y = 0;
	else
		y = 1;

	return y;
}


// LeakyReLU
inline double LReLU(double x)
{
	double y;
	double alpha = 0.01;
	if (x <= 0)
		y = alpha * x;
	else
		y = x;

	return y;
}

inline double dLReLU(double x)
{
	double y;
	double alpha = 0.01;
	if (x <= 0)
		y = alpha;
	else
		y = 1;

	return y;
}


// ELU
inline double ELU(double x)
{
	double y;
	double alpha = 1.0;
	if (x < 0)
		y = alpha * (pow(e, x) - 1);
	else
		y = x;

	return y;
}

inline double dELU(double x)
{
	double y;
	double alpha = 1.0;

	if (x < 0)
		y = alpha * pow(e, x);
	else
		y = 1;

	return y;
}

// SELU
// The alpha and scale values are determined by keras documentation
// https://www.tensorflow.org/api_docs/python/tf/keras/activations/selu
inline double SELU(double x)
{
	double y;
	double alpha = 1.67326324;
	double scale = 1.05070098;

	if (x < 0)
		y = scale * alpha * (pow(e, x) - 1);
	else
		y = scale * x;
		

	return y;
}

inline double dSELU(double x)
{
	double y;
	double alpha = 1.67326324;
	double scale = 1.05070098;

	if (x < 0)
		y = scale * alpha * pow(e, x);
	else
		y = scale;

	return y;
}


inline double softmax(RealVector x)
{

}