
#include <iomanip>
#include <cmath>

#include "pat/convert.hpp"
#include "pat/number.hpp"


namespace pat
{
	Number::Number()
	{
		type_v = int_t;
		value_i = 0;
		value_f = 0.0;
	}

	Number::Number(int num)
	{
		type_v = int_t;
		value_i = static_cast<long long int>(num);
		value_f = 0.0;
	}

	Number::Number(long long int num)
	{
		type_v = int_t;
		value_i = num;
		value_f = 0.0;
	}

	Number::Number(size_t num)
	{
		type_v = int_t;
		value_i = static_cast<long long int>(num);
		value_f = 0.0;
	}

	Number::Number(float num)
	{
		type_v = float_t;
		value_f = static_cast<double>(num);
		value_i = 0;
	}

	Number::Number(double num)
	{
		type_v = float_t;
		value_f = num;
		value_i = 0;
	}

	Number::Number(std::string num)
	{
		if (num.find(".") == std::string::npos && num.find(".") == std::string::npos)
		{
			type_v  = int_t;
			value_i = from_str<long long int>(num);
		}
		else
		{
			type_v  = float_t;
			value_f = from_str<double>(num);
		}
	}

	Number::Number(const Number & num)
	{
		value_f = num.value_f;
		value_i = num.value_i;
		type_v  = num.type_v;
	}

	double Number::to_float() const
	{
		if (type_v == float_t)
		{
			return value_f;
		}
		else
			return static_cast<double>(value_i);
	}

	long long int Number::to_int() const
	{
		if (type_v == int_t)
		{
			return value_i;
		}
		else
			return static_cast<long long int>(value_f);
	}

	Number abs(const Number & num)
	{
		if (num < 0)
			return -num;
		else
			return num;
	}

	Number Number::delta() const
	{
		Number n;
		if (type_v == int_t)
			n = 1;
		if (type_v == float_t)
			n = 0.00000025;
		return n;
	}

	const Number Number::operator-() const
	{
		if (type_v == int_t)
			return Number(-value_i);
		if (type_v == float_t)
			return Number(-value_f);

		throw std::exception();
	}

	Number& Number::operator++()
	{
		if (type_v == int_t)
			++value_i;
		if (type_v == float_t)
			++value_f;

		return *this;
	}

	const Number Number::operator++(int)
	{
		Number num(0);

		num.type_v  = this->type_v;

		if (type_v == int_t)
		{
			num.value_i = this->value_i;
			++value_i;
		}

		if (type_v == float_t)
		{
			num.value_f = this->value_f;
			++value_f;
		}

		return num;
	}

	bool operator <  (const Number& left, const Number& right)
	{
		if (left.type_v == right.type_v)
		{
			if (left.type_v == float_t)
				return left.value_f < right.value_f;

			if (left.type_v == int_t)
				return left.value_i < right.value_i;
		}
		else
		{
			return left.to_float() < right.to_float();
		}
		throw std::exception();
	}

	bool operator >  (const Number& left, const Number& right)
	{
		if (left.type_v == right.type_v)
		{
			if (left.type_v == float_t)
				return left.value_f > right.value_f;

			if (left.type_v == int_t)
				return left.value_i > right.value_i;
		}
		else
		{
			return left.to_float() > right.to_float();
		}
		throw std::exception();
	}

	bool operator <= (const Number& left, const Number& right)
	{
		if (left.type_v == right.type_v)
		{
			if (left.type_v == float_t)
				return left.value_f <= right.value_f;

			if (left.type_v == int_t)
				return left.value_i <= right.value_i;
		}
		else
		{
			return left.to_float() <= right.to_float();
		}
		throw std::exception();
	}

	bool operator >= (const Number& left, const Number& right)
	{
		if (left.type_v == right.type_v)
		{
			if (left.type_v == float_t)
				return left.value_f >= right.value_f;

			if (left.type_v == int_t)
				return left.value_i >= right.value_i;
		}
		else
		{
			return left.to_float() >= right.to_float();
		}
		throw std::exception();
	}

	bool operator != (const Number& left, const Number& right)
	{
		return !operator == (left, right);
	}

	bool operator == (const Number& left, const Number& right)
	{
		if (left.type_v == right.type_v)
		{
			if (left.type_v == float_t)
				return left.value_f == right.value_f;

			if (left.type_v == int_t)
				return left.value_i == right.value_i;
		}
		else
		{
			return left.to_float() == right.to_float();
		}
		throw std::exception();
	}

	Number& Number::operator = (const Number & num)
	{
		if (this == &num)
		{
			return *this;
		}

		value_f = num.value_f;
		value_i = num.value_i;
		type_v  = num.type_v;
		return *this;
	}

	Number& Number::operator += ( const Number & num)
	{
		if (type_v == num.type_v)
		{
			if (type_v == int_t)
			{
				value_i += num.value_i;
			}

			if (type_v == float_t)
			{
				value_f += num.value_f;
			}
		}
		else
		{
			double v;
			if (type_v == float_t)
				v = value_f;
			if (type_v == int_t)
				v = static_cast<double>(value_i);

			value_f = v + num.to_float();
			type_v = float_t;
		}

		return *this;
	}

	Number& Number::operator -= ( const Number & num)
	{
		if (type_v == num.type_v)
		{
			if (type_v == int_t)
			{
				value_i -= num.value_i;
			}

			if (type_v == float_t)
			{
				value_f -= num.value_f;
			}
		}
		else
		{
			double v;
			if (type_v == float_t)
				v = value_f;
			if (type_v == int_t)
				v = static_cast<double>(value_i);

			value_f = v - num.to_float();
			type_v = float_t;
		}

		return *this;
	}


	Number& Number::operator *= ( const Number & num)
	{
		if (type_v == num.type_v)
		{
			if (type_v == int_t)
			{
				value_i *= num.value_i;
			}

			if (type_v == float_t)
			{
				value_f *= num.value_f;
			}
		}
		else
		{
			double v;
			if (type_v == float_t)
				v = value_f;
			if (type_v == int_t)
				v = static_cast<double>(value_i);

			value_f = v * num.to_float();
			type_v = float_t;
		}

		return *this;
	}

	Number& Number::operator /= ( const Number & num)
	{
		if (type_v == num.type_v)
		{
			if (type_v == int_t)
			{
				value_i /= num.value_i;
			}

			if (type_v == float_t)
			{
				value_f /= num.value_f;
			}
		}
		else
		{
			double v;
			if (type_v == float_t)
				v = value_f;
			if (type_v == int_t)
				v = static_cast<double>(value_i);

			value_f = v / num.to_float();
			type_v = float_t;
		}

		return *this;
	}


	const Number operator + (const Number& left, const Number& right)
	{
		Number n(0);

		if (left.type_v == right.type_v)
		{
			n.type_v = left.type_v;

			if (left.type_v == int_t)
			{
				n.value_i = left.value_i + right.value_i;
			}

			if (left.type_v == float_t)
			{
				n.value_f = left.value_f + right.value_f;
			}
		}
		else
		{
			n.type_v = float_t;
			n.value_f = left.to_float() + right.to_float();
		}

		return n;
	}

	const Number operator - (const Number& left, const Number& right)
	{
		Number n(0);

		if (left.type_v == right.type_v)
		{
			n.type_v = left.type_v;

			if (left.type_v == int_t)
			{
				n.value_i = left.value_i - right.value_i;
			}

			if (left.type_v == float_t)
			{
				n.value_f = left.value_f - right.value_f;
			}
		}
		else
		{
			n.type_v = float_t;
			n.value_f = left.to_float() - right.to_float();
		}

		return n;
	}

	const Number operator * (const Number& left, const Number& right)
	{
		Number n(0);

		if (left.type_v == right.type_v)
		{
			n.type_v = left.type_v;

			if (left.type_v == int_t)
			{
				n.value_i = left.value_i * right.value_i;
			}

			if (left.type_v == float_t)
			{
				n.value_f = left.value_f * right.value_f;
			}
		}
		else
		{
			n.type_v = float_t;
			n.value_f = left.to_float() * right.to_float();
		}

		return n;
	}

	const Number operator / (const Number& left, const Number& right)
	{
		Number n(0);

		if (left.type_v == right.type_v)
		{
			n.type_v = left.type_v;

			if (left.type_v == int_t)
			{
				n.value_i = left.value_i / right.value_i;
			}

			if (left.type_v == float_t)
			{
				n.value_f = left.value_f / right.value_f;
			}
		}
		else
		{
			n.type_v = float_t;
			n.value_f = left.to_float() / right.to_float();
		}

		return n;
	}


	std::ostream& operator << (std::ostream& out, const Number& n)
	{
		if (n.type_v == float_t)
			out << n.value_f;

		if (n.type_v == int_t)
			out << n.value_i;

		return out;
	}


}
