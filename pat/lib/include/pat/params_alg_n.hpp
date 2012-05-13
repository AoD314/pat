
#ifndef __PARAMS_ALG_N_HPP__
#define __PARAMS_ALG_N_HPP__

#include "patconfig.hpp"
#include <cstddef>

namespace pat
{
	class PAT_EXPORTS params_n
	{
		protected:
			size_t n;
		public:
			params_n();
			void set_n(size_t n);
	};
}

#endif

