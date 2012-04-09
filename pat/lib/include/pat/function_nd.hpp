
#ifndef __FUNCTION_ND_HPP__
#define __FUNCTION_ND_HPP__

#include <vector>

#include "patconfig.hpp"
#include "pat/point.hpp"
#include "pat/number.hpp"

namespace pat
{
	class PAT_EXPORTS FunctionND
	{
		public:
			Point point;
			Number value;

			friend bool operator < (const FunctionND&, const FunctionND&);
			friend bool operator > (const FunctionND&, const FunctionND&);
			friend Number operator - (const FunctionND&, const FunctionND&);

			friend std::ostream& operator << (std::ostream&, const FunctionND&);

	};

	void sort(std::vector<FunctionND>& vec);
}

#endif

