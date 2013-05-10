
#ifndef __STATUS_HPP__
#define __STATUS_HPP__

#include "patconfig.hpp"

#include "function_nd.hpp"

namespace pat
{
	class PAT_EXPORTS Status
	{
		public:
			FunctionND current; // point, value
			FunctionND minimum; // point, value
			size_t iter;
			size_t N;
			double cur_eps;
			double eps;
	};
}

#endif

