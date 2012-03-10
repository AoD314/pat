
#ifndef __STATUS_HPP__
#define __STATUS_HPP__

#include "pat/function_nd.hpp"

namespace pat
{
	class Status
	{
		public:
			FunctionND fnc; // point, value
			size_t iter;
			size_t N;
			double cur_eps;
			double eps;

	};

}

#endif

