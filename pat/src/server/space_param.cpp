
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "pat/convert.hpp"
#include "space_param.hpp"

namespace pat
{
	SpaceParam::SpaceParam(size_t N, double eps, size_t time) : 
		n(N), e(eps), generator(), distribution(0.0, 1.0), t(time), space(0)
	{ }

	void SpaceParam::set_n(size_t value)
	{
		n = value;
	}

	size_t SpaceParam::max_time()
	{
		return t;
	}

	std::vector<int> SpaceParam::factorize(size_t num)
	{
		std::vector<int> mn;
		size_t M = static_cast<size_t>(sqrt(num)) + 1;
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
			current_point.add(space.at(i).min());
		}
	}

	void SpaceParam::add(std::string name, Gen gen)
	{
		if (!exist(name))
		{
			names.push_back(name);
			space.push_back(gen);
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

	Point SpaceParam::get_rnd()
	{
		Point p;
		

		for (size_t i = 0; i < names.size(); ++i)
		{
			Number n = space.at(i).max() - space.at(i).min();
			Number del = (space.at(i).max().delta() < space.at(i).min().delta()) ? space.at(i).max().delta(): space.at(i).min().delta();

			double number = distribution(generator);
			Number nn(number * (n / del).to_float());
			n = space.at(i).min() + nn * del;

			p.add(n);
		}

		return p;
	}

	double SpaceParam::epsilon()
	{
		return e;
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
				point.add(space[i].middle());
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

			if (div_points[i] == 1)
			{
				num = space[i].min();
			}
			else
			{
				num = space[i].min() + j * (space[i].max() - space[i].min()) / (div_points[i] - 1);
			}

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
				p.add(space.at(i).min());
			}
			return p;
		}
		else
		{
			Point p;
			for (size_t i = 0; i < index; i++)
			{
				p.add(space.at(i).max());
			}
			for (size_t i = index; i < space.size(); i++)
			{
				p.add(space.at(i).min());
			}
			return p;
		}
	}


}

