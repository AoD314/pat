
#ifndef __PAT_ALGORITHM_HPP__
#define __PAT_ALGORITHM_HPP__

#include <QtCore>

#include <limits>

#include "pat/pat_params.hpp"
#include "pat/pat_strparam.hpp"

namespace pat
{	
	class PAT_Algorithm : public QObject
	{
		Q_OBJECT

		protected:
			Params params;
			virtual void logging(QString msg) = 0;

			size_t iter_number;
			size_t max_iters;

		public:
			PAT_Algorithm();
			virtual void init() = 0;
			virtual void next_step(double value) = 0;
			virtual bool is_done() = 0;

			virtual void answer() = 0;

			virtual void set_max_iters(size_t max_it);

			virtual ~PAT_Algorithm();

		signals:
			void send(QString val);
			void log(QString msg);
			void publish(Params params);

		public slots:
			virtual void result(double val) = 0;
			virtual void get(QString name) = 0;
			virtual void init(StrParams sp) = 0;
	};

}
	
#endif
	
