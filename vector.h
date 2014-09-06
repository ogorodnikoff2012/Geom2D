#ifndef VECTOR_H
#define VECTOR_H

class Line;

#include <iostream>

class Vector
{
public:
    double x, y;
    bool isValid;
    Vector(const double x, const double y) :
        x(x),
        y(y),
        isValid(true)
    {

    }

    Vector(const Vector &v) :
        x(v.x),
        y(v.y),
        isValid(v.isValid)
    {

    }

    Vector(const bool isValid = true) :
        x(0),
        y(0),
        isValid(isValid)
    {

    }
    Vector operator -() const;
    Vector operator +(const Vector &v) const;
    Vector operator -(const Vector &v) const;
    double operator *(const Vector &v) const;
    Vector operator *(const double d) const;
    double cross(const Vector &v) const;
    double operator ^(const Vector &v) const;
    double length() const;
    double dist(const Vector &v) const;
    double dist(const Line &l) const;
    bool operator ==(const Vector &v) const;
    Vector operator +=(const Vector &v);
    Vector operator -=(const Vector &v);
    Vector operator *=(double d);
    Vector normalize();
    Vector normalized() const;
    Vector getNormal() const;
    bool operator ||(const Vector &v) const;
    Vector rotate(const double phi);
    Vector rotated(const double phi) const;
};

extern Vector operator *(const double d, const Vector &v);
extern std::istream &operator >>(std::istream &in, Vector &v);
extern std::ostream &operator <<(std::ostream &out, Vector &v);

#endif // VECTOR_H
