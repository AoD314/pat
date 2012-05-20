
#include "pat/generator.hpp"

namespace pat
{

	Gen::Gen(Number a, Number b)
	{
		type = "ab";
		list.push_back(a);
		list.push_back(b);
	}

	Gen::Gen(Number a, Number b, Number step)
	{
		type = "abs";
		list.push_back(a);
		list.push_back(b);
		list.push_back(step);
	}

	Gen::Gen(const std::vector<Number> & v)
	{
		type = "vec";
		list = v;
	}

	std::string Gen::get_type()
	{
		return type;
	}

	std::vector<Number> Gen::get_list()
	{
		return list;
	}

	Number Gen::min()
	{
		return list[0];
	}

	Number Gen::max()
	{
		return list[list.size() - 1];
	}

	Number Gen::middle()
	{
		return ((max() + min()) / Number(2));
	}


}
