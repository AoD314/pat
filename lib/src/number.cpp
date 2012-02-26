
#include "pat/number.hpp"
#include <iomanip>

namespace pat
{
    Number::Number()
    {
        type_v = int_t;
        value_i = 0;
    }

    Number::Number(int num)
    {
        type_v = int_t;
        value_i = static_cast<long long int>(num);
    }

    Number::Number(long long int num)
    {
        type_v = int_t;
        value_i = num;
    }

    Number::Number(float num)
    {
        type_v = float_t;
        value_f = static_cast<double>(num);
    }

    Number::Number(double num)
    {
        type_v = float_t;
        value_f = num;
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


    const Number Number::operator-() const
    {
        if (type_v == int_t)
            return Number(-value_i);
        if (type_v == float_t)
            return Number(-value_f);
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

    bool Number::operator == ( const Number & num )
    {
        if (num.type_v == float_t)
            return num.value_f == value_f;

        if (num.type_v == int_t)
            return num.value_i == value_i;
    }

    Number& Number::operator = (const Number & num)
    {
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
            type_v = float_t;

            double v;
            if (type_v == float_t)
                v = value_f;
            if (type_v == int_t)
                v = static_cast<double>(value_i);

            value_f = v + num.to_float();
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
            type_v = float_t;

            double v;
            if (type_v == float_t)
                v = value_f;
            if (type_v == int_t)
                v = static_cast<double>(value_i);

            value_f = v - num.to_float();
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
            type_v = float_t;

            double v;
            if (type_v == float_t)
                v = value_f;
            if (type_v == int_t)
                v = static_cast<double>(value_i);

            value_f = v * num.to_float();
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
            type_v = float_t;

            double v;
            if (type_v == float_t)
                v = value_f;
            if (type_v == int_t)
                v = static_cast<double>(value_i);

            value_f = v / num.to_float();
        }

        return *this;
    }


    Number  Number::operator + ( const Number & num)
    {
        Number n(0);

        if (type_v == num.type_v)
        {
            n.type_v = num.type_v;

            if (type_v == int_t)
            {
                n.value_i = this->value_i + num.value_i;
            }

            if (type_v == float_t)
            {
                n.value_f = this->value_f + num.value_f;
            }
        }
        else
        {
            n.type_v = float_t;
            n.value_f = to_float() + num.to_float();
        }

        return n;
    }

    Number  Number::operator - ( const Number & num)
    {
        Number n(0);

        if (type_v == num.type_v)
        {
            n.type_v = num.type_v;

            if (type_v == int_t)
            {
                n.value_i = this->value_i - num.value_i;
            }

            if (type_v == float_t)
            {
                n.value_f = this->value_f - num.value_f;
            }
        }
        else
        {
            n.type_v = float_t;
            n.value_f = to_float() - num.to_float();
        }

        return n;
    }

    Number  Number::operator * ( const Number & num)
    {
        Number n(0);

        if (type_v == num.type_v)
        {
            n.type_v = num.type_v;

            if (type_v == int_t)
            {
                n.value_i = this->value_i * num.value_i;
            }

            if (type_v == float_t)
            {
                n.value_f = this->value_f * num.value_f;
            }
        }
        else
        {
            n.type_v = float_t;
            n.value_f = to_float() * num.to_float();
        }

        return n;
    }

    Number  Number::operator / ( const Number & num)
    {
        Number n(0);

        if (type_v == num.type_v)
        {
            n.type_v = num.type_v;

            if (type_v == int_t)
            {
                n.value_i = this->value_i / num.value_i;
            }

            if (type_v == float_t)
            {
                n.value_f = this->value_f / num.value_f;
            }
        }
        else
        {
            n.type_v = float_t;
            n.value_f = to_float() / num.to_float();
        }

        return n;
    }

    std::ostream& operator << (std::ostream& out, const Number& n)
    {
        if (n.type_v == float_t)
            out << std::fixed << std::setprecision(16) << n.value_f;

        if (n.type_v == int_t)
            out << n.value_i;

        return out;
    }


}
