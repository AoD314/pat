
#ifndef __PAT_BASE_HPP__
#define __PAT_BASE_HPP__

#include "patconfig.hpp"
#include "pat/pat_params.hpp"

namespace pat
{
	class PAT_EXPORTS PAT_BASE
	{
		public:
			void set_max_time(size_t sec);
			void set_max_iter(size_t iter);
			void set_precision(double p);

			void run_auto_tune();

			void print_info();

			virtual ~PAT_BASE();

		protected:
			Params params;
			virtual double run() = 0;
			virtual void  init() = 0;

		private:
			size_t max_time;
			size_t max_iter;
			double precision;

			bool next_params();
	};

}

#endif
