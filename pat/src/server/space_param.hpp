

#ifndef __SPACE_PARAM_HPP__
#define __SPACE_PARAM_HPP__

#include <string>

#include "patconfig.hpp"
#include "point.hpp"
#include "pat/gen.hpp"

namespace pat
{
	class PAT_EXPORTS SpaceParam
	{
		public:
			SpaceParam(size_t N = 64, double eps = 0.000025, size_t time = 1000000000);

			void add(std::string name, Gen gen);

			void set_current_point(Point p);
			void set_n(size_t value);

			Point get_def();
			Point get_rnd();

			Point get(size_t index);
			Point get_simplex(size_t index);
			std::string get(std::string name);

			bool exist(std::string name);

			size_t max_iter();
			double epsilon();
			size_t max_time();

		private:
			size_t t;
			size_t n;
			double e;

			void initialize();
			Point def_point;
			Point current_point;
			std::vector<Gen>         space;
			std::vector<std::string> names;

			std::vector<int> div_points;

			std::vector<int> factorize(size_t num);
	};
}

#endif
