
#ifndef __ALGWINDOW_HPP__
#define __ALGWINDOW_HPP__

#include <QtCore>
#include <QtGui>

namespace pat
{

	class AlgWindow : public QDialog
	{
		Q_OBJECT

		public:
			AlgWindow(QWidget * parent = 0);

			int max_iter();
			int method();

		private:

			QVBoxLayout * box_h;
			QHBoxLayout * box_h_b;
			QVBoxLayout * box_v;

			QLabel * lbl_alg;
			QComboBox * list_alg;

			QLabel * lbl_count;
			QSpinBox * spin_count;

			QPushButton * btn_create;
			QPushButton * btn_cancel;

		private slots:
			void cancel();
	};

}

#endif

