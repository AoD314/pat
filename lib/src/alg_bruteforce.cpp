
#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "pat/alg_bruteforce.hpp"
#include "pat/pat_convert.hpp"
#include "pat/space_param.hpp"

namespace pat
{
	PAT_BruteForce::PAT_BruteForce(SpaceParam *sp) : PAT_Algorithm(sp) {}

	void PAT_BruteForce::run()
	{
		init();

		size_t N = space_param->max_iter();

		for (size_t i = 0; i < N; i++)
		{
			Point p = space_param->get(i);
			FunctionND cur = function(p);
			if (cur < minimum)
			{
				minimum = cur;
			}

			Status st;
			st.cur_eps = space_param->epsilon();
			st.eps = 0;
			st.iter = i;
			st.N = N;
			st.fnc = cur;
			emit update_status(st);
		}

		emit publish_result(minimum);
	}
}
