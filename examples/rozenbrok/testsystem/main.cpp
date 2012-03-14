
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdlib.h>

#include "pat/pat.hpp"

using std::cout;
using std::cin;
using std::endl;
using pat::PAT_System;

int main(int argc, const char ** argv)
{
	double total_err = 0;

	PAT_System pat;

	pat.init("x", -10.5, 7.0);
	pat.init("y", -10.0, 18.0);

	try
	{
		double x = pat.get_params<double>("x");
		double y = pat.get_params<double>("y");

		total_err = (1 - x) * (1 - x) + 100.0 * (y - x * x) * (y - x * x);
		//total_err = x*x + y*y;
	}
	catch(...)
	{
		total_err = std::numeric_limits<double>::max();
	}

	///////////////////////////////////////////////

	cout << "total error is : " << total_err << endl;

	pat.send_result(total_err);

	return 0;
}
