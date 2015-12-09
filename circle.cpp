#include "circle.h"
#include "line.h"
#include "vector.h"
#include <cmath>
#include "math_ext.h"

using namespace geom2d;

Circle::Circle(const Vector &center, const Vector &A, const bool isValid_) :
    x(center.x),
    y(center.y),
    r(center.dist(A)),
    isValid(isValid_ && center.isValid && A.isValid)
{

}

Circle::Circle(const Vector &center, const double r, const bool isValid_) :
    x(center.x),
    y(center.y),
    r(r),
    isValid(isValid_ && center.isValid)
{

}

std::pair<Line, Line> Circle::tangents(const Vector &A, Vector *_X1, Vector *_X2) const
{
    if (!(isValid && A.isValid))
    {
        return std::pair<Line, Line>(Line(false), Line(false));
    }

    Vector O(x, y);

    if (equal(r, 0))
    {

        if (_X1 != NULL) {
            *_X1 = O;
        }

        if (_X2 != NULL) {
            *_X2 = O;
        }
        
        return std::pair<Line, Line>(Line(A, O), Line(false));
    }

    double oxProjection = r * r / O.dist(A);
    Vector OH = (A - O).normalize() * oxProjection;
    Vector H = O + OH;
    Vector HX = OH.getNormal() * sqrt(r * r - oxProjection * oxProjection);
    Vector X1 = H + HX, X2 = H - HX;
    
    if (_X1 != NULL) {
        *_X1 = X1;
    }

    if (_X2 != NULL) {
        *_X2 = X2;
    }

    switch (where(A))
    {
    case 1:
        return std::pair<Line, Line>(Line(A, X1), Line(A, X2));

    case 0:
        return std::pair<Line, Line>(Line(A, A + (O - A).getNormal()), Line(false));

    default:
        return std::pair<Line, Line>(Line(false), Line(false));
    }
}

std::pair<Vector, Vector> Circle::intersect(const Line &l) const
{
    if (!(isValid && l.isValid))
    {
        return std::pair<Vector, Vector>(Vector(false), Vector(false));
    }

    Vector O(x, y);
    Vector H = l.projection(O);

    Vector OH = H - O;
    double hlLength = sqrt(max(r * r - OH.length() * OH.length(), 0.0));
    Vector HL = OH.getNormal() * hlLength;

    switch (where(H))
    {
    case -1:
        return std::pair<Vector, Vector>(H + HL, H - HL);

    case 0:
        return std::pair<Vector, Vector>(H, Vector(false));

    default:
        return std::pair<Vector, Vector>(Vector(false), Vector(false));
    }
}

std::pair<Vector, Vector> Circle::intersect(const Circle &c) const
{
    return intersect(radixLine(c));
}

bool Circle::operator ==(const Circle &c) const
{
    return isValid && c.isValid && equal(x, c.x) && equal(y, c.y) && equal(r, c.r);
}

std::pair<Line, Line> Circle::commonTangents(const Circle &c,
        const bool outer) const
{
    return outer ? commonOuterTangents(c) : commonInnerTangents(c);
}

std::pair<Line, Line> Circle::commonOuterTangents(const Circle &c) const
{
    if (!(isValid && c.isValid) || (Vector(x, y).dist(Vector(c.x, c.y)) < fabs(r - c.r)))
    {
        return std::pair<Line, Line>(Line(false), Line(false));
    }

    Vector point;
    Circle pseudo;

    if (r < c.r)
    {
        point = Vector(x, y);
        pseudo = Circle(c.x, c.y, c.r - r);
    }
    else
    {
        point = Vector(c.x, c.y);
        pseudo = Circle(x, y, r - c.r);
    }

    Vector X1, X2;
    std::pair<Line, Line> ts = pseudo.tangents(point, &X1, &X2);
    if (!ts.second.isValid)
    {
        ts.first.moveToVector((point - pseudo.center()).getNormal() * r);
        ts.first.moveToVector(-(point - pseudo.center()).getNormal() * r);
    }
    else
    {
        ts.first .moveToVector((X1 - pseudo.center()).normalized() * min(r, c.r));
        ts.second.moveToVector((X2 - pseudo.center()).normalized() * min(r, c.r));
    }
    return ts;
}

std::pair<Line, Line> Circle::commonInnerTangents(const Circle &c) const
{
    if (!(isValid && c.isValid) || (Vector(x, y).dist(Vector(c.x, c.y)) < r + c.r))
    {
        return std::pair<Line, Line>(Line(false), Line(false));
    }

    Vector point(c.x, c.y);
    Circle pseudo(x, y, r + c.r);

    Vector X1, X2;
    std::pair<Line, Line> ts = pseudo.tangents(point, &X1, &X2);

    if (!ts.second.isValid)
    {
        ts.first .moveToVector((pseudo.center() - point).normalized() * c.r);
        ts.second = ts.first;
    }
    else
    {
        ts.first .moveToVector((pseudo.center() - X1).normalized() * c.r);
        ts.second.moveToVector((pseudo.center() - X2).normalized() * c.r);
    }
    return ts;
}

Vector Circle::center() const
{
    return Vector(x, y, isValid);
}

bool Circle::isTangent(const Line &l) const
{
    if (!(isValid && l.isValid))
    {
        return false;
    }
    Vector O(x, y);
    return equal(r, (O - l.projection(O)).length());
}

int Circle::where(const Vector &v) const
{
    if (!(isValid && v.isValid))
    {
        return -100;
    }
    Vector O(x, y);
    return signum((O - v).length() - r);
}

Line Circle::radixLine(const Circle &c) const
{
    // (x - x1) ^ 2 + (y - y1) ^ 2 - (x - x2) ^ 2 - (y - y2) ^ 2 = r1 ^ 2 - r2 ^ 2
    // x1^2 - 2*x*x1 + y1^2 - 2*y*y1 -x2^2 + 2*x*x2 - y2^2 + 2*y*y2 = r1^2 - r2^2
    // x * (-2 * x1 + 2 * x2) + y * (-2 * y1 + 2 * y2) + x1^2 + y1^2 - r1^2 - x2^2 -y2^2 + r2^2 = 0
    return Line(2 * (c.x - x), 2 * (c.y - y), x * x + y * y - r * r - c.x * c.x - c.y * c.y + c.r * c.r, isValid && c.isValid);
}

