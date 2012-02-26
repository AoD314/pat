
#include "pat/point.hpp"

namespace pat
{
    Point::Point() : point() {}

    Point& Point::add(const Number & num)
    {
        point.push_back(num);
        return *this;
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

    const Point operator+(const Number& left, const Point& right)
    {
        return operator +(right, left);
    }


    Point& Point::operator += ( const Point & p)
    {
        for (size_t i = 0; i < point.size(); ++i)
            point.at(i) += p.point.at(i);

        return *this;
    }

    Point& Point::operator += ( const Number & num)
    {
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
        for (size_t i = 0; i < point.size(); ++i)
            point.at(i) -= p.point.at(i);

        return *this;
    }

    Point& Point::operator -= ( const Number & num)
    {
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
        for (size_t i = 0; i < point.size(); ++i)
            point.at(i) *= p.point.at(i);

        return *this;
    }

    Point& Point::operator *= ( const Number & num)
    {
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
        for (size_t i = 0; i < point.size(); ++i)
            point.at(i) /= p.point.at(i);

        return *this;
    }

    Point& Point::operator /= ( const Number & num)
    {
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
