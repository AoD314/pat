
#include "pat/gen.hpp"

namespace pat
{
    Gen::Gen() {}

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

	std::ostream& operator << (std::ostream& out, const Gen& gen)
	{
		out << "[ ";

		for (size_t i = 0; i < gen.list.size(); ++i)
		{
			out << to_str<Number>(gen.list.at(i));
			if (i != gen.list.size() - 1)
				out << ", ";
		}

		out << " ]";
		return out;
	}

}
