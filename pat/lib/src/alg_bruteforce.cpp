
#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "pat/alg_bruteforce.hpp"
#include "pat/convert.hpp"
#include "pat/space_param.hpp"

namespace pat
{
	PAT_BruteForce::PAT_BruteForce(SpaceParam *sp) : PAT_Algorithm(sp) {}

	void PAT_BruteForce::run()
	{
		init();

		QElapsedTimer timer;
		timer.start();

		size_t N = space_param->max_iter();

		minimum = function(space_param->get(0));

		for (size_t i = 1; (i < N) && (!timer.hasExpired(static_cast<qint64>(space_param->max_time()) * 1000)); ++i)
		{
			FunctionND current = function(space_param->get(i));
			if (current < minimum)
			{
				minimum = current;
			}

			Status st;
			st.cur_eps = 0.0;
			st.eps = 0;
			st.iter = i + 1;
			st.N = N;
			st.minimum = minimum;
			st.current = current;
			emit update_status(st);
		}

		emit publish_result(minimum);
	}
}
