
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

		double lamda = 1.0;

		Point x1, x2, x3, x4, x5;

		while(true)
		{
			Point grad = norm(gradient(x0));
			x1 = x0 - 0.025 * lamda * grad;
			x2 = x0 - 0.250 * lamda * grad;
			x3 = x0 - 0.500 * lamda * grad;
			x4 = x0 - 0.850 * lamda * grad;
			x5 = x0 - 1.050 * lamda * grad;

			FunctionND f0 = function(x0);

			FunctionND f1 = function(x1);
			FunctionND f2 = function(x2);
			FunctionND f3 = function(x3);
			FunctionND f4 = function(x4);
			FunctionND f5 = function(x5);

			double koeff;
			FunctionND    m = f1; x0 = x1; koeff = 0.025;
			if (f2 < m)	{ m = f2; x0 = x2; koeff = 0.250; }
			if (f3 < m)	{ m = f3; x0 = x3; koeff = 0.500; }
			if (f4 < m)	{ m = f4; x0 = x4; koeff = 0.850; }
			if (f5 < m)	{ m = f5; x0 = x5; koeff = 1.050; }

			lamda *= koeff;

			double eps = fabs((m - f0).to_float());

			if (iter > N || eps < e)
			{
				//qDebug() << "iter:" << iter << " eps:" << eps << " lamda:" << lamda << " koeff:" << koeff;
				emit publish_result(m);
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
		}
	}

	Point PAT_Gradient::gradient(const Point & point)
	{
		FunctionND fnc = function(point);
		Point grad;
		for (size_t i = 0; i < point.dim(); ++i)
		{
			Point dx = point;
			dx[i] += point.delta(i);
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
			if (abs(p[i]) > n)
			{
				n = abs(p[i]);
			}
		}

		if (n < 1) n = 1;

		for (size_t i = 0; i < p.dim(); ++i)
		{
			p[i] /= n;
		}

		return p;
	}

}



