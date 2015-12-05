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

std::pair<Line, Line> Circle::tangents(const Vector &A) const
{
    if (!(isValid && A.isValid))
    {
        return std::pair<Line, Line>(Line(false), Line(false));
    }

    Vector O(x, y);

    double oxProjection = r * r / O.dist(A);
    Vector OH = (A - O).normalize() * oxProjection;
    Vector H = O + OH;
    Vector HX = OH.getNormal() * sqrt(r * r - oxProjection * oxProjection);
    Vector X1 = H + HX, X2 = H - HX;

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
    double a = 2 * (c.x - x);
    double b = 2 * (c.y - y);
    double c_ = x * x - c.x * c.x + y * y - c.y * c.y + c.r * c.r - r * r;
    return intersect(Line(a, b, c_, c.isValid));
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
        point.x = x;
        point.y = y;
        pseudo.x = c.x;
        pseudo.y = c.y;
        pseudo.r = c.r - r;
    }
    else
    {
        point.x = c.x;
        point.y = c.y;
        pseudo.x = x;
        pseudo.y = y;
        pseudo.r = r - c.r;
    }

    std::pair<Line, Line> ts = pseudo.tangents(point);
    std::pair<Vector, Vector> normals(ts.first.getNormal() * fabs(r - c.r),
                                      ts.second.getNormal() * fabs(r - c.r));

    if (ts.first || ts.second)
    {
        ts.first.moveToVector(normals.first);
        ts.second.moveToVector(-normals.first);
    }
    else
    {
        ts.first.moveToVector(normals.first);

        if (!(isTangent(ts.first) && c.isTangent(ts.first)))
        {
            ts.first.moveToVector(-2 * normals.first);
        }

        ts.second.moveToVector(normals.second);

        if (!(isTangent(ts.second) && c.isTangent(ts.second)))
        {
            ts.second.moveToVector(-2 * normals.second);
        }
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

    std::pair<Line, Line> ts = pseudo.tangents(point);
    std::pair<Vector, Vector> normals(ts.first.getNormal() * fabs(r - c.r),
                                      ts.second.getNormal() * fabs(r - c.r));

    ts.first.moveToVector(normals.first);

    if (!(isTangent(ts.first) && c.isTangent(ts.first)))
    {
        ts.first.moveToVector(-2 * normals.first);
    }

    ts.second.moveToVector(normals.second);

    if (!(isTangent(ts.second) && c.isTangent(ts.second)))
    {
        ts.second.moveToVector(-2 * normals.second);
    }


    return ts;
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
    return Line(2 * (c.x - x), 2 * (c.y - y), x * x + y * y - r * r - c.x * c.x - c.y * c.y + c.r * c.r);
}

