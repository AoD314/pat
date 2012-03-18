
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

			size_t  max_iter();
			double  eps();
			int     max_time();
			size_t  method();
			QString app();

			bool push_create();

		private:

			QVBoxLayout * box_h;
			QHBoxLayout * box_h_b;
			QVBoxLayout * box_v;
			QHBoxLayout * box_h_l;

			QLabel * lbl_alg;
			QComboBox * list_alg;

			QLabel * lbl_app;
			QLineEdit * text_edit;
			QPushButton * btn_choose;

			QLabel * lbl_count;
			QSpinBox * spin_count;

			QLabel * lbl_time;
			QSpinBox * spin_time;

			QLabel * lbl_eps;
			QDoubleSpinBox * spin_eps;

			QPushButton * btn_create;
			QPushButton * btn_cancel;

			bool is_create;

		private slots:
			void cancel();
			void create();
			void choose_app();

			void update_time(int sec);
	};

}

#endif

