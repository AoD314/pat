
#ifndef __SETTINGSWINDOW_HPP__
#define __SETTINGSWINDOW_HPP__

#include <QtCore>
#include <QtGui>

#include "settings.hpp"

namespace pat
{

	class SettingsWindow : public QDialog
	{
		Q_OBJECT

		public:
			SettingsWindow(Settings * set, QWidget * parent = 0);

		private:
			QHBoxLayout * box_h_l;
			QHBoxLayout * box_h_b;
			QVBoxLayout * box_v;

			QLabel * lbl_lang;
			QComboBox * list_lang;

			QPushButton * btn_save;
			QPushButton * btn_cancel;

			Settings * settings;

		private slots:
			void save_settings();
			void cancel();
	};

}

#endif
