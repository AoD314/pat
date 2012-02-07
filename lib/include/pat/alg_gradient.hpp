
#ifndef __ALG_GRADIENT_HPP__
#define __ALG_GRADIENT_HPP__

#include <QtCore>

#include "patconfig.hpp"
#include "pat/pat_params.hpp"
#include "pat/algorithm.hpp"

#include <vector>

namespace pat
{
	class PAT_EXPORTS PAT_Gradient : public PAT_Algorithm
	{
		Q_OBJECT

		public:
			PAT_Gradient();

			void init();
			void next_step(double value);
			bool is_done();
			void answer();

		protected:
			void logging(QString msg);

		private:
			Params params_min;
			Params params_point;
			double MIN;
			bool isdone;
			bool is_need_first_pass;
			std::string testsystem;
			double lambda;
			size_t mode;
			std::vector<double> res;
			std::vector<std::string> list;

		public slots:
			void result(double val);
			void get(QString name);
			void init(StrParams sp);
	};

}

#endif
