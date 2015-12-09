#include <cmath>
#include <iostream>
#include "vector.h"
#include "math_ext.h"

using namespace geom2d;

Vector Vector::operator -() const
{
    return Vector(-x, -y, isValid);
}

Vector Vector::operator +(const Vector &v) const
{
    return Vector(x + v.x, y + v.y, isValid && v.isValid);
}

Vector Vector::operator -(const Vector &v) const
{
    return Vector(x - v.x, y - v.y, isValid && v.isValid);
}

Vector Vector::operator *(const double d) const
{
    return Vector(x * d, y * d, isValid);
}

Vector Vector::operator /(const double d) const
{
    return Vector(x / d, y / d, isValid && !equal(d, 0));
}

double Vector::operator *(const Vector &v) const
{
    return x * v.x + y * v.y;
}

double Vector::operator /(const Vector &v) const
{
    return x * v.y - y * v.x;
}

double Vector::operator ^(const Vector &v) const
{
    if (!(isValid && v.isValid))
    {
        return -100;
    }
    return atan2((*this) / (v), (*this)*(v));
}

Vector geom2d::operator *(const double d, const Vector &v)
{
    return v * d;
}

double Vector::length() const
{
    if (!isValid)
    {
        return -100;
    }
    return sqrt(x * x + y * y);
}

double Vector::dist(const Vector &v) const
{
    return (*this - v).length();
}

bool Vector::operator ==(const Vector &v) const
{
    return isValid && v.isValid && equal(x, v.x) && equal(y, v.y);
}

Vector Vector::operator +=(const Vector &v)
{
    x += v.x;
    y += v.y;
    isValid &= v.isValid;
    return *this;
}

Vector Vector::operator -=(const Vector &v)
{
    x -= v.x;
    y -= v.y;
    isValid &= v.isValid;
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
    if (!equal(l, 0))
    {
        x /= l;
        y /= l;
    }
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
    return Vector(y, -x, isValid).normalize();
}

bool Vector::operator ||(const Vector &v) const
{
    return isValid && v.isValid && equal(x * v.y, y * v.x);
}

Vector Vector::rotated(const double phi) const
{
    Vector v(*this);
    double cosa = v.x, sina = v.y;
    double cosphi = cos(phi), sinphi = sin(phi);
    v.x = cosa * cosphi - sina * sinphi;
    v.y = sina * cosphi + cosa * sinphi;
    return v;
}

Vector Vector::rotate(const double phi)
{
    return *this = rotated(phi);
}

std::istream &geom2d::operator >>(std::istream &in, Vector &v)
{
    in >> v.x >> v.y;
    return in;
}

std::ostream &geom2d::operator <<(std::ostream &out, const Vector &v)
{
    out << v.x << ' ' << v.y;
    return out;
}
