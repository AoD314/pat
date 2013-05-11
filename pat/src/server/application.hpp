
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
			QString path_to_str;
			QMutex mutex;
				 

		public:
			Application(int argc, char ** argv);
			~Application();


		signals:
			void quit();

		public slots:
			void print_log(std::string msg);
			void params(std::string name, std::string value);
			void algorithm(std::string name);
			void init(std::string name, Gen gen);
			void get(std::string name);
			void result(double result);

            void update_status(const Status & status);

			void run_app(const Point & p);
			void app_finished(int code);
			void publish_result(FunctionND func);
	};

}


#endif

