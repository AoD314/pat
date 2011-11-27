
#include "pat/gui_mainwindow.hpp"
#include "pat/gui_alg_bruteforce.hpp"

namespace pat
{
	MainWindow::MainWindow(QWidget * parent) : QWidget(parent)
	{
		//C:/work/pat/examples/build/bin/testsystem.exe
		QLineEdit    * edit   = new QLineEdit(QString("/work/projects/pat/pat/examples/build-stereo/bin/testsystem"));
		QPushButton  * button = new QPushButton("RUN");
		QTextEdit    * text   = new QTextEdit(QString("Hello !"));
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

		connect(this, SIGNAL(add_text(QString)), text, SLOT(change_path(QString)));

		connect(server, SIGNAL(log(QString)),  text,  SLOT(append(QString)));
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
		alg->init();

		QObject::connect(server, SIGNAL(get(QString)),     alg,    SLOT(get(QString)));
		QObject::connect(alg,    SIGNAL(send(QString)),    server, SLOT(send_to_value(QString)));

		QObject::connect(alg,    SIGNAL(logging(QString)), this, SLOT());

		QObject::connect(server, SIGNAL(init(QString,QString,QString,QString,QString,QString)), alg, SLOT(init(QString,QString,QString,QString,QString,QString)));

		// set working directory
		program = QString(path_to_testsystem.c_str());
		QStringList folders = program.split("/");
		folders.removeLast();
		path = folders.join("/");

		try
		{
			QProcess * app = new QProcess(this);
			qDebug() << "set working directory : " << path;
			app->setWorkingDirectory(path);		
			qDebug() << "start program  : " << program;
			app->start(program, arguments);
		}
		catch(...)
		{
			qDebug() << " EXCEPTION !!! ";
		}
	}
}
