
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
		connect(&server, SIGNAL(log(std::string)), this, SLOT(print_log(std::string)));
		connect(&server, SIGNAL(alg(std::string)), this, SLOT(algorithm(std::string)));
		connect(&server, SIGNAL(params(std::string,std::string)), this, SLOT(params(std::string,std::string)));

		connect(&server, SIGNAL(init(std::string, Gen)), this, SLOT(init(std::string, Gen)));
		connect(&server, SIGNAL(get(std::string)),       this, SLOT(get(std::string)));
		connect(&server, SIGNAL(result(double)),         this, SLOT(result(double)));

		path_to_str = QString::fromStdString(settings.path_to_app());;

		emit run_app(Point());
	}

	Application::~Application()
	{
		if (sp != 0)
		{
			delete sp;
		}

		if (alg != 0)
		{
			delete alg;
		}

		if (app != 0)
		{
			app->waitForFinished();
			delete app;
		}
	}

    void Application::update_status(const Status & status)
    {
        emit print_log("progress : [" + to_str(status.iter) + "/" + to_str(status.N) + "] ~ " +
                       to_str(status.iter * 100.0 / static_cast<double>(status.N), 6, 2) + "%        " +
                       "eps: " + to_str(status.cur_eps) + " (" + to_str(status.eps) + ")\n                     current: " + 
					   to_str(status.current) + "      minimum: " + to_str(status.minimum));
    }

	void Application::params(std::string name, std::string value)
	{
		if (name.compare("n") == 0)
		{
			sp->set_n(from_str<size_t>(value));
		}
	}

	void Application::print_log(std::string msg)
	{
		qDebug() << QTime::currentTime().toString("hh:mm:ss.zzz") << "  :  " << msg.c_str();
	}

	void Application::algorithm(std::string name)
	{
		//emit print_log("create algorithm: " + name);

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

	void Application::init(std::string name, Gen gen)
	{
		sp->add(name, gen);
		//emit print_log("init " + name + " : " + to_str<Gen>(gen));
	}

	void Application::get(std::string name)
	{
		server.send_to_client(sp->get(name));
	}

	void Application::result(double result)
	{
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
		//emit print_log("run application");
		
		if (sp != 0)
		{
			sp->set_current_point(p);
		}

		if (app != 0)
		{
			//qDebug() << "finish APP : " << app;
			app->waitForFinished();
			delete app;
			app = 0;
		}

		app = new QProcess(this);

		//qDebug() << "start  APP : " << app;

		connect(app, SIGNAL(finished(int)), this, SLOT(app_finished(int)));
		app->start(path_to_str);
	}

	void Application::app_finished(int code)
	{
		if (code != 0)
		{
			emit print_log("application finished with code : " + to_str(code));
		}
	}

	void Application::publish_result(FunctionND func)
	{
		emit print_log("\n\nRESULT: F(" + to_str(func.point) + ") = " + func.value.str() + "\n\n");
		if (app != 0)
		{
			//qDebug() << "finish APP : " << app;
			app->waitForFinished();
			delete app;
			app = 0;
		}
		emit quit();
	}

}

