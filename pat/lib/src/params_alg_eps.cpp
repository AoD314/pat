
#include "pat/params_alg_eps.hpp"

namespace pat
{
	params_eps::params_eps()
	{
		eps = 0.000001;
	}

	void params_eps::set_eps(double e)
	{
		eps = e;
	}
}

