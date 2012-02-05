
#ifndef __PARAMSTATUS_HPP__
#define __PARAMSTATUS_HPP__

#include <QtCore>
#include <QtGui>

#include <stdint.h>

#include "pat/pat_params.hpp"

namespace pat
{
	class ParamStatus : public QWidget
	{
			Q_OBJECT

		public:
			ParamStatus(QWidget * parent = 0);

		private:
			Params p;
			int64_t iter;
			int64_t points_in_dims;

			QLabel * lbl_points;
			QLabel * lbl_result;
			QLabel * lbl_iter;

			QTableWidget * table;
			QProgressBar * progress;

			QGridLayout * lay;

		public slots:
			void update(Params params);
	};
}

#endif
