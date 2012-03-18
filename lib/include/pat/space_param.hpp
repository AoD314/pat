

#ifndef __SPACE_PARAM_HPP__
#define __SPACE_PARAM_HPP__

#include <string>

#include "patconfig.hpp"
#include "pat/point.hpp"
#include "pat/range.hpp"

namespace pat
{
	class PAT_EXPORTS SpaceParam
	{
		public:
			SpaceParam(size_t N = 64, double eps = 0.000025, size_t time = 1000000000);

			void add(std::string name, Range r);

			void set_current_point(Point p);

			Point get_def();

			Point get(size_t index);
			Point get_simplex(size_t index);
			std::string get(std::string name);

			bool exist(std::string name);

			size_t max_iter();
			double epsilon();
			size_t max_time();

			bool have_points();

		private:
			size_t t;
			size_t n;
			double e;

			void initialize();
			Point def_point;
			Point current_point;
			std::vector<Range>       space;
			std::vector<std::string> names;

			std::vector<int>    div_points;

			std::vector<int> factorize(size_t num);

	};


}

#endif

