
#ifndef __RECORD_PARAMS_HPP__
#define __RECORD_PARAMS_HPP__

#include <string>

namespace pat
{
	template <typename T>
	class RecordParams
	{
		public:
			RecordParams(std::string params_name, T min_value, T max_value, T step_value, T start_value)
				: name(params_name), min(min_value), max(max_value), step(step_value), value(start_value){}

			std::string get_name()
			{
				return name;
			}

			T get_min()
			{
				return min;
			}

			T get_max()
			{
				return max;
			}

			T get_step()
			{
				return step;
			}

			T get_value()
			{
				return value;
			}

			void set_value(T current_value)
			{
				value = current_value;
			}

		private:
			std::string name;
			T min;
			T max;
			T step;
			T value;
	};
}

#endif
