
#ifndef __RECORD_PARAMS_HPP__
#define __RECORD_PARAMS_HPP__

#include <string>

#include "patconfig.hpp"

namespace pat
{
	template <typename T>
	class PAT_EXPORTS RecordParams
	{
		public:
			RecordParams(std::string name_var, T min_value, T max_value, T step_value, T def_value)
			: name(name_var), min(min_value), max(max_value), step(step_value), def(def_value), value(T())
			{}

			std::string name;
			T min;
			T max;
			T step;
			T def;
			T value;
	};
}

#endif
