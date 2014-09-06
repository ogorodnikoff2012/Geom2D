#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include "line.h"

class Ray : public Line
{
public:
    Vector end, direction;
    Ray(const Vector &end, const Vector &direction) :
        Line(end, end + direction),
        end(end),
        direction(direction)
    {

    }

    double dist(Vector &v) const;
};

#endif // RAY_H
