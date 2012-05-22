
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

	std::cout << "create alg" << std::endl;
	pat::RND alg;
	alg.set_time(1000);
	alg.set_n(500000);

	std::cout << "init : X" << std::endl;
	alg.init("x", pat::Gen(-8.25, 11.5));
	std::cout << "init : Y" << std::endl;
	alg.init("y", pat::Gen(-10.0, 18.0));

	try
	{
		std::cout << "get : X" << std::endl;
		double x = alg.get<double>("x");
		std::cout << "get : Y" << std::endl;
		double y = alg.get<double>("y");

		std::cout << "calc error" << std::endl;
		total_err = (1 - x) * (1 - x) + 100.0 * (y - x * x) * (y - x * x);
	}
	catch(...)
	{
		total_err = std::numeric_limits<double>::max();
	}

	///////////////////////////////////////////////

	cout << "total error is : " << total_err << endl;

	pat::System sys;
	std::cout << "send result" << std::endl;
	sys.send_result(total_err);

	std::cout << "done." << std::endl;
	return 0;
}
