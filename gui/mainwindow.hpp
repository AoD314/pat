
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

			QString path;
			QString program;
			QStringList arguments;

			SpaceParam * space_param;

		signals:
			void send_to_client(QString value);

		private slots:
			void publish_result(FunctionND fnc);
			void run_app(Point p);

			void process_get(QString name);
			void process_init(StrParams params);

			void about_application();
			void about_qt();
			void settings_window();
			void new_opt();
	};
}

#endif
