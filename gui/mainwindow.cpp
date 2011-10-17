
#include "mainwindow.hpp"

namespace pat
{
	MainWindow::MainWindow(QWidget * parent) : QWidget(parent)
	{
		QTextEdit    * edit   = new QTextEdit("full path to testsystem application");
		QPushButton  * button = new QPushButton("RUN");
		QTextEdit    * text   = new QTextEdit;

		QHBoxLayout * layout_h = new QHBoxLayout;
		layout_h->addWidget(edit);
		layout_h->addWidget(button);

		QVBoxLayout * layout_v = new QVBoxLayout;
		layout_v->addLayout(layout_h);
		layout_v->addWidget(text);

		setLayout(layout_v);

		port = 13314;
		server = new pat::PAT_Server(port);

		connect(server, SIGNAL(log(QString)), text, SLOT(append(QString)));
		connect(server, SIGNAL(next_step(double)), this, SLOT(next_step(double)));

		connect(button, SIGNAL(clicked()), this, SLOT(click_run()));
	}

	void MainWindow::next_step(double result)
	{
		alg->next_step(result);
	}

	void MainWindow::click_run()
	{
		alg = new pat::PAT_BruteForce();
		alg->init();
	}
}
