
#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <Qt/QtCore>

#include "patconfig.hpp"
#include "pat/settings.hpp"
#include "pat/server.hpp"
#include "pat/algorithm.hpp"
#include "pat/space_param.hpp"

namespace pat
{
	class PAT_EXPORTS Application : public QObject
	{
		Q_OBJECT

		private:
			Settings settings;
			Server server;
			PAT_Algorithm * alg;
			SpaceParam * sp;
			QProcess * app;

		public:
			Application(int argc, char ** argv);


		signals:
			void quit(int);

		public slots:
			void print_log(QString msg);
			void algorithm(QString name);
			void init(QString name, Gen gen);
			void get(QString name);
			void result(double result);

			void run_app(const Point & p);
			void app_finished(int code);
			void publish_result(FunctionND func);
	};

}


#endif

