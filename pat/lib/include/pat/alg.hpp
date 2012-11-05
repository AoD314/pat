
#ifndef __alg_hpp__
#define __alg_hpp__

#include <vector>

#include "patconfig.hpp"
#include <pat/number.hpp>

namespace pat
{
	enum PAT_EXPORTS PAT_ALGORITHM
	{
		//! Random
		PAT_ALG_RND,

		//! BruteForce
		PAT_ALG_BF,

		//! Gradient
		PAT_ALG_GR,

		//! DownHill Sampling
		PAT_ALG_DHS
	};

	//! This class provide connect between this application and PAT System
	class PAT_EXPORTS Alg
	{
		public:
			Alg(PAT_ALGORITHM alg);

			void set_dx(std::vector<Number> & dx);
			void set_x (std::vector<Number> & x);

			//! set limit by epsilon of working of the algorithm
			//! \param eps - it's different between two last results
			void set_eps(double eps = 0.000000025);

			//! set limit by iterations of working of the algorithm
			//! \param n - in iterations
			void set_n(size_t n = 2000000000);

			//! set limit by time of working of the algorithm
			//! \param time - in seconds
			void set_time(size_t time);

		private:

	};

}

#endif
