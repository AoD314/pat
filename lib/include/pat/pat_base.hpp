
#ifndef __PAT_BASE_HPP__
#define __PAT_BASE_HPP__

#include "patconfig.hpp"
#include "pat/pat_params.hpp"

namespace pat
{
	class PAT_EXPORTS PAT_BASE
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

}

#endif
