
#ifndef __PAT_HPP__
#define __PAT_HPP__

#define PAT

#include <string>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

#include "pat/params.hpp"

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

	class PAT_Server
	{
		public:

		private:
			QTcpServer server;
	};

	class PAT_System
	{
		public:
			PAT_System();
			PAT_System(const std::string & host, unsigned int port);
			~PAT_System();

			std::string get_params (const std::string & name);

			template <typename T>
			void init(const std::string & name, T min_value, T max_value, T step, T start_value)
			{
			}

			void send_result(double result);

		private:
			std::string  host;
			unsigned int port;
			QTcpSocket * socket;
	};

}

#endif
