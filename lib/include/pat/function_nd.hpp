
#ifndef __FUNCTION_ND_HPP__
#define __FUNCTION_ND_HPP__

#include <vector>

#include "pat/point.hpp"
#include "pat/number.hpp"

namespace pat
{
    class FunctionND
    {
        public:
            Point point;
            Number value;

			friend bool operator < (const FunctionND&, const FunctionND&);
			friend Number operator - (const FunctionND&, const FunctionND&);
    };

	void sort(std::vector<FunctionND>& vec);
}

#endif

