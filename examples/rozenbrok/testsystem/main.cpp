
#include <iostream>
#include <algorithm>
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

	pat.init("x", -100.0, 100.0);
	pat.init("y", -100.0, 100.0);

	double x = pat.get_params<double>("x");
	double y = pat.get_params<double>("y");

    ///////////////////////////////////////////////

    total_err = (1 - x) * (1 - x) + 100.0 * (y - x * x) * (y - x * x);

    ///////////////////////////////////////////////

	cout << "total error is : " << total_err << endl;

	pat.send_result(total_err);

	return 0;
}
