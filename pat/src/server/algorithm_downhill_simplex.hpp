
#ifndef __ALG_DOWNHILL_SIMPLEX_HPP__
#define __ALG_DOWNHILL_SIMPLEX_HPP__

#include <QtCore>

#include <vector>

#include "patconfig.hpp"

#include "algorithm.hpp"

namespace pat
{
	class PAT_EXPORTS Downhill_Simplex : public Algorithm
	{
		Q_OBJECT

		public:
			Downhill_Simplex(SpaceParam * sp);
			void run();

		private:
			double alpha;
			double beta;
			double gamma;

			FunctionND minimum;
	};

}



#endif

