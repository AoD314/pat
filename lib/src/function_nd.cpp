
#include "pat/function_nd.hpp"

namespace pat
{

	bool operator < (const FunctionND& left, const FunctionND& right)
	{
		return left.value < right.value;
	}

	Number operator - (const FunctionND& left, const FunctionND& right)
	{
		return (left.value - right.value);
	}

	void sort(std::vector<FunctionND>& vec)
	{
		for (size_t i = 0; i < vec.size(); i++)
			for (size_t j = 0; j < vec.size() - 1; j++)
			{
				if (vec[j] < vec[j+1])
				{
					FunctionND tmp = vec[j];
					vec[j] = vec[j+1];
					vec[j+1] = tmp;
				}
			}
	}

}
