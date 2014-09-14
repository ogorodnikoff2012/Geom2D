#include <cmath>
#include <iostream>
#include "vector.h"
#include "line.h"
#include "math_ext.h"

Vector Vector::operator -() const
{
    return Vector(-x, -y);
}

Vector Vector::operator +(const Vector &v) const
{
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator -(const Vector &v) const
{
    return Vector(x - v.x, y - v.y);
}

Vector Vector::operator *(const double d) const
{
    return Vector(x * d, y * d);
}

double Vector::operator *(const Vector &v) const
{
    return x * v.x + y * v.y;
}

double Vector::cross(const Vector &v) const
{
    return x * v.y - y * v.x;
}

double Vector::operator ^(const Vector &v) const
{
    return atan2(this->cross(v), this->operator *(v));
}

Vector operator *(const double d, const Vector &v)
{
    return v * d;
}

double Vector::length() const
{
    return sqrt(x * x + y * y);
}

double Vector::dist(const Vector &v) const
{
    return (*this - v).length();
}

double Vector::dist(const Line &l) const
{
    return l.dist(*this);
}

bool Vector::operator ==(const Vector &v) const
{
    return equal(x, v.x) && equal(y, v.y);
}

Vector Vector::operator +=(const Vector &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector Vector::operator -=(const Vector &v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector Vector::operator *=(double d)
{
    x *= d;
    y *= d;
    return *this;
}

Vector Vector::normalize()
{
    double l = length();
    x /= l;
    y /= l;
    return *this;
}

Vector Vector::normalized() const
{
    Vector v(*this);
    v.normalize();
    return v;
}

Vector Vector::getNormal() const
{
    return Vector(y, -x).normalize();
}

bool Vector::operator ||(const Vector &v) const
{
    return equal(x * v.y, y * v.x);
}

Vector Vector::rotated(const double phi) const
{
    Vector v = normalized();
    double cosa = v.x, sina = v.y;
    double cosphi = cos(phi), sinphi = sin(phi);
    v.x = cosa * cosphi + sina * sinphi;
    v.y = sina * cosphi - cosa * sinphi;
    return v * length();
}

Vector Vector::rotate(const double phi)
{
    return *this = rotated(phi);
}

std::istream &operator >>(std::istream &in, Vector &v)
{
    in >> v.x >> v.y;
    return in;
}

std::ostream &operator <<(std::ostream &out, const Vector &v)
{
    out << v.x << ' ' << v.y;
    return out;
}
