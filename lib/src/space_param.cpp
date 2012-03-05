
#include "pat/space_param.hpp"
#include "pat/pat_convert.hpp"

namespace pat
{

	SpaceParam::SpaceParam(size_t N, double eps)
	{
		n = N;
		e = eps;

		div_points.clear();
		space.clear();
	}

	void SpaceParam::add(std::string name, Range r, Number def_value)
	{
		if (!exist(name))
		{
			names.push_back(name);
			space.push_back(r);
			def_point.add(def_value);
		}
	}

	size_t SpaceParam::max_iter()
	{
		return n;
	}

	std::string SpaceParam::get(std::string name)
	{
		int index = -1;

		for(size_t i = 0; i < names.size(); i++)
		{
			if (name.compare(names.at(i)) == 0)
			{
				index = i;
			}
		}

		return to_str(current_point[index]);
	}

	double SpaceParam::epsilon()
	{
		return e;
	}

	bool SpaceParam::have_points()
	{

	}

	bool SpaceParam::exist(std::string name)
	{
		bool ex = false;

		for(size_t i = 0; i < names.size(); i++)
		{
			if (name.compare(names.at(i)) == 0)
			{
				ex = true;
				break;
			}
		}

		return ex;
	}

	void SpaceParam::set_current_point(Point p)
	{
		current_point = p;
	}

	Point SpaceParam::get_def()
	{
		if (def_point.dim() == 0)
		{
			Point point;

			for (size_t i = 0; i < space.size(); ++i)
			{
				Range r(space[i]);
				point.add((r.max - r.min) / 2);
			}

			return point;
		}
		else
		{
			return def_point;
		}
	}

	Point SpaceParam::get(size_t i)
	{
		Point point;
		return point;
	}


}

