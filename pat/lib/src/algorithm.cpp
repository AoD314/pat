
#include "pat/algorithm.hpp"

namespace pat
{
	PAT_Algorithm::PAT_Algorithm(SpaceParam * sp) : lock(new int(0)), is_run(false), space_param(sp) {}

	FunctionND PAT_Algorithm::function(const Point &point)
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

	void PAT_Algorithm::init()
	{
		function(Point());
	}

	void PAT_Algorithm::result(double val)
	{
		function_nd.value = val;
		*lock = 0;
	}

	bool PAT_Algorithm::isrun()
	{
		return is_run;
	}

	PAT_Algorithm::~PAT_Algorithm(){}
}
