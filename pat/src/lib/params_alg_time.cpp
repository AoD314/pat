
#include "pat/params_alg_time.hpp"

namespace pat
{
	params_time::params_time()
	{
		time = 60 * 60;
	}

	void params_time::set_time(size_t t)
	{
		time = t;
	}
}
