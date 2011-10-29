
#include "pat/gui_mainwindow.hpp"
#include "pat/gui_alg_bruteforce.hpp"

namespace pat
{
	MainWindow::MainWindow(QWidget * parent) : QWidget(parent)
	{
		QLineEdit    * edit   = new QLineEdit(QString("/work/projects/pat/pat/examples/build-stereo/bin/testsystem"));
		QPushButton  * button = new QPushButton("RUN");
		QTextEdit    * text   = new QTextEdit;
		text->setReadOnly(true);

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
		connect(server, SIGNAL(result(double)), this, SLOT(next_step(double)));


		connect(button, SIGNAL(clicked()), this, SLOT(click_run()));
		connect(edit, SIGNAL(textChanged(QString)), this, SLOT(change_path(QString)));

		this->resize(800, 600);
	}

	void MainWindow::change_path(QString path)
	{
		path_to_testsystem = path.toStdString();
	}

	void MainWindow::next_step(double result)
	{
		alg->next_step(result);
		if (!alg->is_done())
		{
			QProcess * app = new QProcess(this);
			app->setWorkingDirectory(path);
			app->start(program, arguments);
		}
		else
		{
			alg->answer();
		}
	}

	void MainWindow::click_run()
	{
		alg = new pat::PAT_BruteForce();

		connect(server, SIGNAL(get(QString)),  alg,    SLOT(get(QString)));
		//connect(alg,    SIGNAL(info(QString)), text,   SLOT(append(QString)));
		connect(alg,    SIGNAL(send(QString)), server, SLOT(send_to_value(QString)));
		connect(server, SIGNAL(init(QString,QString,QString,QString,QString,QString)), alg, SLOT(init(QString,QString,QString,QString,QString,QString)));

		program = QString(path_to_testsystem.c_str());
		QStringList folders = program.split("/");
		folders.removeLast();
		path = folders.join("/");

		QProcess * app = new QProcess(this);
		app->setWorkingDirectory(path);
		app->start(program, arguments);
	}

	void MainWindow::finished(int i)
	{
		qDebug() << "finish : " << i;
	}
}
