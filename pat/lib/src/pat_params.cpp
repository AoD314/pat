
#include "pat/pat_params.hpp"
#include "pat/pat_convert.hpp"

namespace pat
{

	Params::Params(): minvalue(std::numeric_limits<double>::max()), record_int(), record_float(), list_name_params(){}

	Params::~Params() {}

	void Params::operator /= (double val)
	{
		std::vector<std::string> list = get_list_params();

		for (int i = 0; i < list.size(); i++)
		{
			std::string name = list.at(i);

			if (find_record_float(name))
				get_record_float(name).value /= val;

			if (find_record_int(name))
				get_record_int(name).value = static_cast<r_int>(static_cast<r_float>(get_record_int(name).value) / static_cast<r_float>(val));
		}
	}

	void Params::operator += (Params & p)
	{
		std::vector<std::string> list = p.get_list_params();

		for (int i = 0; i < list.size(); i++)
		{
			std::string name = list.at(i);

			if (find_record_float(name))
				get_record_float(name).value += p.get_record_float(name).value;

			if (find_record_int(name))
				get_record_int(name).value += p.get_record_int(name).value;
		}

	}

	bool Params::find(std::string name)
	{
		if (find_record_int(name))   return true;
		if (find_record_float(name)) return true;
		return false;
	}

	std::string Params::get_str(std::string name)
	{
		if (find_record_float(name))
			return to_str(get_record_float(name).value);

		if (find_record_int(name))
			return to_str(get_record_int(name).value);

		return "";
	}

	RecordParams<Params::r_int>& Params::get_record_int(std::string name)
	{
		for(std::size_t i = 0; i < record_int.size(); i++)
		{
			if (record_int[i].name.compare(name) == 0)
			{
				return record_int[i];
			}
		}
		throw std::exception();
	}

	RecordParams<Params::r_float>& Params::get_record_float(std::string name)
	{
		for(std::size_t i = 0; i < record_float.size(); i++)
		{
			if (record_float[i].name.compare(name) == 0)
			{
				return record_float[i];
			}
		}
		throw std::exception();
	}

	std::vector<std::string> Params::get_list_params()
	{
		return list_name_params;
	}

	bool Params::find_record_int(std::string name)
	{
		for(std::size_t i = 0; i < record_int.size(); i++)
		{
			if (record_int[i].name.compare(name) == 0)
			{
				return true;
			}
		}
		return false;
	}

	bool Params::find_record_float(std::string name)
	{
		for(std::size_t i = 0; i < record_float.size(); i++)
		{
			if (record_float[i].name.compare(name) == 0)
			{
				return true;
			}
		}

		return false;
	}

	void Params::set_min(std::string name)
	{
		if (find_record_float(name))
			get_record_float(name).value = get_record_float(name).min;

		if (find_record_int(name))
			get_record_int(name).value   = get_record_int(name).min;
	}

	void Params::set_max(std::string name)
	{
		if (find_record_float(name))
			get_record_float(name).value = get_record_float(name).max;

		if (find_record_int(name))
			get_record_int(name).value = get_record_int(name).max;
	}

	void Params::set_def(std::string name)
	{
		if (find_record_float(name))
			get_record_float(name).value = get_record_float(name).def;

		if (find_record_int(name))
			get_record_int(name).value = get_record_int(name).def;
	}

	void Params::next(std::string name, unsigned int count)
	{
		if (find_record_float(name))
			get_record_float(name).value = get_record_float(name).value + count * get_record_float(name).step;

		if (find_record_int(name))
			get_record_int(name).value = get_record_int(name).value + count * get_record_int(name).step;
	}

	size_t Params::dim()
	{
		return record_int.size() + record_float.size();
	}

	bool Params::more_max(std::string name)
	{
		if (find_record_float(name))
			return get_record_float(name).value > get_record_float(name).max;

		if (find_record_int(name))
			return get_record_int(name).value > get_record_int(name).max;

		return true;
	}

	bool Params::less_min(std::string name)
	{
		if (find_record_float(name))
			return get_record_float(name).value < get_record_float(name).min;

		if (find_record_int(name))
			return get_record_int(name).value < get_record_int(name).min;

		return true;
	}

}

