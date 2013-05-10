
#include <QDebug>

#include "application.hpp"

#include "algorithm_rnd.hpp"
#include "algorithm_gradient.hpp"
#include "algorithm_downhill_simplex.hpp"
#include "algorithm_bruteforce.hpp"

namespace pat
{
	Application::Application(int argc, char ** argv) : settings(argc, argv), server(settings), alg(0), sp(0), app(0)
	{
		connect(&server, SIGNAL(log(QString)), this, SLOT(print_log(QString)));
		connect(&server, SIGNAL(alg(QString)), this, SLOT(algorithm(QString)));
		connect(&server, SIGNAL(params(QString,QString)), this, SLOT(params(QString,QString)));

		connect(&server, SIGNAL(init(QString, Gen)), this, SLOT(init(QString, Gen)));
		connect(&server, SIGNAL(get(QString)),       this, SLOT(get(QString)));
		connect(&server, SIGNAL(result(double)),     this, SLOT(result(double)));

		emit run_app(Point());
	}

    void Application::update_status(const Status & status)
    {
        std::string minimum = to_str(status.minimum);
        emit print_log("progress : [" + QString::number(status.iter) + "/" + QString::number(status.N) + "] ~ " +
                       QString::number(status.iter * 100.0 / static_cast<double>(status.N)) + "%        " +
                       "eps: " + QString::number(status.cur_eps) + " (" + QString::number(status.eps) + ")            " +
                       QString::fromStdString(minimum));
    }

	void Application::params(QString name, QString value)
	{
        //emit print_log("set " + name + " = " + value);

		if (name.compare("n") == 0)
		{
			sp->set_n(from_str<size_t>(value.toStdString()));
		}
	}

	void Application::print_log(QString msg)
	{
		msg = QTime::currentTime().toString("hh:mm:ss.zzz") + "    :  " + msg;
		qDebug() << msg;
	}

	void Application::algorithm(QString name)
	{
        //emit print_log("create algorithm : " + name);

		if (name.compare("rnd") == 0)
		{
			if (alg == 0 && sp == 0)
			{
				sp = new SpaceParam(1024);
				alg = new RND(sp);
				connect(alg, SIGNAL(run_application(Point)),     this, SLOT(run_app(Point)));
				connect(alg, SIGNAL(publish_result(FunctionND)), this, SLOT(publish_result(FunctionND)));
                connect(alg, SIGNAL(update_status(Status)),      this, SLOT(update_status(Status)));
			}
		}
		else if (name.compare("bf") == 0)
		{
			if (alg == 0 && sp == 0)
			{
				sp = new SpaceParam(1024);
				alg = new BruteForce(sp);
				connect(alg, SIGNAL(run_application(Point)),     this, SLOT(run_app(Point)));
				connect(alg, SIGNAL(publish_result(FunctionND)), this, SLOT(publish_result(FunctionND)));
                connect(alg, SIGNAL(update_status(Status)),      this, SLOT(update_status(Status)));
            }
		}
		else if (name.compare("gr") == 0)
		{
			if (alg == 0 && sp == 0)
			{
				sp = new SpaceParam(1024);
				alg = new Gradient(sp);
				connect(alg, SIGNAL(run_application(Point)),     this, SLOT(run_app(Point)));
				connect(alg, SIGNAL(publish_result(FunctionND)), this, SLOT(publish_result(FunctionND)));
                connect(alg, SIGNAL(update_status(Status)),      this, SLOT(update_status(Status)));
            }
		}			
		else if (name.compare("dhs") == 0)
		{
			if (alg == 0 && sp == 0)
			{
				sp = new SpaceParam(1024);
				alg = new Downhill_Simplex(sp);
				connect(alg, SIGNAL(run_application(Point)),     this, SLOT(run_app(Point)));
				connect(alg, SIGNAL(publish_result(FunctionND)), this, SLOT(publish_result(FunctionND)));
                connect(alg, SIGNAL(update_status(Status)),      this, SLOT(update_status(Status)));
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
        //emit print_log("Application::result() = " + QString::number(result));
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
		if (sp != 0)
		{
			sp->set_current_point(p);
		}

		std::string path_to_app = settings.path_to_app();

		if (app != 0)
		{
			app->waitForFinished();
			delete app;
		}

		app = new QProcess;

		connect(app, SIGNAL(finished(int)), this, SLOT(app_finished(int)));
        //emit print_log("run application : " + QString::fromStdString(path_to_app));
		app->start(QString::fromStdString(path_to_app));
	}

	void Application::app_finished(int code)
	{
        //emit print_log("application finished with code : " + QString::number(code));
	}

	void Application::publish_result(FunctionND func)
	{
		emit print_log("\n\nRESULT: F(" + QString::fromStdString(to_str(func.point)) + ") = " + QString::number(func.value.to_float()) + "\n\n");
        //emit quit(0);
        emit qApp->quit();
	}

}

