
#ifndef __PAT_ALG_RND_HPP__
#define __PAT_ALG_RND_HPP__

#include <QtCore>

#include "patconfig.hpp"

#include "algorithm.hpp"
#include "function_nd.hpp"
#include "space_param.hpp"

namespace pat
{
	class PAT_EXPORTS RND : public Algorithm
	{
		Q_OBJECT

		public:
			RND(SpaceParam * sp);
			void run();

		private:
			FunctionND minimum;
	};

}

#endif

