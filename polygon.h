#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "vector.h"
#include "line.h"

namespace geom2d {

class Polygon
{
public:
    std::vector<Vector> points;
    bool isValid;
    Polygon(const std::vector<Vector> &points, const bool isValid = true);
    Polygon(const bool isValid = true) :
        isValid(isValid)
    {
        points.resize(1);
    }

    double area() const;
    bool hasPoint(const Vector &v) const;
    bool isConvex() const;
    Polygon convexHull() const;
    std::pair<Polygon, Polygon> split(const Line &l) const;
    Polygon intersection(const Polygon &p) const;
};
}
#endif // POLYGON_H
