
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdlib.h>

#include "pat/pat.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(int, const char **)
{
	double total_err = 0;

	pat::RND alg;
	alg.set_time(1000);
	alg.set_n(500000);

	alg.init("x", pat::Gen(-8.25, 11.5));
	alg.init("y", pat::Gen(-10.0, 18.0));

	try
	{
		double x = alg.get<double>("x");
		double y = alg.get<double>("y");

		total_err = (1 - x) * (1 - x) + 100.0 * (y - x * x) * (y - x * x);
	}
	catch(...)
	{
		total_err = std::numeric_limits<double>::max();
	}

	///////////////////////////////////////////////

	cout << "total error is : " << total_err << endl;

	pat::System sys;
	sys.send_result(total_err);

	return 0;
}
