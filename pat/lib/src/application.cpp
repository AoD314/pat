
#include <QDebug>

#include "pat/application.hpp"
#include "pat/alg_rnd.hpp"
#include "pat/alg_gradient.hpp"
#include "pat/alg_downhill_simplex.hpp"
#include "pat/alg_bruteforce.hpp"

namespace pat
{

	Application::Application(int argc, char ** argv) : settings(argc, argv), server(settings), alg(0), sp(0), app(0)
	{
		connect(&server, SIGNAL(log(QString)), this, SLOT(print_log(QString)));
		connect(&server, SIGNAL(alg(QString)), this, SLOT(algorithm(QString)));

		connect(&server, SIGNAL(init(QString,Gen)), this, SLOT(init(QString, Gen)));
		connect(&server, SIGNAL(get(QString)), this, SLOT(get(QString)));
		connect(&server, SIGNAL(result(double)), this, SLOT(result(double)));

	}

	void Application::print_log(QString msg)
	{
		msg = QTime::currentTime().toString("hh:mm:ss.zzz") + "     :   " + msg;
		qDebug() << msg;
	}

	void Application::algorithm(QString name)
	{
		if (name.compare("RND") == 0)
		{
			if (alg == 0 && sp == 0)
			{
				sp = new SpaceParam(1024);
				alg = new PAT_RND(sp);
				connect(alg, SIGNAL(run_application(Point)), this, SLOT(run_app(Point)));
				connect(alg, SIGNAL(publish_result(FunctionND)), this, SLOT(publish_result(FunctionND)));
			}
		}
	}

	void Application::init(QString name, Gen gen)
	{
		sp->add(name.toStdString(), gen);
	}

	void Application::get(QString name)
	{
		server.send_to_client(QString::fromStdString(sp->get(name.toStdString())));
	}

	void Application::result(double result)
	{
		emit print_log("Application::result() = " + QString::number(result));
		if (alg->isrun())
		{
			alg->result(result);
		}
		else
		{
			alg->run();
		}
	}

	void Application::run_app(const Point & p)
	{
		sp->set_current_point(p);
		std::string path_to_app = settings.path_to_app();

		if (app != 0)
		{
			app->waitForFinished();
			delete app;
		}

		app = new QProcess;

		connect(app, SIGNAL(finished(int)), this, SLOT(app_finished(int)));
		emit print_log("run application : " + QString::fromStdString(path_to_app));
		app->start(QString::fromStdString(path_to_app));
	}

	void Application::app_finished(int code)
	{
		emit print_log("application finished with code :" + QString::number(code));
	}

	void Application::publish_result(FunctionND func)
	{
		emit print_log("\t\tRESULT: F(" + QString::fromStdString(to_str(func.point)) + ") = " + QString::number(func.value.to_float()));
		emit quit(0);
	}

}

