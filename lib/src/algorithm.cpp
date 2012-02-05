
#include "pat/algorithm.hpp"

namespace pat
{
	PAT_Algorithm::PAT_Algorithm() : params(), iter_number(0), max_iters(10) {}

	void PAT_Algorithm::set_max_iters(size_t max_it)
	{
		max_iters = max_it;
	}

	PAT_Algorithm::~PAT_Algorithm(){}
}
