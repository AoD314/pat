
#ifndef __ALG_DOWNHILL_SIMPLEX_HPP__
#define __ALG_DOWNHILL_SIMPLEX_HPP__

#include <QtCore>

#include "patconfig.hpp"
#include "pat/pat_params.hpp"
#include "pat/algorithm.hpp"

#include <vector>

namespace pat
{
	class PAT_EXPORTS PAT_Downhill_Simplex : public PAT_Algorithm
	{
		Q_OBJECT

		public:
			PAT_Downhill_Simplex();

			void init();
			void next_step(double value);
			bool is_done();
			void answer();

		protected:
			void logging(QString msg);

		private:
			Params params_def;
			Params params_min;

			double alpha;

			double MIN;
			bool isdone;
			bool is_need_first_pass;
			std::string testsystem;
			double lambda;
			size_t mode;
			std::vector<Params> res;
			std::vector<std::string> list;

		public slots:
			void result(double val);
			void get(QString name);
			void init(StrParams sp);
	};

}



#endif

