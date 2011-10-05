
#ifndef __PAT_HPP__
#define __PAT_HPP__

#include <string>

#include <QtNetwork/QTcpSocket>

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
	};

	class PAT_Client
	{
		public:
			PAT_Client();
			std::string get_params(std::string name);

		private:
			QTcpSocket socket;
	};
}

#endif
