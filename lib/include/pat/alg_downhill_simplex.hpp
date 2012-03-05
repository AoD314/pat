
#ifndef __ALG_DOWNHILL_SIMPLEX_HPP__
#define __ALG_DOWNHILL_SIMPLEX_HPP__

#include <QtCore>

#include <vector>

#include "patconfig.hpp"
#include "pat/algorithm.hpp"

namespace pat
{
	class PAT_EXPORTS PAT_Downhill_Simplex : public PAT_Algorithm
	{
		Q_OBJECT

		public:
			PAT_Downhill_Simplex(SpaceParam * sp);
			void run();
	};

}



#endif

