
#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <QtCore/QtCore>

#include "patconfig.hpp"
#include "settings.hpp"

#include "server.hpp"
#include "algorithm.hpp"
#include "space_param.hpp"
#include "status.hpp"

namespace pat
{
	class PAT_EXPORTS Application : public QObject
	{
		Q_OBJECT

		private:
			Settings settings;
			Server server;
			Algorithm * alg;
			SpaceParam * sp;
			QProcess * app;

		public:
			Application(int argc, char ** argv);


		signals:
			void quit(int);

		public slots:
			void print_log(QString msg);
			void params(QString name, QString value);
			void algorithm(QString name);
			void init(QString name, Gen gen);
			void get(QString name);
			void result(double result);

            void update_status(const Status & status);

			void run_app(const Point & p);
			void app_finished(int code);
			void publish_result(FunctionND func);
	};

}


#endif

