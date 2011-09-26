
#ifndef __CONVERT_HPP__
#define __CONVERT_HPP__

#include <string>
#include <sstream>
#include <iomanip>

namespace pat
{
	//! Convert Type to std::string
	template <typename T>
	std::string to_str(const T & t, int align = 0, int precision = 0, char c = ' ')
	{
		std::stringstream ss;
		ss	<< std::setiosflags(std::ios::fixed)
			<< std::setw(align)
			<< std::setfill(c);

		if (precision != 0)
			ss << std::setprecision(precision);

		ss << t;

		return ss.str();
	}

	//! Parse Type from std::string
	template <typename T>
	T from_str(const std::string & val, bool throw_exception = true, T defval = T())
	{
		std::istringstream iss(val);
		T t = T();
		bool result = iss >> t;
		if (!result && throw_exception) throw std::exception();
		if (!result && !throw_exception) return defval;
		return t;
	}


	//! Formating size to std::string
	std::string size_to_str(const size_t size_in_byte);

	//! Formating time to std::string
	std::string time_to_str(const double time_in_sec );
}

#endif

