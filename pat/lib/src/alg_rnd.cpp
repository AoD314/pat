
#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "pat/alg_rnd.hpp"

namespace pat
{
	PAT_RND::PAT_RND(SpaceParam *sp) : PAT_Algorithm(sp) {}

	void PAT_RND::run()
	{
		init();

		QElapsedTimer timer;
		timer.start();

		size_t N = space_param->max_iter();
		size_t iter = 0;

		minimum = function(space_param->get_rnd());

		while (true)
		{
			FunctionND current = function(space_param->get_rnd());
			if (current < minimum)
			{
				minimum = current;
			}

			iter++;

			Status st;
			st.cur_eps = 0.0;
			st.eps = 0;
			st.iter = iter;
			st.N = N;
			st.minimum = minimum;
			st.current = current;
			emit update_status(st);

			if (iter >= N || timer.hasExpired(static_cast<qint64>(space_param->max_time()) * 1000))
			{
				break;
			}
		}

		emit publish_result(minimum);
	}
}
