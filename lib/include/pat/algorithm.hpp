
#ifndef __PAT_ALGORITHM_HPP__
#define __PAT_ALGORITHM_HPP__

#include <QtCore>

#include <limits>

#include "patconfig.hpp"

#include "pat/point.hpp"
#include "pat/function_nd.hpp"
#include "pat/space_param.hpp"

namespace pat
{	
    class PAT_EXPORTS PAT_Algorithm : public QThread
	{
		Q_OBJECT

		protected:
			FunctionND function(const Point & point);

			volatile mutable int * lock;

			SpaceParam * space_param;

			FunctionND function_nd;

            virtual void init();


		public:
			PAT_Algorithm(SpaceParam * sp);
			virtual void run() = 0;
			virtual ~PAT_Algorithm();

		signals:
			void run_application(const Point & p);
			void publish_result(FunctionND res);

		public slots:
			void result(double val);
	};

}
	
#endif
	
