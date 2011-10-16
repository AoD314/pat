
#include "pat/params.hpp"
#include "pat/convert.hpp"

namespace pat
{
	std::string Params::get_str(std::string name)
	{
		if (find_record_float(name))
			return to_str(get_record_float(name).get_value());

		if (find_record_int(name))
			return to_str(get_record_int(name).get_value());
	}

	RecordParams<Params::r_int>&   Params::get_record_int(std::string name)
	{
		for(std::size_t i = 0; i < record_int.size(); i++)
		{
			if (record_int[i].get_name().compare(name) == 0)
			{
				return record_int[i];
			}
		}
	}

	RecordParams<Params::r_float>& Params::get_record_float(std::string name)
	{
		for(std::size_t i = 0; i < record_float.size(); i++)
		{
			if (record_float[i].get_name().compare(name) == 0)
			{
				return record_float[i];
			}
		}
	}

	std::vector<std::string> Params::get_list_params()
	{
		return list_name_params;
	}

	bool Params::find_record_int(std::string name)
	{
		for(std::size_t i = 0; i < record_int.size(); i++)
		{
			if (record_int[i].get_name().compare(name) == 0)
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
			if (record_float[i].get_name().compare(name) == 0)
			{
				return true;
			}
		}

		return false;
	}

	void Params::set_min(std::string name)
	{
		if (find_record_float(name))
			get_record_float(name).set_value(get_record_float(name).get_min());

		if (find_record_int(name))
			get_record_int(name).set_value(get_record_int(name).get_min());
	}

	void Params::set_max(std::string name)
	{
		if (find_record_float(name))
			get_record_float(name).set_value(get_record_float(name).get_max());

		if (find_record_int(name))
			get_record_int(name).set_value(get_record_int(name).get_max());
	}

	void Params::next(std::string name, unsigned int count)
	{
		if (find_record_float(name))
			get_record_float(name).set_value(get_record_float(name).get_value() + count * get_record_float(name).get_step());

		if (find_record_int(name))
			get_record_int(name).set_value(get_record_int(name).get_value() + count * get_record_int(name).get_step());
	}

	bool Params::more_max(std::string name)
	{
		if (find_record_float(name))
			return get_record_float(name).get_value() > get_record_float(name).get_max();

		if (find_record_int(name))
			return get_record_int(name).get_value() > get_record_int(name).get_max();

		return true;
	}

	bool Params::less_min(std::string name)
	{
		if (find_record_float(name))
			return get_record_float(name).get_value() < get_record_float(name).get_min();

		if (find_record_int(name))
			return get_record_int(name).get_value() < get_record_int(name).get_min();

		return true;
	}

}
