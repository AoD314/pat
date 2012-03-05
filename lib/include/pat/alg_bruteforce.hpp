
#ifndef __PAT_ALG_BRUTEFORCE_HPP__
#define __PAT_ALG_BRUTEFORCE_HPP__

#include <QtCore>

#include "patconfig.hpp"
#include "pat/algorithm.hpp"
#include "pat/function_nd.hpp"
#include "pat/space_param.hpp"

namespace pat
{	
	class PAT_EXPORTS PAT_BruteForce : public PAT_Algorithm
	{
		Q_OBJECT

		public:
			PAT_BruteForce(SpaceParam * sp);
			void run();

		private:
			FunctionND minimum;
	};

}
	
#endif
	
