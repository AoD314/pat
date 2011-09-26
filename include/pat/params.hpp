
#ifndef __PARAMS_HPP__
#define __PARAMS_HPP__

#include <string>
#include <vector>
#include <typeinfo>

#include "pat/record_params.hpp"

namespace pat
{
	typedef long long int r_int;
	typedef double      r_float;

	class Params
	{
		public:
			template <typename T>
			void add(std::string name, T min_value, T max_value, T step, T start_value)
			{
				std::string type(typeid(step).name());

				if ((type.compare("f") == 0)     ||
					(type.compare("d") == 0)     ||
					(type.compare("float") == 0) ||
					(type.compare("double") == 0))
				{
					record_float.push_back(RecordParams<r_float>(name, min_value, max_value, step, start_value));
				}
				else
				{
					record_int.push_back(RecordParams<r_int>(name, min_value, max_value, step, start_value));
				}

				list_name_params.push_back(name);
			}

			template <typename T>
			void add(std::string name, T min_value, T max_value, T step)
			{
				add<T>(name, min_value, max_value, step, min_value + ((max_value - min_value)/static_cast<T>(2)));
			}

			template <typename T>
			void add(std::string name, T min_value, T max_value)
			{
				add<T>(name, min_value, max_value, static_cast<T>(1));
			}

			template <typename T>
			T get(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).get_value());

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).get_value());
			}

			template <typename T>
			T get_min(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).get_min());

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).get_min());
			}

			template <typename T>
			T get_step(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).get_step());

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).get_step());
			}

			template <typename T>
			T get_max(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).get_max());

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).get_max());
			}

			template <typename T>
			void set(std::string name, T value)
			{
				if (find_record_float(name))
					get_record_float(name).set_value(value);

				if (find_record_int(name))
					get_record_int(name).set_value(value);
			}

			void set_min(std::string name);

			void set_max(std::string name);

			void next(std::string name, unsigned int count = 1);

			bool more_max(std::string name);
			bool less_min(std::string name);

			std::vector<std::string> get_list_params();

		private:
			std::vector<RecordParams<r_int> >   record_int;
			std::vector<RecordParams<r_float> > record_float;
			std::vector<std::string>            list_name_params;

			RecordParams<r_int>&   get_record_int  (std::string name);
			RecordParams<r_float>& get_record_float(std::string name);

			bool find_record_int(std::string name);
			bool find_record_float(std::string name);
	};
}

#endif
