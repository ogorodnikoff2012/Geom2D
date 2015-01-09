#include "ray.h"

using namespace geom2d;

double Ray::dist(Vector &v) const
{
    if(!(isValid && v.isValid))
    {
        return -100;
    }
    Vector H = projection(v);
    if((H - end) * direction < 0)
    {
        return v.dist(end);
    }
    return v.dist(H);
}
