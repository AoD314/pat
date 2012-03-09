
#define QWT_DLL

#include <iostream>

#include "mainwindow.hpp"
#include "settingswindow.hpp"
#include "algwindow.hpp"

#include "pat/alg_bruteforce.hpp"
#include "pat/alg_gradient.hpp"
#include "pat/alg_downhill_simplex.hpp"
#include "pat/pat_convert.hpp"

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

		setGeometry(settings->get_geometry_window());
		setWindowTitle("PAT System (GUI)");
		resize(QSize(800, 600));
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

    void MainWindow::add_msg(QString msg)
    {
        msg = QTime::currentTime().toString("hh:mm:ss.zzz") + " : " + msg;
        text_log->append(msg);
        text_log->update();
    }

	void MainWindow::run_app(Point p)
	{
        add_msg(" - - - run application --- run  ");

		space_param->set_current_point(p);
		try
		{
			QProcess * application = new QProcess(this);
			text_log->append(QString("set working directory : " + path));
			application->setWorkingDirectory(path);
			text_log->append(QString("start program : " + program));
			application->start(program, arguments);
			application->waitForFinished();
		}
		catch(...)
		{
            add_msg("Exception with run application : " + program);
		}
        add_msg(" - - - run application --- exit "); text_log->update();
	}

	void MainWindow::new_opt()
	{
		AlgWindow * win = new AlgWindow();
		win->exec();

		if (win->push_create())
		{
            size_t max_iter = 32; //win->max_iter();
			size_t meth = win->method();
            QString app = "/home/aod314/work/pat/examples/build/rozenbrok/testsystem/testsystem"; //win->app();

			text_log->append(QString("Max iteration : " + QString::number(max_iter)));

			if (alg != 0)
				delete alg;

			space_param = new SpaceParam(max_iter);

			switch (meth)
			{
				case 0:
					alg = new pat::PAT_BruteForce(space_param);
					break;

				case 1:
					alg = new pat::PAT_Gradient(space_param);
					break;

				case 2:
					alg = new pat::PAT_Downhill_Simplex(space_param);
					break;

			}

            qRegisterMetaType<Point>("Point");
            qRegisterMetaType<FunctionND>("FunctionND");

			connect(alg, SIGNAL(publish_result(FunctionND)), this, SLOT(publish_result(FunctionND)));
			connect(alg, SIGNAL(run_application(Point)),     this, SLOT(run_app(Point)));

            connect(server, SIGNAL(result(double)),  alg,  SLOT(result(double)));
			connect(server, SIGNAL(get(QString)),    this, SLOT(process_get(QString)));
			connect(server, SIGNAL(init(StrParams)), this, SLOT(process_init(StrParams)));

			connect(this, SIGNAL(send_to_client(QString)), server, SLOT(send_to_client(QString)));


			QStringList folders = app.split("/");
			folders.removeLast();

			path = folders.join("/");
			program = app;

            alg->start();
		}
	}

	void MainWindow::process_init(StrParams params)
	{
        add_msg("process init");
		Range r;
		r.min = params.value_min.toStdString();
		r.max = params.value_max.toStdString();

        space_param->add(params.name.toStdString(), r);
	}

	void MainWindow::process_get(QString name)
	{
        add_msg("process get");
		std::string value = space_param->get(name.toStdString());
		emit send_to_client(value.c_str());
	}

    void MainWindow::publish_result(FunctionND fnc)
	{
        add_msg("publish");
        std::cout << fnc << std::endl;

        add_msg(QString("minimum = ") + QString(to_str(fnc.value).c_str()));
        add_msg("in point : ");
        add_msg(to_str(fnc.point).c_str());
	}

}
