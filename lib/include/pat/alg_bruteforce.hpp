
#ifndef __PAT_ALG_BRUTEFORCE_HPP__
#define __PAT_ALG_BRUTEFORCE_HPP__

#include <QtCore>

#include "pat/pat_params.hpp"
#include "pat/algorithm.hpp"
#include "pat/pat_strparam.hpp"

namespace pat
{	
	class PAT_BruteForce : public PAT_Algorithm
	{
		Q_OBJECT

		public:
			PAT_BruteForce();

			void init();
			void next_step(double value);
			bool is_done();
			void answer();

		protected:
			void logging(QString msg);

		private:
			Params params_min;
			bool isdone;
			bool is_need_first_pass;
			std::string testsystem;

		public slots:
			void result(double val);
			void get(QString name);
			void init(StrParams sp);
	};

}
	
#endif
	
