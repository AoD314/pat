
#include "pat_function.hpp"
#include <cmath>

PAT_Func::PAT_Func(int argc, const char ** argv){}

void PAT_Func::init()
{
	params.add("x", -1, 3, 1);
	params.add("y", -1.0, 2.0, 0.5);
}

double function(double x, double y)
{
	return cos(x) + sin(y) + 13.0 * pow(1.314, -(fabs(x) + fabs(y)));
}

double PAT_Func::run()
{
	double x = params.get<double>("x");
	double y = params.get<double>("y");
	return function(x, y);
}
