
#ifndef __PARAMS_HPP__
#define __PARAMS_HPP__

#include <string>
#include <vector>
#include <typeinfo>
#include <limits>
#include <exception>

#include <stdint.h>

#include "pat/pat_record_params.hpp"
#include "patconfig.hpp"

namespace pat
{
	class PAT_EXPORTS Params
	{
		public:
			Params();
			virtual ~Params();

			double minvalue;

			typedef int64_t   r_int;
			typedef double    r_float;

			void operator+=(Params & p);
			void operator/=(double val);

			template <typename T>
			void add(std::string name, T min, T max, T step, T def)
			{
				std::string type(typeid(step).name());

				if ((type.compare("f") == 0)     ||
					(type.compare("d") == 0)     ||
					(type.compare("float") == 0) ||
					(type.compare("double") == 0))
				{
					record_float.push_back(RecordParams<r_float>(name, min, max, step, def));
				}
				else
				{
					record_int.push_back  (RecordParams<r_int>  (name, min, max, step, def));
				}

				list_name_params.push_back(name);
			}

			template <typename T>
			void add(std::string name, T min, T max, T step)
			{
				add<T>(name, min, max, step, min + ((max - min)/static_cast<T>(2)));
			}

			template <typename T>
			void add(std::string name, T min, T max)
			{
				add<T>(name, min, max, static_cast<T>(1));
			}

			bool find(std::string name);

			std::string get_str(std::string name);

			template <typename T>
			T get(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).value);

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).value);

				return T();
			}

			template <typename T>
			T get_min(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).min);

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).min);

				return T();
			}

			template <typename T>
			T get_step(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).step);

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).step);

				return T();
			}

			template <typename T>
			T get_max(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).max);

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).max);

				return T();
			}

			template <typename T>
			T get_def(std::string name)
			{
				if (find_record_float(name))
					return static_cast<T>(get_record_float(name).def);

				if (find_record_int(name))
					return static_cast<T>(get_record_int(name).def);

				return T();
			}

			template <typename T>
			void set(std::string name, T value)
			{
				if (find_record_float(name))
					get_record_float(name).value = value;

				if (find_record_int(name))
					get_record_int(name).value = value;

				return T();
			}

			void set_min(std::string name);

			void set_def(std::string name);

			void set_max(std::string name);

			template<typename T>
			void modify_add(std::string name, T value)
			{
				if (find_record_float(name))
				{
					get_record_float(name).value = static_cast<T>(get_record_float(name).value + value);
					if (get_record_float(name).value < get_record_float(name).min)
						get_record_float(name).value = get_record_float(name).min;
					if (get_record_float(name).value > get_record_float(name).max)
						get_record_float(name).value = get_record_float(name).max;
				}

				if (find_record_int(name))
				{
					get_record_int(name).value = static_cast<T>(get_record_int(name).value + value);
					if (get_record_int(name).value < get_record_int(name).min)
						get_record_int(name).value = get_record_int(name).min;
					if (get_record_int(name).value > get_record_int(name).max)
						get_record_int(name).value = get_record_int(name).max;
				}

			}

			void next(std::string name, unsigned int count = 1);

			bool more_max(std::string name);
			bool less_min(std::string name);

			size_t get_points(std::string name)
			{
				if (find_record_float(name))
					return static_cast<size_t>(1 + (get_record_float(name).max - get_record_float(name).min) / (get_record_float(name).step));

				if (find_record_int(name))
					return static_cast<size_t>(1 + (get_record_int(name).max - get_record_int(name).min) / (get_record_int(name).step));

				throw std::exception();
			}

			std::vector<std::string> get_list_params();

			size_t dim();

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

