
#ifndef __PARAMS_ALG_X_HPP__
#define __PARAMS_ALG_X_HPP__

#include <vector>

#include "patconfig.hpp"

namespace pat
{
	class PAT_EXPORTS params_x
	{
		protected:
			std::vector<double>        x_f;
			std::vector<long long int> x_l;
		public:
			void set_x(std::vector<double> & v);
			void set_x(std::vector<long long int> & v);
	};
}

#endif

