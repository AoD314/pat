
#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <vector>

#include "patconfig.hpp"

#include "pat/number.hpp"

namespace pat
{
	class PAT_EXPORTS Point
	{
		public:
			Point();

			Point& add(const Number & );


			Number& operator[](size_t n);
			Number  operator[](size_t n) const;

			Number  delta(size_t i) const;

			size_t dim() const;

			const Point operator-() const;

			Point& operator += ( const Point & );
			Point& operator += ( const Number & );

			Point& operator -= ( const Point & );
			Point& operator -= ( const Number & );

			Point& operator *= ( const Point & );
			Point& operator *= ( const Number & );

			Point& operator /= ( const Point & );
			Point& operator /= ( const Number & );

			friend const Point operator + (const Point& left,  const Point& right);
			friend const Point operator + (const Point& left,  const Number& right);
			friend const Point operator + (const Number& left, const Point& right);

			friend const Point operator - (const Point& left,  const Point& right);
			friend const Point operator - (const Point& left,  const Number& right);
			friend const Point operator - (const Number& left, const Point& right);

			friend const Point operator * (const Point& left,  const Point& right);
			friend const Point operator * (const Point& left,  const Number& right);
			friend const Point operator * (const Number& left, const Point& right);

			friend const Point operator / (const Point& left,  const Point& right);
			friend const Point operator / (const Point& left,  const Number& right);

			friend std::ostream& operator << (std::ostream&, const Point&);

		private:
			std::vector<Number> point;
	};


	Point  abs(const Point & point);
	Number max(const Point & p);
	Number min(const Point & p);

}

#endif
