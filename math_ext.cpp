#include <cmath>
#include "math_ext.h"

const double EPS = 1e-7;

double geom2d::eps()
{
    return EPS;
}

double geom2d::toRadians(const double deg)
{
    return deg * M_PI / 180.0;
}

double geom2d::toDegrees(const double rad)
{
    return rad * 180.0 / M_PI;
}

bool geom2d::equal(const double a, const double b)
{
    return std::abs(a - b) < EPS;
}

int geom2d::signum(double a)
{
    return equal(a, 0.0) ? 0 : a > 0 ? 1 : -1;
}

double geom2d::max(double a, double b)
{
    return a < b ? b : a;
}
