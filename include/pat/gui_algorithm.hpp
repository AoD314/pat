
#ifndef __PAT_ALGORITHM_HPP__
#define __PAT_ALGORITHM_HPP__

#include <QtCore>
#include "pat/pat_params.hpp"

namespace pat
{	
	class PAT_Algorithm : public QObject
	{
		Q_OBJECT

		protected:
			Params params;

		public:
			virtual void init() = 0;
			virtual void next_step(double value) = 0;
			virtual bool is_done() = 0;

			virtual void answer() = 0;
			virtual void log(QString msg) = 0;

		signals:
			void send(QString val);
			void logging(QString msg);

		public slots:
			virtual void result(double val) = 0;
			virtual void get(QString name) = 0;
			virtual void init(QString name, QString value, QString value_from, QString value_to, QString step, QString type) = 0;
	};

}
	
#endif
	
