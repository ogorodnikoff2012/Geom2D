#include "line.h"
#include "vector.h"
#include <cmath>
#include "math_ext.h"

using namespace geom2d;

Line::Line(const Vector &A, const Vector &B, const bool isValid_)
{
	// Vector normal = (A - B).getNormal();
	Vector direction = (A - B);

	a = direction.y;
	b = - direction.x;
	c = -(a * A.x + b * A.y);
	isValid = isValid_ && A.isValid && B.isValid;
}

double Line::dist(const Vector &A) const
{
	if (!(isValid && A.isValid))
	{
		return -100;
	}
	Line l = normalized();
	return fabs(l.a * A.x + l.b * A.y + l.c);
}

Vector Line::intersect(const Line &l) const
{
	if (!(isValid && l.isValid))
	{
		return Vector(false);
	}
    
        double det = a * l.b - l.a * b;
        return Vector(c * l.b - l.c * b, a * l.c - l.a * c) / det;
}

Line Line::normalize()
{
	double k = sqrt(a * a + b * b) * signum(a);
	if (!equal(k, 0))
	{
		a /= k;
		b /= k;
		c /= k;
	}
	return *this;
}

Line Line::normalized() const
{
	Line l(*this);
	return l.normalize();
}

Vector Line::getNormal() const
{
	return Vector(a, b, isValid).normalize();
}

bool Line::operator ||(const Line &l) const
{
	return isValid && l.isValid && (getNormal() || l.getNormal());
}

int Line::where(const Vector &v) const
{
	if (!(isValid && v.isValid))
	{
		return -100;
	}
	return signum(a * v.x + b * v.y + c);
}

bool Line::operator ==(const Line &l) const
{
	return isValid && l.isValid && equal(a * l.b, b * l.a) && equal(a * l.c, c * l.a);
}

Vector Line::projection(const Vector &v) const
{
	if (!(isValid && v.isValid))
	{
		return Vector(false);
	}
	Vector normal = getNormal();
	return intersect(Line(v, v + normal));
}

void Line::moveToVector(const Vector &v)
{
	if (!(isValid && v.isValid))
	{
		return;
	}
	normalize();
	Vector normal(a, b);
	c -= v * normal;
}
