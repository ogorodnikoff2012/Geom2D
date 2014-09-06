#include <cmath>

const double EPS = 1e-7;

double eps()
{
    return EPS;
}

double toRadians(const double deg)
{
    return deg * M_PI / 180.0;
}

double toDegrees(const double rad)
{
    return rad * 180.0 / M_PI;
}

bool equal(const double a, const double b)
{
    return abs(a - b) < EPS;
}

int signum(double a)
{
    return equal(a, 0.0) ? 0 : a > 0 ? 1 : -1;
}

double max(double a, double b)
{
    return a < b ? b : a;
}
