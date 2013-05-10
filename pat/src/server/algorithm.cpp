
#include "algorithm.hpp"

namespace pat
{
	Algorithm::Algorithm(SpaceParam * sp) : lock(new int(0)), is_run(false), space_param(sp) {}

	FunctionND Algorithm::function(const Point &point)
	{
		*lock = 1;

		emit run_application(point);

		QEventLoop loop;
		while (*lock != 0)
		{
			loop.processEvents();
		}

		function_nd.point = point;
		return function_nd;
	}

	void Algorithm::init()
	{
		function(Point());
	}

	void Algorithm::result(double val)
	{
		function_nd.value = val;
		*lock = 0;
	}

	bool Algorithm::isrun()
	{
		return is_run;
	}

	Algorithm::~Algorithm(){}
}
