#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include "line.h"

class Ray : public Line
{
public:
    Vector end, direction;
    Ray(const Vector &end, const Vector &direction, const bool isValid = true) :
        Line(end, end + direction, isValid && end.isValid && direction.isValid),
        end(end),
        direction(direction)
    {

    }

    double dist(Vector &v) const;
};

#endif // RAY_H
