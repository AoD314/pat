
#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

#include <QtCore>
#include <limits>

#include "patconfig.hpp"

#include "point.hpp"
#include "function_nd.hpp"
#include "space_param.hpp"
#include "status.hpp"

namespace pat
{
	class PAT_EXPORTS Algorithm : public QThread
	{
		Q_OBJECT

		protected:
			FunctionND function(const Point & point);

			volatile mutable int * lock;
			volatile bool is_run;

			SpaceParam * space_param;

			FunctionND function_nd;

			virtual void init();


		public:
			Algorithm(SpaceParam * sp);
			virtual void run() = 0;
			bool isrun();
			virtual ~Algorithm();

		signals:
			void run_application(const Point & p);
			void publish_result(FunctionND res);
			void update_status(Status status);

		public slots:
			void result(double val);
	};

}

#endif

