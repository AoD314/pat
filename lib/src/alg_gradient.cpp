
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
        init();

		size_t N = space_param->max_iter();
		double e = space_param->epsilon();
		size_t iter = 0;

		Point x0 = space_param->get_def();
		Point x1;
		double lamda = 0.5;

		while(true)
		{
			x1 = x0 - lamda * norm(gradient(x0));

			lamda *= 0.35;

			FunctionND f0 = function(x0);
			FunctionND f1 = function(x1);

			double eps = fabs((f1 - f0).to_float());
			if (iter > N || eps < e)
			{
				qDebug() << "iter:" << iter << " eps:" << eps;
				emit publish_result(((f0 < f1) ? f0 : f1));
				break;
			}

			Status st;
			st.cur_eps = eps;
			st.eps = e;
			st.iter = iter;
			st.N = N;
			st.fnc = f1;

			emit update_status(st);

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

	Point PAT_Gradient::norm(const Point & point)
	{
		Point p(point);
		Number n(0);

		for (size_t i = 0; i < p.dim(); ++i)
		{
			if (p[i] > n ||  p[i] < (-n))
			{
				n = p[i];
			}
		}

		for (size_t i = 0; i < p.dim(); ++i)
		{
			p[i] /= n;
		}

		return p;
	}

}



