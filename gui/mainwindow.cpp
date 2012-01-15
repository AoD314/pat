
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

		alg = 0;

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
		menu_bar.setFixedHeight(25);

		/////////

		text_log = new QTextEdit();
		text_log->setReadOnly(true);

		status = new ParamStatus;


		QSplitter * splitter = new QSplitter(Qt::Horizontal);
		splitter->addWidget(status);
		splitter->addWidget(text_log);

		QVBoxLayout * layout_v = new QVBoxLayout;
		layout_v->addWidget(&menu_bar);
		layout_v->addWidget(splitter);
		setLayout(layout_v);

		port = 13314;
		server = new pat::PAT_Server(port);

		connect(server, SIGNAL(log(QString)),   text_log, SLOT(append(QString)));
		connect(server, SIGNAL(result(double)), this,     SLOT(next_step(double)));

		setGeometry(settings->get_geometry_window());
		setWindowTitle("PAT System (GUI)");
	}

	MainWindow::~MainWindow()
	{
		settings->set_win_size(this);
		settings->SaveSettings();
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

			text_log->append(QString("Max iteration : " + QString::number(max_iter)));

			if (alg != 0)
				delete alg;

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
			connect(alg, SIGNAL(log(QString)),  text_log, SLOT(append(QString)));
			connect(alg, SIGNAL(publish(Params)), status, SLOT(update(Params)));
			connect(alg, SIGNAL(send(QString)),   server, SLOT(send_to_client(QString)));

			connect(server, SIGNAL(init(StrParams)), alg, SLOT(init(StrParams)));
			connect(server, SIGNAL(get(QString)),    alg, SLOT(get(QString)));

			QStringList folders = app.split("/");
			folders.removeLast();
			path = folders.join("/");

			program = app;

			try
			{
				QProcess * application = new QProcess(this);
				text_log->append(QString("set working directory : " + path));
				application->setWorkingDirectory(path);
				text_log->append(QString("start program : " + app));
				application->start(app, arguments);
			}
			catch(...)
			{
				text_log->append("Exception with run application : " + app);
			}

		}
	}

	void MainWindow::next_step(double result)
	{
		text_log->append("MainWindow::next_step(" + QString::number(result) + ")");
		alg->next_step(result);
		if (!alg->is_done())
		{
			text_log->append("\nRun process again : " + program);
			QProcess * app = new QProcess(this);
			app->setWorkingDirectory(path);
			app->start(program, arguments);
		}
		else
		{
			alg->answer();
		}
	}
}
