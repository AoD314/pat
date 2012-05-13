
#include <QDebug>

#include "pat/application.hpp"
#include "pat/alg_rnd.hpp"
#include "pat/alg_gradient.hpp"
#include "pat/alg_downhill_simplex.hpp"
#include "pat/alg_bruteforce.hpp"

namespace pat
{

	Application::Application(int argc, char ** argv) : settings(argc, argv), server(settings), alg(0), sp(0)
	{
		connect(&server, SIGNAL(log(QString)), this, SLOT(print_log(QString)));
		connect(&server, SIGNAL(alg(QString)), this, SLOT(algorithm(QString)));
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
			if (alg != 0)
			{
				delete alg;
			}

			if (sp != 0)
			{
				delete sp;
			}

			sp = new SpaceParam();
			alg = new PAT_RND(sp);
		}
	}

}

