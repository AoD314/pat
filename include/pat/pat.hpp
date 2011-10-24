
#ifndef __PAT_HPP__
#define __PAT_HPP__
#define use_pat_system

#include <string>

#include <QtCore/QProcess>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

#include "pat/params.hpp"
#include "pat/convert.hpp"

namespace pat
{
	class PAT_BASE
	{
		public:
			void set_max_time(unsigned int sec);
			void set_max_iter(unsigned long long iter);
			void set_precision(double p);

			void run_auto_tune();

			void print_info();

		protected:
			Params params;
			virtual double run() = 0;
			virtual void  init() = 0;

		private:
			unsigned int       max_time;
			unsigned long long max_iter;
			double             precision;

			bool next_params();
	};

	class PAT_System
	{
		public:
			PAT_System();
			PAT_System(const std::string & host, unsigned int port);
			~PAT_System();

			template <typename T>
			T get_params(const std::string & name)
			{
				send_message_to_server("get", name, "", "", "", "", "");
				return from_str<T>(receive_message_from_server());
			}

			template <typename T>
			void init(const std::string & name, T min_value, T max_value, T step, T start_value)
			{
				send_message_to_server("init", name, to_str(start_value), to_str(min_value), to_str(max_value), to_str(step), typeid(step).name());
			}

			void send_result(double result);

		private:
			std::string  host;
			unsigned int port;
			QTcpSocket * socket;
			quint32 block_size;

			void send_message_to_server(std::string cmd, std::string var_name, std::string value, std::string value_from, std::string value_to, std::string value_step, std::string value_type);
			std::string receive_message_from_server();
	};

	class PAT_Algorithm : public QObject
	{
		Q_OBJECT
		protected:
			Params params;

		public:
			virtual void init() = 0;
			virtual void next_step(double value) = 0;
			virtual bool is_done() = 0;
			virtual void answer() = 0;

		signals:
			virtual void send(QString val);
			virtual void info(QString info);

		public slots:
			virtual void result(double val) = 0;
			virtual void get(QString name) = 0;
			virtual void init(QString name, QString value, QString value_from, QString value_to, QString step, QString type) = 0;
	};

	class PAT_BruteForce : public PAT_Algorithm
	{
		Q_OBJECT

		public:
			PAT_BruteForce();

			void init();
			void next_step(double value);
			bool is_done();
			void answer();

		private:
			Params params_min;
			double MIN;
			bool isdone;
			bool is_need_first_pass;
			std::string testsystem;

		signals:
			void send(QString val);
			void info(QString info);

		public slots:
			void result(double val);
			void get(QString name);
			void init(QString name, QString value, QString value_from, QString value_to, QString step, QString type);
	};

}

#endif
