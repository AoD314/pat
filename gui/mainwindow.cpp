
#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget * parent) : QWidget(parent)
{
	QTextEdit    * edit   = new QTextEdit("full path to testsystem application");
	QPushButton  * button = new QPushButton("RUN");
	QTextBrowser * text   = new QTextBrowser;

	QHBoxLayout * layout_h = new QHBoxLayout;
	layout_h->addWidget(edit);
	layout_h->addWidget(button);

	QVBoxLayout * layout_v = new QVBoxLayout;
	layout_v->addLayout(layout_h);
	layout_v->addWidget(text);

	setLayout(layout_v);
}