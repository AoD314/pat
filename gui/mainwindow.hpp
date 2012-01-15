
#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <string>

#include <QtCore>

#include "pat/algorithm.hpp"
#include "server.hpp"
#include "settings.hpp"
#include "paramstatus.hpp"

namespace pat
{
	class MainWindow : public QWidget
	{
		Q_OBJECT

		public:
			MainWindow(Settings * set, QWidget * parent = 0);
			~MainWindow();

		private:

			// --- menu --- //

			QMenuBar menu_bar;

			QMenu * menu_app;
			QMenu * menu_opt;
			QMenu * menu_tools;
			QMenu * menu_help;

			// ------------ //

			Settings * settings;

			// ------------ //

			QHBoxLayout * layout_h;
			QVBoxLayout * layout_v;

			QTextEdit   * text_log;
			ParamStatus * status;

			PAT_Server * server;
			int port;


			PAT_Algorithm * alg;
			QString path_to_testsystem;
			QString path;
			QString program;
			QStringList arguments;

		signals:
			void add_text(QString msg);

		private slots:
			void next_step(double result);
			void about_application();
			void about_qt();
			void settings_window();
			void new_opt();
	};
}

#endif
