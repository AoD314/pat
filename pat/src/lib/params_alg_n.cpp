
#include "pat/params_alg_n.hpp"

namespace pat
{
	params_n::params_n()
	{
		this->n = 1000;
	}

	void params_n::set_n(size_t n)
	{
		this->n = n;
	}
}
