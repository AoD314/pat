
#ifndef __PAT_ALG_RND_HPP__
#define __PAT_ALG_RND_HPP__

#include <QtCore>

#include "patconfig.hpp"
#include "pat/algorithm.hpp"
#include "pat/function_nd.hpp"
#include "pat/space_param.hpp"

namespace pat
{
	class PAT_EXPORTS PAT_RND : public PAT_Algorithm
	{
		Q_OBJECT

		public:
			PAT_RND(SpaceParam * sp);
			void run();

		private:
			FunctionND minimum;
	};

}

#endif

