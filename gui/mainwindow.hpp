
#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <QtGui>
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

			QTextEdit   * edit;
			QPushButton * button;
			QTextEdit   * text;

			pat::PAT_Server * server;
			int port;

			pat::PAT_Algorithm * alg;

		private slots:
			void click_run();
			void next_step(double result);
	};
}

#endif
