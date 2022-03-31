#pragma once

double get_activated_value(int index, double x)
{
	double temp = .0;

	if (index == 1) temp = logsig(x);
	else if (index == 2) temp = tansig(x);
	else if (index == 3) temp = purelin(x);
	else if (index == 4) temp = ReLU(x);
	else if (index == 5) temp = LReLU(x);
	else if (index == 6) temp = ELU(x);
	else temp = SELU(x);

	return temp;
}

double get_dactivated_value(int index, double x)
{
	double temp = .0;

	if (index == 1) temp = dlogsig(x);
	else if (index == 2) temp = dtansig(x);
	else if (index == 3) temp = dpurelin(x);
	else if (index == 4) temp = dReLU(x);
	else if (index == 5) temp = dLReLU(x);
	else if (index == 6) temp = dELU(x);
	else temp = dSELU(x);

	return temp;
}