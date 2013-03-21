
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdlib.h>

#include <pat/pat.hpp>

using std::cout;
using std::cin;
using std::endl;

int main(int, const char **)
{
	double total_err = 0;

	std::cout << "create alg" << std::endl;
	pat::Alg alg(PAT_ALG_RND);
	alg.set_time(1000);
	alg.set_n(500000);

	//std::cout << "init : X" << std::endl;
	alg.init("x", pat::Gen(-8.25, 11.5));
	//std::cout << "init : Y" << std::endl;
	alg.init("y", pat::Gen(-10.0, 18.0));

	try
	{
		std::cout << "get : X = ";
		double x = alg.get<double>("x");
		std::cout << x << std::endl;

		std::cout << "get : Y = ";
		double y = alg.get<double>("y");
		std::cout << y << std::endl;

		std::cout << "calc error = ";
		total_err = (1 - x) * (1 - x) + 100.0 * (y - x * x) * (y - x * x);
		std::cout << total_err << std::endl;
	}
	catch(...)
	{
		total_err = std::numeric_limits<double>::max();
	}

	///////////////////////////////////////////////

	pat::System sys;
	std::cout << "send result ... ";
	sys.send_result(total_err);

	std::cout << "done.\n" << std::endl;
	return 0;
}
