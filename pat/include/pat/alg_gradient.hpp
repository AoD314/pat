
#ifndef __ALG_GRADIENT_HPP__
#define __ALG_GRADIENT_HPP__

#include <QtCore>

#include "patconfig.hpp"
#include "pat/algorithm.hpp"

#include <vector>

namespace pat
{
	class PAT_EXPORTS PAT_Gradient : public PAT_Algorithm
	{
		Q_OBJECT

		public:
			PAT_Gradient(SpaceParam * sp);
			void run();

		private:
			FunctionND minimum;
		protected:
			Point gradient(const Point & point);
			Point norm(const Point & point);
	};

}

#endif
