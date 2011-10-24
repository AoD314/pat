
#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <string>

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include "pat_server.hpp"

#include "pat/pat.hpp"

namespace pat
{

	class MainWindow : public QWidget
	{
		Q_OBJECT

		public:
			MainWindow(QWidget * parent = 0);

		private:
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



		private slots:
			void click_run();
			void next_step(double result);
			void change_path(QString path);
			void finished(int i);
	};
}

#endif
