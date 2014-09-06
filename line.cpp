#include "line.h"
#include "vector.h"
#include <cmath>
#include "math_ext.h"

Line::Line(const Vector &A, const Vector &B)
{
    Vector normal = (A - B).getNormal();
    a = normal.x;
    b = normal.y;
    c = -(a * A.x + b * A.y);
    isValid = true;
}

double Line::dist(const Vector &A) const
{
    Line l = normalized();
    return fabs(l.a * A.x + l.b * A.y + l.c);
}

Vector Line::intersect(const Line &l) const
{
    if (a * l.b == b * l.a)
    {
        return Vector(false);
    }

    if (a == 0)
    {
        double y = -c / b;
        double x = -(l.b * y + l.c) / l.a;
        return Vector(x, y);
    }
    else
    {
        double koeff = l.a / a;
        double _b = b * koeff;
        double _c = c * koeff;
        // (l.a - _a) * x + (l.b - _b) * y + (l.c - _c) = 0
        double y = (_c - l.c) / (l.b - _b);
        double x = -(b * y + c) / a;
        return Vector(x, y);
    }
}

Line Line::normalize()
{
    double k = sqrt(a * a + b * b);
    a /= k;
    b /= k;
    c /= k;
    return *this;
}

Line Line::normalized() const
{
    Line l(*this);
    return l.normalize();
}

Vector Line::getNormal() const
{
    return Vector(a, b).normalize();
}

bool Line::operator ||(const Line &l) const
{
    return getNormal() || l.getNormal();
}

int Line::where(const Vector &v) const
{
    return signum(a * v.x + b * v.y + c);
}

bool Line::operator ==(const Line &l) const
{
    return equal(a * l.b, b * l.a) && equal(a * l.c, c * l.a);
}

Vector Line::projection(const Vector &v) const
{
    Vector normal = getNormal();
    return intersect(Line(v, v + normal));
}

void Line::moveToVector(const Vector &v)
{
    normalize();
    Vector normal(a, b);
    c += v * normal;
}
