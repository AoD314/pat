
#include "point.hpp"

namespace pat
{
	Point::Point() : point() {}

	Point& Point::add(const Number & num)
	{
		point.push_back(num);
		return *this;
	}

	Number& Point::operator[](size_t n)
	{
		return point.at(n);
	}

	Number  Point::operator[](size_t n) const
	{
		return point.at(n);
	}

	Point abs(const Point & point)
	{
		Point p;

		for (size_t i = 0; i < point.dim(); ++i)
		{
			p.add(abs(point[i]));
		}

		return p;
	}

	Number max(const Point & p)
	{
		Number n(0);

		if (p.dim() > 0)
		{
			n = p[0];
		}

		for (size_t i = 1; i < p.dim(); ++i)
		{
			if (n < p[i])
			{
				n = p[i];
			}
		}

		return n;
	}

	Number min(const Point & p)
	{
		Number n(0);

		if (p.dim() > 0)
		{
			n = p[0];
		}

		for (size_t i = 1; i < p.dim(); ++i)
		{
			if (n > p[i])
			{
				n = p[i];
			}
		}

		return n;
	}

	size_t Point::dim() const
	{
		return point.size();
	}

	Number Point::delta(size_t i) const
	{
		return point.at(i).delta();
	}

	const Point Point::operator-() const
	{
		Point pnt;

		for (size_t i = 0; i < point.size(); ++i)
			pnt.add(0 - point.at(i));

		return pnt;
	}

	const Point operator + (const Point& left, const Point & right)
	{
		Point pnt;

		for (size_t i = 0; i < left.point.size(); ++i)
			pnt.add(left.point.at(i) + right.point.at(i));

		return pnt;
	}

	const Point operator+(const Point& left,  const Number& right)
	{
		Point pnt;

		for (size_t i = 0; i < left.point.size(); ++i)
			pnt.add(left.point.at(i) + right);

		return pnt;
	}

	const Point operator + (const Number& left, const Point& right)
	{
		return operator +(right, left);
	}


	Point& Point::operator += ( const Point & p)
	{
		while(point.size() < p.point.size())
		{
			point.push_back(Number(0));
		}

		for (size_t i = 0; i < point.size(); ++i)
			point.at(i) += p.point.at(i);

		return *this;
	}

	Point& Point::operator += ( const Number & num)
	{
		if (point.size() == 0)
			point.push_back(Number(0));

		for (size_t i = 0; i < point.size(); ++i)
			point.at(i) += num;

		return *this;
	}

	const Point operator - (const Point& left, const Point & right)
	{
		Point pnt;

		for (size_t i = 0; i < left.point.size(); ++i)
			pnt.add(left.point.at(i) - right.point.at(i));

		return pnt;
	}

	const Point operator - (const Point& left,  const Number& right)
	{
		Point pnt;

		for (size_t i = 0; i < left.point.size(); ++i)
			pnt.add(left.point.at(i) - right);

		return pnt;
	}

	const Point operator - (const Number& left, const Point& right)
	{
		return operator +(-right, left);
	}


	Point& Point::operator -= ( const Point & p)
	{
		while(point.size() < p.point.size())
		{
			point.push_back(Number(0));
		}

		for (size_t i = 0; i < point.size(); ++i)
			point.at(i) -= p.point.at(i);

		return *this;
	}

	Point& Point::operator -= ( const Number & num)
	{
		if (point.size() == 0)
			point.push_back(Number(0));

		for (size_t i = 0; i < point.size(); ++i)
			point.at(i) -= num;

		return *this;
	}

	const Point operator * (const Point& left, const Point & right)
	{
		Point pnt;

		for (size_t i = 0; i < left.point.size(); ++i)
			pnt.add(left.point.at(i) * right.point.at(i));

		return pnt;
	}

	const Point operator * (const Point& left,  const Number& right)
	{
		Point pnt;

		for (size_t i = 0; i < left.point.size(); ++i)
			pnt.add(left.point.at(i) * right);

		return pnt;
	}

	const Point operator * (const Number& left, const Point& right)
	{
		return operator *(right, left);
	}

	Point& Point::operator *= ( const Point & p)
	{
		while(point.size() < p.point.size())
		{
			point.push_back(Number(1));
		}

		for (size_t i = 0; i < point.size(); ++i)
			point.at(i) *= p.point.at(i);

		return *this;
	}

	Point& Point::operator *= ( const Number & num)
	{
		if (point.size() == 0)
			point.push_back(Number(1));

		for (size_t i = 0; i < point.size(); ++i)
			point.at(i) *= num;

		return *this;
	}

	const Point operator / (const Point& left, const Point & right)
	{
		Point pnt;

		for (size_t i = 0; i < left.point.size(); ++i)
			pnt.add(left.point.at(i) / right.point.at(i));

		return pnt;
	}

	const Point operator / (const Point& left,  const Number& right)
	{
		Point pnt;

		for (size_t i = 0; i < left.point.size(); ++i)
			pnt.add(left.point.at(i) / right);

		return pnt;
	}

	Point& Point::operator /= ( const Point & p)
	{
		while(point.size() < p.point.size())
		{
			point.push_back(Number(1));
		}

		for (size_t i = 0; i < point.size(); ++i)
			point.at(i) /= p.point.at(i);

		return *this;
	}

	Point& Point::operator /= ( const Number & num)
	{
		if (point.size() == 0)
			point.push_back(Number(1));

		for (size_t i = 0; i < point.size(); ++i)
			point.at(i) /= num;

		return *this;
	}

	std::ostream& operator << (std::ostream& out, const Point& p)
	{
		out << "[ ";

		for (size_t i = 0; i < p.point.size(); ++i)
		{
			out << p.point.at(i);
			if (i != p.point.size() - 1)
				out << ", ";
		}

		out << " ]";
		return out;
	}



}
