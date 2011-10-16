
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
	}

}
