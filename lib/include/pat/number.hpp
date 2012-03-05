
#ifndef __NUMBER_HPP__
#define __NUMBER_HPP__

#include <string>
#include <ostream>

namespace pat
{
    enum TypeValue
    {
        int_t,
        float_t
    };

    class Number
    {
        public:
            Number();
            Number(int num);
            Number(long long int num);

            Number(float num);
            Number(double num);

			Number(std::string num);

            Number(const Number & );

			Number delta() const;

            // operators
            const Number operator-() const;

                 Number& operator++();
            const Number operator++(int);

            Number& operator  = ( const Number & );

            Number& operator += ( const Number & );
            Number& operator -= ( const Number & );
            Number& operator *= ( const Number & );
            Number& operator /= ( const Number & );

			friend bool operator <  (const Number& left, const Number& right);
			friend bool operator >  (const Number& left, const Number& right);
			friend bool operator <= (const Number& left, const Number& right);
			friend bool operator >= (const Number& left, const Number& right);
			friend bool operator == (const Number& left, const Number& right);
			friend bool operator != (const Number& left, const Number& right);

            double to_float() const ;
            long long int to_int() const ;

			friend const Number operator + (const Number& left, const Number& right);
			friend const Number operator - (const Number& left, const Number& right);
			friend const Number operator * (const Number& left, const Number& right);
			friend const Number operator / (const Number& left, const Number& right);

            friend std::ostream& operator << (std::ostream&, const Number&);

        private:

            TypeValue type_v;

            double        value_f;
            long long int value_i;
    };
}

#endif
