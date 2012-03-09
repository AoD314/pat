

#ifndef __SPACE_PARAM_HPP__
#define __SPACE_PARAM_HPP__

#include <string>

#include "pat/point.hpp"
#include "pat/range.hpp"

namespace pat
{
	class SpaceParam
	{
		public:
			SpaceParam(size_t N = 64, double eps = 0.25);

            void add(std::string name, Range r);

			void set_current_point(Point p);

			Point get_def();

			Point get(size_t i);
			std::string get(std::string name);

			bool exist(std::string name);

			size_t max_iter();
			double epsilon();

			bool have_points();

		private:
			size_t n;
			double e;

            void initialize();
			Point def_point;
			Point current_point;
			std::vector<Range>       space;
			std::vector<std::string> names;

			std::vector<int>    div_points;
	};


}

#endif

