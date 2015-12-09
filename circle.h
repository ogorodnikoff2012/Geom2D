#ifndef CIRCLE_H
#define CIRCLE_H

#include <utility>
#include <cstring>

namespace geom2d
{
class Vector;
class Line;

class Circle
{
public:
    double x, y, r;
    bool isValid;
    Circle(const double x, const double y, const double r, const bool isValid = true) :
        x(x),
        y(y),
        r(r),
        isValid(isValid)
    {

    }

    Circle(const bool isValid = true) :
        x(0),
        y(0),
        r(0),
        isValid(isValid)
    {

    }

    Circle(const Vector &center, const Vector &A, const bool isValid = true);
    Circle(const Vector &center, const double r, const bool isValid = true);
    std::pair<Line, Line> tangents(const Vector &v, Vector *X1 = NULL, Vector *X2 = NULL) const;
    std::pair<Vector, Vector> intersect(const Line &l) const;
    std::pair<Vector, Vector> intersect(const Circle &c) const;
    bool operator ==(const Circle &c) const;
    std::pair<Line, Line> commonTangents(const Circle &c, const bool outer) const;
    std::pair<Line, Line> commonOuterTangents(const Circle &c) const;
    std::pair<Line, Line> commonInnerTangents(const Circle &c) const;
    bool isTangent(const Line &l) const;
    int where(const Vector &v) const;
    Line radixLine(const Circle &c) const;
    Vector center() const;
};
}
#endif // CIRCLE_H
