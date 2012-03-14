
#include <cmath>

#include "pat/space_param.hpp"
#include "pat/pat_convert.hpp"

#include <iostream>


namespace pat
{

	SpaceParam::SpaceParam(size_t N, double eps)
	{
		n = N;
		e = eps;
		space.clear();
	}

	std::vector<int> SpaceParam::factorize(size_t num)
	{
		std::vector<int> mn;
		size_t M = sqrt(num) + 1;
		size_t j = 0;

		for (size_t i = 2; i < M;)
		{
			if (num % i == 0)
			{
				if (mn.size() < space.size())
				{
					mn.push_back(i);
					j++;
				}
				else
				{
					j = (j + 1) % space.size();
					mn[j] *= i;
				}

				num /= i;
			}
			else
			{
				i++;
			}
			if (num <= 1)  break;
		}

		return mn;
	}

	void SpaceParam::initialize()
	{
		for (size_t i = 0; i < names.size(); ++i)
		{
			current_point.add(space.at(i).min);
		}
	}

	void SpaceParam::add(std::string name, Range r)
	{
		if (!exist(name))
		{
			names.push_back(name);
			space.push_back(r);
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
				break;
			}
		}

		if (current_point.dim() == 0)
			initialize();

		return to_str(current_point[index], 0, 32);
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
				point.add((r.min + r.max) / 2);
			}

			return point;
		}
		else
		{
			return def_point;
		}
	}

	Point SpaceParam::get(size_t index)
	{
		if (div_points.empty())
		{
			div_points = factorize(n);

			while (space.size() > div_points.size())
			{
				div_points.push_back(1);
			}
		}

		Point point;

		for (size_t i = 0; i < space.size(); i++)
		{
			size_t j = index % div_points[i];
			index /= div_points[i];

			Number num;
			num = space[i].min + j * (space[i].max - space[i].min) / (div_points[i] - 1);
			point.add(num);
		}
		return point;
	}

	Point SpaceParam::get_simplex(size_t index)
	{
		if (index == 0)
		{
			Point p;
			for (size_t i = 0; i < space.size(); i++)
			{
				p.add(space.at(i).min);
			}
			return p;
		}
		else
		{
			Point p;
			for (size_t i = 0; i < index; i++)
			{
				p.add(space.at(i).max);
			}
			for (size_t i = index; i < space.size(); i++)
			{
				p.add(space.at(i).min);
			}
			return p;
		}
	}


}

