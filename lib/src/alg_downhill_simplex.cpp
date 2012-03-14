
#include "pat/alg_downhill_simplex.hpp"

#include <iostream>

namespace pat
{
	PAT_Downhill_Simplex::PAT_Downhill_Simplex(SpaceParam *sp) : PAT_Algorithm(sp), alpha(1.0), beta(0.5), gamma(2.0) {} // central symmetry (alpha = 1)

	void PAT_Downhill_Simplex::run()
	{
		init();

		size_t N = space_param->max_iter();
		double e = space_param->epsilon();
		size_t iter = 0;

		Point x0 = space_param->get_simplex(0);
		size_t n = x0.dim();

		std::vector<FunctionND> v_fnc;
		v_fnc.push_back(function(x0));

		// simplex
		for (size_t i = 0; i < n; ++i)
		{
			v_fnc.push_back(function(space_param->get_simplex(i+1)));
		}

		// start alg
		while(true)
		{
			sort(v_fnc);

			FunctionND f_h, f_g, f_l;
			f_h = v_fnc.at(0);
			f_g = v_fnc.at(1);
			f_l = v_fnc.at(v_fnc.size() - 1);

			// step 3
			Point x_c = v_fnc.at(1).point;

			for (size_t i = 2; i < n+1; ++i)
			{
				x_c += v_fnc.at(i).point;
			}

			x_c /= Number(n);

			// step 4
			Point x_r = (1.0 + alpha) * x_c - alpha * (f_h.point);
			FunctionND f_r = function(x_r);


			// step 5
			if (f_r < f_l)
			{
				Point x_e = (1.0 - gamma) * x_c + gamma * x_r;
				FunctionND f_e = function(x_e);

				if (f_e < f_l)
				{
					v_fnc.at(0) = f_e;
				}
				else if (f_l < f_e)
				{
					v_fnc.at(0) = f_r;
				}
			}
			else
			{
				if (f_l < f_r && f_r < f_g)
				{
					v_fnc.at(0) = f_r;
				}
				else
				{
					if (f_g < f_r && f_r < f_h)
					{
						FunctionND tmp = f_h;
						f_h = f_r;
						f_r = tmp;
					}

					// step 6
					Point x_s = (beta) * f_h.point + (1.0 - beta) * x_c;
					FunctionND f_s = function(x_s);

					// step 7
					if (f_s < f_h)
					{
						v_fnc.at(0) = f_s;
					}
					//step 8
					else if (f_s > f_h)
					{
						for (size_t i = 0; i < n; ++i)
						{
							v_fnc.at(i).point = f_l.point + (v_fnc.at(i).point - f_l.point) / 2;
						}
					}
				}
			}

			x_c = v_fnc.at(1).point;
			for (size_t i = 2; i < n+1; ++i)
			{
				x_c += v_fnc.at(i).point;
			}
			x_c /= Number(n);
			FunctionND f_c = function(x_c);

			double eps = abs(f_c - v_fnc.at(n)).to_float();

			// step 9
			// ...
			if (iter >= N || eps < e)
			{
				break;
			}

			Status st;
			st.cur_eps = 0.0;
			st.eps = 0.0;
			st.iter = iter;
			st.N = N;
			st.fnc = f_c;

			emit update_status(st);

			iter++;
		}

		Point x_c = v_fnc.at(1).point;
		for (size_t i = 2; i < n+1; ++i)
		{
			x_c += v_fnc.at(i).point;
		}
		x_c /= Number(n);
		FunctionND result = function(x_c);

		emit publish_result(result);
	}

}

