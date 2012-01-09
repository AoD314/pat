
#include "mainwindow.hpp"
#include "settingswindow.hpp"
#include "algwindow.hpp"

#include "pat/alg_bruteforce.hpp"
#include "pat/alg_gradient.hpp"

namespace pat
{
	MainWindow::MainWindow(Settings * set, QWidget * parent) : QWidget(parent)
	{
		settings = set;

		QTranslator trans;
		QString l = settings->language();
		QString pl = settings->get_path_to_language();
		trans.load(l + ".qm", pl);
		qApp->installTranslator(&trans);

		QTextEdit * text = new QTextEdit();
		text->setReadOnly(true);


		// MENU //

		menu_app = new QMenu(tr("Application"));
		menu_app->addAction(tr("Exit"), this, SLOT(close()));

		menu_opt = new QMenu(tr("Optimization"));
		menu_opt->addAction(tr("New"), this, SLOT(new_opt()));
		menu_opt->addAction(tr("Open"));
		menu_opt->addAction(tr("Save"));
		menu_opt->addSeparator();
		menu_opt->addAction(tr("Run/Stop"));

		menu_tools = new QMenu(tr("Tools"));
		menu_tools->addAction(tr("Settings"), this, SLOT(settings_window()));

		menu_help = new QMenu(tr("Help"));
		menu_help->addAction(tr("About Application"), this, SLOT(about_application()));
		menu_help->addSeparator();
		menu_help->addAction(tr("About Qt"), this, SLOT(about_qt()));

		// Menu Bar

		menu_bar.addMenu(menu_app);
		menu_bar.addMenu(menu_opt);
		menu_bar.addMenu(menu_tools);
		menu_bar.addMenu(menu_help);

		/////////

		QVBoxLayout * layout_v = new QVBoxLayout;
		layout_v->addWidget(&menu_bar);
		//layout_v->addWidget(text);

		setLayout(layout_v);

		port = 13314;
		server = new pat::PAT_Server(port);

		connect(server, SIGNAL(log(QString)),  text,  SLOT(append(QString)));
		connect(server, SIGNAL(result(double)), this, SLOT(next_step(double)));		

		setGeometry(settings->get_geometry_window());
		setWindowTitle("PAT System (GUI)");
	}

	void MainWindow::about_application()
	{
		QMessageBox::about(0, tr("About Application"), tr(" PAT System v0.0.1 "));
	}

	void MainWindow::about_qt()
	{
		QMessageBox::aboutQt(0);
	}

	void MainWindow::settings_window()
	{
		SettingsWindow * win = new SettingsWindow(settings);
		win->exec();
	}

	void MainWindow::new_opt()
	{
		AlgWindow * win = new AlgWindow();
		win->exec();

		if (win->push_create())
		{
			int max_iter = win->max_iter();
			int meth = win->method();
			QString app = win->app();

			switch (meth)
			{
				case 0:
					alg = new pat::PAT_BruteForce();
					break;

				case 1:
					alg = new pat::PAT_Gradient();
					break;
			}

			alg->init();

		}

	}

	MainWindow::~MainWindow()
	{
		settings->set_win_size(this);
		settings->SaveSettings();
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
		//;

		QObject::connect(server, SIGNAL(get(QString)),     alg,    SLOT(get(QString)));
		QObject::connect(alg,    SIGNAL(send(QString)),    server, SLOT(send_to_value(QString)));

		QObject::connect(alg,    SIGNAL(logging(QString)), this, SLOT());

		QObject::connect(server, SIGNAL(init(QString,QString,QString,QString,QString,QString)), alg, SLOT(init(QString,QString,QString,QString,QString,QString)));

		// set working directory
		QStringList folders = path_to_testsystem.split("/");
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
