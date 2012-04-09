
#include "pat/algorithm.hpp"

namespace pat
{
	PAT_Algorithm::PAT_Algorithm(SpaceParam * sp) : lock(new int(0)), space_param(sp) {}

	FunctionND PAT_Algorithm::function(const Point &point)
	{
		*lock = 1;

		emit run_application(point);

        while (*lock != 0){ }

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

	PAT_Algorithm::~PAT_Algorithm(){}
}
