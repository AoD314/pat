
#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <string>

#include <QtCore>

#include "pat/algorithm.hpp"
#include "server.hpp"
#include "settings.hpp"

namespace pat
{
	class MainWindow : public QWidget
	{
		Q_OBJECT

		public:
			MainWindow(Settings * set, QWidget * parent = 0);
			~MainWindow();

		private:
			Settings * settings;
			QHBoxLayout * layout_h;
			QVBoxLayout * layout_v;

			QLineEdit   * edit;
			QPushButton * button;
			QTextEdit   * text;

			pat::PAT_Server * server;
			int port;

			std::string path_to_testsystem;

			pat::PAT_Algorithm * alg;
			QString path;
			QString program;
			QStringList arguments;

		signals:
			void add_text(QString msg);


		private slots:
			void click_run();
			void next_step(double result);
			void change_path(QString path);
	};
}

#endif
