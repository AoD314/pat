
#include "pat/params_alg_x.hpp"

namespace pat
{
	void params_x::set_x(std::vector<double> & v)
	{
		x_f = v;
		x_l.clear();
	}

	void params_x::set_x(std::vector<long long int> & v)
	{
		x_l = v;
		x_f.clear();
	}
}
