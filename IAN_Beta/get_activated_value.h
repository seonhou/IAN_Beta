#pragma once

double get_activated_value(int index, double x)
{
	double _temp = .0;

	if (index == 1) _temp = logsig(x);
	else if (index == 2) _temp = tansig(x);
	else if (index == 3) _temp = purelin(x);
	else if (index == 4) _temp = ReLU(x);
	else if (index == 5) _temp = LReLU(x);
	else if (index == 6) _temp = ELU(x);
	else _temp = SELU(x);

	return _temp;
}

double get_dactivated_value(int index, double x)
{
	double _temp = .0;

	if (index == 1) _temp = dlogsig(x);
	else if (index == 2) _temp = dtansig(x);
	else if (index == 3) _temp = dpurelin(x);
	else if (index == 4) _temp = dReLU(x);
	else if (index == 5) _temp = dLReLU(x);
	else if (index == 6) _temp = dELU(x);
	else _temp = dSELU(x);

	return _temp;
}