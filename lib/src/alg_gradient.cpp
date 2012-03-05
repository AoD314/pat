
#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "pat/alg_gradient.hpp"
#include "pat/pat_convert.hpp"

namespace pat
{
	PAT_Gradient::PAT_Gradient(SpaceParam * sp) : PAT_Algorithm(sp) {}

	void PAT_Gradient::run()
	{
		size_t N = space_param->max_iter();
		double e = space_param->epsilon();
		size_t iter = 0;

		Point x0 = space_param->get_def();
		Point x1;
		double lamda = 0.5;

		while(true)
		{
			x1 = x0 - lamda * gradient(x0);

			lamda *= 0.5;

			FunctionND f0 = function(x0);
			FunctionND f1 = function(x1);

			if (iter > N || ((f1 - f0) < e))
			{
				if (f0 < f1)
				{
					emit publish_result(f0);
				}
				else
				{
					emit publish_result(f1);
				}
				break;
			}

			iter++;
			x0 = x1;
		}
	}

	Point PAT_Gradient::gradient(const Point & point)
	{
		FunctionND fnc = function(point);
		Point grad;
		for (size_t i = 0; i < point.dim(); ++i)
		{
			Point dx = point + point.delta(i);
			FunctionND nfnc = function(dx);
			grad.add((nfnc.value - fnc.value) / point.delta(i));
		}

		return grad;
	}

}



